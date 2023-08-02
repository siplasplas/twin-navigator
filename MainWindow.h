#ifndef TWINNAVIGATOR_MAINWINDOW_H
#define TWINNAVIGATOR_MAINWINDOW_H

#include <QMainWindow>
#include "Config.h"

class MainWindow: public QMainWindow {
    QWidget* createGroup(int index);
    QWidget* createButtons();
    Config config;
public:
    void handleChangePanel();
    QTabWidget *panels[2];
    int focusedPanel = -1;
    MainWindow(QWidget *parent = nullptr);
public slots:
    void onAddTab();
    void onCloseTab();
};

#endif //TWINNAVIGATOR_MAINWINDOW_H
