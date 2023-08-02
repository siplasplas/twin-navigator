#ifndef TWINNAVIGATOR_MAINWINDOW_H
#define TWINNAVIGATOR_MAINWINDOW_H

#include <QMainWindow>

class MainWindow: public QMainWindow {
    QWidget* createGroup(int index);
    QWidget* createButtons();
public:
    void handleChangePanel();
    QTabWidget *panels[2];
    int focusedPanel = -1;
    MainWindow(QWidget *parent = nullptr);
};

#endif //TWINNAVIGATOR_MAINWINDOW_H
