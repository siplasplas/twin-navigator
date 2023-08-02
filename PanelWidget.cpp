#include "PanelWidget.h"
#include "MainWindow.h"
#include <QApplication>

void PanelWidget::focusInEvent(QFocusEvent* event)
{
    MainWindow* mainWindow = nullptr;
    const auto topLevelWidgets = QApplication::topLevelWidgets();
    for (QWidget* widget : topLevelWidgets) {
        mainWindow = dynamic_cast<MainWindow*>(window());
        if (mainWindow) {
            break;
        }
    }
    if (mainWindow) {
        auto parent = parentWidget()->parentWidget()->parentWidget();
        if (parent==mainWindow->groups[0])
            mainWindow->focusedGroup = 0;
        else if (parent==mainWindow->groups[1])
            mainWindow->focusedGroup = 1;
        else
            mainWindow->focusedGroup = -1;
        qDebug() << mainWindow->focusedGroup;
    }
}
