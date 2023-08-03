#ifndef TWINNAVIGATOR_MAINWINDOW_H
#define TWINNAVIGATOR_MAINWINDOW_H

#include <QMainWindow>
#include "Config.h"
#include "editor/editorwindow.h"

class MainWindow: public QMainWindow {
    QWidget* createGroup(int index);
    QWidget* createButtons();
    Config config;
    void F3View();
    void F4Edit();
    void F5Copy();
    void F6Move();
    void F7Directory();
    void F8Delete();
    void F9Terminal();
    void LastButtonExit();
    EditorWindow editorWindow;
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
