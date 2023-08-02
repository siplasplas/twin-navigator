#ifndef TWINNAVIGATOR_MAINWINDOW_H
#define TWINNAVIGATOR_MAINWINDOW_H

#include <QMainWindow>

class MainWindow: public QMainWindow {
    QWidget* createGroup();
    QWidget* createButtons();
public:
    MainWindow(QWidget *parent = nullptr);
};

#endif //TWINNAVIGATOR_MAINWINDOW_H
