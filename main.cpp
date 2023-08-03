#include <QApplication>
#include "MainWindow.h"
#include "editor/editorwindow.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    app.setStyle("fusion");
    MainWindow w;
    w.show();
    return app.exec();
}
