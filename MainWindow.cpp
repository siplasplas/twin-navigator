#include "MainWindow.h"
#include "PanelWidget.h"
#include <QMenuBar>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QStatusBar>
#include <QToolButton>
#include <QScreen>
#include <QGuiApplication>

typedef void (MainWindow::*MainWindowMethod)();

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
    QIcon icon;
    icon.addFile(":Floppy_icon.svg", QSize(72, 72));
    setWindowIcon(icon);

    QMenuBar *menuBar = new QMenuBar;
    QMenu *fileMenu = new QMenu("File", this);
    QMenu *tabsMenu = new QMenu("Tabs", this);
    menuBar->addMenu(fileMenu);
    menuBar->addMenu(tabsMenu);
    this->setMenuBar(menuBar);
    QToolBar *toolbar = addToolBar("Main Toolbar");

    auto group0 = createGroup(0);
    auto group1 = createGroup(1);

    QHBoxLayout *hLayout = new QHBoxLayout;
    hLayout->addWidget(group0);
    hLayout->addWidget(group1);

    QLabel *label = new QLabel("Label", this);
    QLineEdit *lineEdit = new QLineEdit(this);

    QVBoxLayout *vLayout = new QVBoxLayout;
    vLayout->addLayout(hLayout);

    QHBoxLayout *hLayout2 = new QHBoxLayout;
    hLayout2->addWidget(label);
    hLayout2->addWidget(lineEdit);
    vLayout->addLayout(hLayout2);

    QWidget *widget = new QWidget;
    widget->setLayout(vLayout);
    setCentralWidget(widget);

    QString StatusLabels[] = {"F3 View", "F4 Edit", "F5 Copy", "F6 Move",
                              "F7 Directory", "F8 Delete", "F9 Terminal", "Alt+F4 Exit "};

    const MainWindowMethod handlers[8] = {&MainWindow::F3View, &MainWindow::F4Edit,
                                          &MainWindow::F5Copy, &MainWindow::F6Move,
                                          &MainWindow::F7Directory, &MainWindow::F8Delete,
                                          &MainWindow::F9Terminal, &MainWindow::LastButtonExit};

    QStatusBar *statusBar = new QStatusBar;
    for (int i = 0; i < 8; ++i) {
        QToolButton *button = new QToolButton();
        button->setText(StatusLabels[i]);
        button->setAutoRaise(true);
        button->setContentsMargins(0,0,0,0);
        connect(button, &QToolButton::clicked, this, handlers[i]);
        statusBar->addWidget(button);
    }
    setStatusBar(statusBar);

    QAction *actionAddTab = new QAction("Add tab", this);
    actionAddTab->setShortcut(QKeySequence("Ctrl+t"));
    tabsMenu->addAction(actionAddTab);
    connect(actionAddTab, &QAction::triggered, this, &MainWindow::onAddTab);

    QAction *actionCloseTab = new QAction("Close tab", this);
    actionCloseTab->setShortcut(QKeySequence("ctrl+w"));
    tabsMenu->addAction(actionCloseTab);
    connect(actionCloseTab, &QAction::triggered, this, &MainWindow::onCloseTab);

    focusedPanel = 0;
    panels[focusedPanel]->currentWidget()->setFocus();
    QScreen *screen = QGuiApplication::primaryScreen();
    QRect  screenGeometry = screen->geometry();
    editorWindow.setGeometry(int(screenGeometry.width()*0.1), int(screenGeometry.height()*0.1),
                           int(screenGeometry.width()*0.8), int(screenGeometry.height()*0.8));
    editorWindow.show();
}

QWidget* MainWindow::createButtons() {
    QWidget *widget = new QWidget(this);
    QHBoxLayout *hLayout = new QHBoxLayout;
    hLayout->setSpacing(0); // Redukuje odstępy poziome
    hLayout->setContentsMargins(0, 0, 0, 0); // Usuwa marginesy

    // Dodajemy kilka mniejszych przycisków
    for (int i = 0; i < 2; ++i) {
        QToolButton *button = new QToolButton();
        button->setText(QString("Button %1").arg(i+1));
        button->setAutoRaise(true);
        hLayout->addWidget(button);
    }

    // Wypełniamy resztę układu pustym miejscem
    hLayout->addStretch(1);

    widget->setLayout(hLayout);
    return widget;
}

QWidget* MainWindow::createGroup(int index) {
    QWidget *widget = new QWidget(this);

    QVBoxLayout *vLayout = new QVBoxLayout;
    vLayout->setSpacing(0); // Redukuje odstępy pionowe
    vLayout->setContentsMargins(0, 0, 0, 0); // Usuwa marginesy

    vLayout->addWidget(createButtons());
    vLayout->addWidget(createButtons());
    int n = config.paths[index].size();
    if (n==0)
        config.paths[index].push_back(".");
    n = config.paths[index].size();
    QTabWidget* tabWidget = new QTabWidget;
    for (int i=0; i<n; i++) {
        PanelWidget* panelWidget = new PanelWidget(this, config.paths[index][i]);
        connect(panelWidget, &PanelWidget::changePanelSignal, this, &MainWindow::handleChangePanel);
        tabWidget->addTab(panelWidget,panelWidget->getTitle());
    }
    panels[index] = tabWidget;
    vLayout->addWidget(tabWidget);
    vLayout->addWidget(new QLabel("Label", this));

    widget->setLayout(vLayout);
    return widget;
}

void MainWindow::handleChangePanel() {
    if (focusedPanel == 0)
        focusedPanel = 1;
    else
        focusedPanel = 0;
    panels[focusedPanel]->currentWidget()->setFocus();
}

void MainWindow::onAddTab()
{
    if (focusedPanel<0)
        return;
    QTabWidget *tabWidget = panels[focusedPanel];
    PanelWidget* panelWidget = new PanelWidget(this, ".");
    connect(panelWidget, &PanelWidget::changePanelSignal, this, &MainWindow::handleChangePanel);
    tabWidget->addTab(panelWidget,panelWidget->getTitle());
}

void MainWindow::onCloseTab()
{
    qDebug() << "Control+W was pressed";
}

void MainWindow::F3View() {

}

void MainWindow::F4Edit() {

}

void MainWindow::F5Copy() {

}

void MainWindow::F6Move() {

}

void MainWindow::F7Directory() {

}

void MainWindow::F8Delete() {

}

void MainWindow::F9Terminal() {

}

void MainWindow::LastButtonExit() {
    close();
}
