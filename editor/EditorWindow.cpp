/****************************************************************************
**
** Created by Andrzej Borucki on 2022-08-17
**
** This file is part of the EdiQ project
** see file LICENSE
**
****************************************************************************/

#include "EditorWindow.h"
#include "EditorFactory.h"
#include "SearchBar.h"
#include <QMenuBar>
#include <QFileDialog>
#include <QCloseEvent>
#include <QGuiApplication>
#include "CodeEditor.h"

void initLibraryResources() {
    Q_INIT_RESOURCE(icons1);
}

Q_CONSTRUCTOR_FUNCTION(initLibraryResources)

EditorWindow::EditorWindow(QWidget *parent)
    : QMainWindow(parent)
{
    createMenus();
    tabWidget.setTabsClosable(true);
    tabWidget.setMovable(true);
    tabWidget.setTabPosition(QTabWidget::South);
    setCentralWidget(&tabWidget);
    editorFactory = new EditorFactory(&tabWidget);
    connect(&tabWidget, &QTabWidget::tabCloseRequested, this, [this](int index) {
        IEditor::CloseEnum canClose = IEditor::clClose;
        editorFactory->tryCloseEditor(index, canClose);
    });
    connect(&tabWidget, &QTabWidget::currentChanged, this, &EditorWindow::tabSelected);
    QGuiApplication::instance()->installEventFilter(this);
}

EditorWindow::~EditorWindow()
{
    delete (EditorFactory*)editorFactory;
}

void EditorWindow::createMenus() {
    QMenu *fileMenu = menuBar()->addMenu(tr("&File"));

    QAction *newAct = new QAction(tr("&New"), this);
    newAct->setShortcut(QKeySequence("ctrl+n"));
    fileMenu->addAction(newAct);
    connect(newAct, &QAction::triggered, this, &EditorWindow::newFile);

    QAction *openAct = new QAction(tr("&Open..."), this);
    openAct->setShortcut(QKeySequence("ctrl+o"));
    fileMenu->addAction(openAct);
    connect(openAct, &QAction::triggered, this, &EditorWindow::openFile);

    QAction *saveAct = new QAction(tr("&Save"), this);
    saveAct->setShortcut(QKeySequence("ctrl+s"));
    fileMenu->addAction(saveAct);
    connect(saveAct, &QAction::triggered, this, &EditorWindow::saveFile);

    QAction *saveAsAct = new QAction(tr("save &As..."), this);
    fileMenu->addAction(saveAsAct);
    connect(saveAsAct, &QAction::triggered, this, &EditorWindow::saveAsFile);

    QAction *closeAct = new QAction(tr("&Close"), this);
    closeAct->setShortcut(QKeySequence("ctrl+F4"));
    fileMenu->addAction(closeAct);
    connect(closeAct, &QAction::triggered, this, &EditorWindow::closeFile);

    QAction *closeAllAct = new QAction(tr("clos&E all"), this);
    closeAllAct->setShortcut(QKeySequence("shift+ctrl+F4"));
    fileMenu->addAction(closeAllAct);
    connect(closeAllAct, &QAction::triggered, this, &EditorWindow::closeAllFile);

    QMenu *searchMenu = menuBar()->addMenu(tr("&Search"));
    QAction *findAct = new QAction(tr("&Find..."), this);
    findAct->setShortcut(QKeySequence("ctrl+f"));
    searchMenu->addAction(findAct);
    connect(findAct, &QAction::triggered, this, &EditorWindow::findSearch);

    QAction *findNextAct = new QAction(tr("find &Next"), this);
    findNextAct->setShortcut(QKeySequence("f3"));
    searchMenu->addAction(findNextAct);
    connect(findNextAct, &QAction::triggered, this, &EditorWindow::findNextSearch);

    QAction *findPreviousAct = new QAction(tr("find &Previous"), this);
    findPreviousAct->setShortcut(QKeySequence("shift+f3"));
    searchMenu->addAction(findPreviousAct);
    connect(findPreviousAct, &QAction::triggered, this, &EditorWindow::findPreviousSearch);

    QMenu *toolsMenu = menuBar()->addMenu(tr("&Tools"));
    QAction *insertDateAct = new QAction(tr("insert &Date"), this);
    toolsMenu->addAction(insertDateAct);
    connect(insertDateAct, &QAction::triggered, this, &EditorWindow::insertDate);

    QAction *insertTimeAct = new QAction(tr("insert &Time"), this);
    toolsMenu->addAction(insertTimeAct);
    connect(insertTimeAct, &QAction::triggered, this, &EditorWindow::insertTime);

    QAction *insertBothAct = new QAction(tr("insert &Both date and time"), this);
    toolsMenu->addAction(insertBothAct);
    connect(insertBothAct, &QAction::triggered, this, &EditorWindow::insertBoth);
}

void EditorWindow::newFile() {
    CodeEditor *editor = (CodeEditor *)editorFactory->createEditorTab("");
    tabWidget.setCurrentWidget(editor);
}

void EditorWindow::openOrActivate(QString path) {
    CodeEditor *editor = (CodeEditor *)editorFactory->getEditorByPath(path);
    if (editor) {
        auto plainEdit = editor->plainEdit;
        QTextCursor cursor = plainEdit->textCursor();
        int position = cursor.position();
        editor->openFile();
        cursor.setPosition(position, QTextCursor::MoveAnchor);
        plainEdit->setTextCursor(cursor);
        editor->activateWindow();
        plainEdit->document()->setModified(false);
        editorFactory->onTextChanged();
    }
    else {
        editor = (CodeEditor *) editorFactory->createEditorTab(path);
        editor->openFile();
        editorFactory->onTextChanged();
    }
    tabWidget.setCurrentWidget(editor);
    editor->setPlainFocus();
}

void EditorWindow::openFile()
{
    QFileDialog dialog(this, tr("Open File"));
    dialog.setOption(QFileDialog::DontUseNativeDialog);
    if (dialog.exec() == QDialog::Accepted) {
        QString path = dialog.selectedFiles().first();
        openOrActivate(path);
    }
}

void EditorWindow::saveFile() {
    IEditor *editor = editorFactory->getCurrentEditor();
    if (!editor) return;
    editor->save();
    editorFactory->onTextChanged();
}

void EditorWindow::saveAsFile() {
    IEditor *editor = editorFactory->getCurrentEditor();
    if (!editor) return;
    editor->saveAs();
    tabWidget.setTabText(tabWidget.currentIndex(), editor->getTitle());
    editorFactory->onTextChanged();
    tabSelected(tabWidget.currentIndex());
}

void EditorWindow::closeFile() {
    editorFactory->tryCloseCurrentEditor();
}

void EditorWindow::closeAllFile() {
    editorFactory->tryCloseAll();
}

void EditorWindow::closeEvent(QCloseEvent *event) {
    if (editorFactory->tryCloseAll())
        event->accept();
    else
        event->ignore();
}

void EditorWindow::findSearch() {
    IEditor *editor = editorFactory->getCurrentEditor();
    if (!editor) return;
    editor->find();
}

void EditorWindow::findNextSearch() {
    IEditor *editor = editorFactory->getCurrentEditor();
    if (!editor) return;
    editor->findNext();
}

void EditorWindow::findPreviousSearch() {
    IEditor *editor = editorFactory->getCurrentEditor();
    if (!editor) return;
    editor->findPrevious();
}

void EditorWindow::activateTab(int index) {
    assert(index>=0);
    if (index==tabWidget.currentIndex()) return;
    if (index>=tabWidget.count()) return;
    tabWidget.setCurrentWidget(tabWidget.widget(index));
}

bool EditorWindow::eventFilter(QObject *target, QEvent *event) {
    QKeyEvent* keyEvent = dynamic_cast<QKeyEvent*>(event);
    if (event->type() == QEvent::KeyPress)
    {
        int key = keyEvent->key();
        if (key >= '0' && key <= '9' && keyEvent->modifiers() & Qt::AltModifier) {
            int n = key > '0'? key-'1': 9;
            activateTab(n);
            return true;
        } else if (key == Qt::Key_Escape) {
            IEditor* editor = editorFactory->getCurrentEditor();
            if (editor)
                editor->setPlainFocus();
            return true;
        }
    }
    return QObject::eventFilter(target, event);
}

void EditorWindow::insertDate() {
    IEditor *editor = editorFactory->getCurrentEditor();
    if (!editor) return;
    editor->insertDate();
}

void EditorWindow::insertTime() {
    IEditor *editor = editorFactory->getCurrentEditor();
    if (!editor) return;
    editor->insertTime();
}

void EditorWindow::insertBoth() {
    IEditor *editor = editorFactory->getCurrentEditor();
    if (!editor) return;
    editor->insertBoth();
}

void EditorWindow::tabSelected(int n) {
    IEditor *editor = editorFactory->getCurrentEditor();
    if (!editor) return;
    this->setWindowTitle(editor->getPath());
}
