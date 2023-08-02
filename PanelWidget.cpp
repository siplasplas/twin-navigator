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
        if (parent==mainWindow->panels[0])
            mainWindow->focusedPanel = 0;
        else if (parent==mainWindow->panels[1])
            mainWindow->focusedPanel = 1;
        else
            mainWindow->focusedPanel = -1;
        qDebug() << mainWindow->focusedPanel;
    }
    QTableView::focusInEvent(event);
}
