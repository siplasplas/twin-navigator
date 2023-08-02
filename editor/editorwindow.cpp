#include "editorwindow.h"
#include <QDebug>

EditorWindow::EditorWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setCentralWidget(&editor);
}

EditorWindow::~EditorWindow()
{
}
