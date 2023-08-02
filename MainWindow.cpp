#include "MainWindow.h"
#include "PanelWidget.h"
#include <QMenuBar>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QStatusBar>
#include <QToolButton>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
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

    QStatusBar *statusBar = new QStatusBar;
    for (int i = 0; i < 8; ++i) {
        QToolButton *button = new QToolButton();
        button->setText(QString("Section %1").arg(i+1));
        button->setAutoRaise(true);
        button->setContentsMargins(0,0,0,0);
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
    PanelWidget* panelWidget = new PanelWidget(this, "..");
    connect(panelWidget, &PanelWidget::changePanelSignal, this, &MainWindow::handleChangePanel);
    QTabWidget* tabWidget = new QTabWidget;
    panels[index] = tabWidget;
    tabWidget->addTab(panelWidget,panelWidget->getTitle());
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