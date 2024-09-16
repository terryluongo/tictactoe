#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    QWidget *center = new QWidget();

    setCentralWidget(center);

    QGridLayout *mainLayout = new QGridLayout(center);

    buttonArray = new QPushButton*[9];
    playerValues = new bool[9]();
    opponentValues = new bool[9]();

    opponentTurn = 1;

    // put buttons on screen, conncet up to handling function
    for(int i = 0; i < 9; i++) {
        buttonArray[i] = new QPushButton(" ");

        mainLayout->addWidget(buttonArray[i], i / 3, i % 3, Qt::AlignCenter);

        connect(buttonArray[i], &QPushButton::clicked, this,
                [this, i]() {this->buttonClicked(i); //lambda function to pass id;
        });
    }

}

MainWindow::~MainWindow() {
//delete []
}

void MainWindow::buttonClicked(int id) {
    // do nothing if box was already played
    if(!opponentTurn && playerValues[id]) return;
    if(opponentTurn && opponentValues[id]) return;

    // other persons turn
    this->opponentTurn = !this->opponentTurn;

    // add the new square to the right person's array
    opponentTurn ? this->opponentValues[id] = true : this->playerValues[id] = true;
    QString text;

    // set text to display
    if(opponentTurn && opponentValues[id]) text = "o";
    else if (!opponentTurn && playerValues[id]) text = "x";
    else text = " ";
    this->buttonArray[id]->setText(text);

    // check if win, then handle new game or quit
    QMessageBox::StandardButton reply;
    if(isWinState(playerValues)) {
        reply = QMessageBox::question(this, "Game Over", "Player wins! Play again?");
        handleWin(reply);
    }
    if(isWinState(opponentValues)) {
        reply = QMessageBox::question(this, "Game Over", "Opponent wins! Play again?");
        handleWin(reply);
    }
}

// quit the game or start a new one with clean memory
void MainWindow::handleWin(int responseFlag) {
    if (responseFlag == QMessageBox::Yes) {
        for (int i = 0; i < 9; i++) {
            playerValues[i] = 0;
            opponentValues[i] = 0;
            buttonArray[i]->setText(" ");
        }
    }
    else QApplication::quit();
}

//check if specific player's array is in a win state
bool MainWindow::isWinState(bool* values) {
    bool win = false;

    for (int i = 0; i < 3; i++) {
        win = win || checkLine(values, i, false) || checkLine(values, i, true);
    }

    win = win || checkDiagonals(values);

    return win;
}

// check a specific line for a win
bool MainWindow::checkLine(bool* values, int i, bool isColumn) {
    if (isColumn) {
        return values[3 * i] && values[3 * i + 1] && values[3 * i + 2];
    }
    else {
        return values[i] && values[i + 3] && values[i + 6];
    }
}

// check diagonals for a win
bool MainWindow::checkDiagonals(bool* values) {
    bool firstDiagonal = values[0] && values[4] && values[8];
    bool secondDiagonal = values[2] && values[4] && values[6];

    return firstDiagonal || secondDiagonal;
}


