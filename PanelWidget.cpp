#include "PanelWidget.h"
#include "MainWindow.h"
#include <QApplication>

void PanelWidget::focusInEvent(QFocusEvent* event)
{
    MainWindow* mainWindow = dynamic_cast<MainWindow*>(mainWidget);
    if (mainWindow) {
        auto qTab =parent()->parent();
        if (qTab==mainWindow->panels[0])
            mainWindow->focusedPanel = 0;
        else if (qTab==mainWindow->panels[1])
            mainWindow->focusedPanel = 1;
        else
            mainWindow->focusedPanel = -1;
    }
    QTableView::focusInEvent(event);
}
