/****************************************************************************
**
** Created by Andrzej Borucki on 2022-08-17
**
** This file is part of the EdiQ project
** see file LICENSE
**
****************************************************************************/

#ifndef EDITORWINDOW_H
#define EDITORWINDOW_H

#include <QMainWindow>
#include "IEditorFactory.h"

class EditorWindow : public QMainWindow
{
    Q_OBJECT
public:
    EditorWindow(QWidget *parent = nullptr);
    ~EditorWindow();
    void receivedMessage(int instanceId, QByteArray message);
    void openOrActivate(QString path);
protected:
    void closeEvent(QCloseEvent *event) override;
private:
    void tabSelected(int n);
    IEditorFactory *editorFactory;
    void createMenus();
    QTabWidget tabWidget;
    void newFile();
    void openFile();
    void saveFile();
    void saveAsFile();
    void closeFile();
    void closeAllFile();
    void findSearch();
    void findNextSearch();
    void findPreviousSearch();
    void onTextChanged();
    void activateTab(int index);
    bool eventFilter(QObject *target, QEvent *event) override;
    void insertDate();
    void insertTime();
    void insertBoth();
};
#endif // EDITORWINDOW_H
