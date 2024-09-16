#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtWidgets>
#include <QApplication>

class MainWindow : public QMainWindow
{
    Q_OBJECT
    bool opponentTurn;
    QPushButton** buttonArray;
    bool* playerValues;
    bool* opponentValues;
    bool isWinState(bool* values);
    bool checkLine(bool* values, int i, bool isColumn);
    bool checkDiagonals(bool* values);
    private slots:
        void buttonClicked(int it);  // Declaration of the slot
        void handleWin(int flag);

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
};
#endif // MAINWINDOW_H
