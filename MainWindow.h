#ifndef TWINNAVIGATOR_MAINWINDOW_H
#define TWINNAVIGATOR_MAINWINDOW_H

#include <QMainWindow>

class MainWindow: public QMainWindow {
    QWidget* createGroup();
    QWidget* createButtons();
public:
    QWidget *groups[2];
    int focusedGroup = -1;
    MainWindow(QWidget *parent = nullptr);
};

#endif //TWINNAVIGATOR_MAINWINDOW_H
