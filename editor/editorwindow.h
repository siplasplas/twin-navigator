#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPlainTextEdit>

class EditorWindow : public QMainWindow
{
    Q_OBJECT

public:
    EditorWindow(QWidget *parent = nullptr);
    ~EditorWindow();
private:
    QPlainTextEdit editor;
protected:
    //void changeEvent(QEvent *event) override;
};
#endif // MAINWINDOW_H
