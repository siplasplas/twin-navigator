#include <QApplication>
#include <QMainWindow>
#include <QMenu>
#include <QMenuBar>
#include <QToolBar>
#include <QAction>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QGroupBox>
#include <QTabWidget>
#include <QLabel>
#include <QLineEdit>
#include <QStatusBar>
#include <QTableView>
#include <QToolButton>
#include "PanelWidget.h"

class MainWindow : public QMainWindow {
public:
    MainWindow(QWidget *parent = nullptr) : QMainWindow(parent) {
        // Tworzenie menu
        QMenuBar *menuBar = new QMenuBar;
        QMenu *fileMenu = new QMenu("File", this);
        menuBar->addMenu(fileMenu);
        this->setMenuBar(menuBar);

        // Tworzenie toolbar
        QToolBar *toolbar = addToolBar("Main Toolbar");

        // Tworzenie grup widgetów
        QWidget *groupBox1 = createGroup();
        QWidget *groupBox2 = createGroup();

        QHBoxLayout *hLayout = new QHBoxLayout;
        hLayout->addWidget(groupBox1);
        hLayout->addWidget(groupBox2);

        // Tworzenie labela i linii edycyjnej
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

        // Tworzenie statusu
//        QStatusBar *statusBar = new QStatusBar;
//        for (int i = 0; i < 8; ++i) {
//            statusBar->addWidget(new QLabel(QString("Section %1").arg(i+1)));
//        }
        QStatusBar *statusBar = new QStatusBar;
        for (int i = 0; i < 8; ++i) {
            QToolButton *button = new QToolButton();
            button->setText(QString("Section %1").arg(i+1));
            button->setAutoRaise(true);
            button->setContentsMargins(0,0,0,0);
            //button->setStyleSheet("QToolButton { border: none; }");
//            connect(button, &QPushButton::clicked, this, &MainWindow::onButtonClicked);
            statusBar->addWidget(button);
        }
        setStatusBar(statusBar);
    }

    QWidget* createGroup() {
        QWidget *widget = new QWidget(this);

        QVBoxLayout *vLayout = new QVBoxLayout;
        vLayout->setSpacing(0); // Redukuje odstępy pionowe
        vLayout->setContentsMargins(0, 0, 0, 0); // Usuwa marginesy

        vLayout->addWidget(createButtons());
        vLayout->addWidget(createButtons());
        PanelWidget* panelWidget = new PanelWidget("..");
        QTabWidget* tabWidget = new QTabWidget;
        tabWidget->addTab(panelWidget,panelWidget->getTitle());
        vLayout->addWidget(tabWidget);
        vLayout->addWidget(new QLabel("Label", this));

        widget->setLayout(vLayout);
        return widget;
    }

    QWidget* createButtons() {
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
};

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    app.setStyle("fusion");
    MainWindow w;
    w.show();
    return app.exec();
}
