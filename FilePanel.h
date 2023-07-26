#ifndef TABLEWIDGET_FILEPANEL_H
#define TABLEWIDGET_FILEPANEL_H

#include <QDir>
#include <QFileInfoList>

class FilePanel
{
public:
    FilePanel(const QString& path = QDir::homePath())
            : dir(path)
    {
        refresh();
    }

    void setPath(const QString& newPath) {
        dir.setPath(newPath);
        refresh();
    }

    const QString getPath() const { return dir.canonicalPath(); }
    const QFileInfoList& getFiles() const { return files; }

    void refresh() {
        files = dir.entryInfoList(QDir::AllEntries | QDir::NoDotAndDotDot);
    }

private:
    QString dirPath;
    QDir dir;
    QFileInfoList files;
};

#endif //TABLEWIDGET_FILEPANEL_H
