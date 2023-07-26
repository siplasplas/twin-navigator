#ifndef TABLEWIDGET_PANELWIDGET_H
#define TABLEWIDGET_PANELWIDGET_H

#include <QTableView>
#include <QStandardItem>
#include <QDateTime>
#include <QHeaderView>
#include <QFileIconProvider>
#include <QStyledItemDelegate>
#include <QPainter>
#include "FilePanel.h"
#include "MarkableItem.h"


class MyDelegate : public QStyledItemDelegate {
public:
    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const override {
        QStandardItemModel *model = qobject_cast<QStandardItemModel*>(const_cast<QAbstractItemModel*>(index.model()));
        MarkableItem *item = nullptr;
        if (model) {
            item = static_cast<MarkableItem*>(model->itemFromIndex(index));
        }
        if (item && item->isMarked) {
            QStyleOptionViewItem opt = option;
            opt.palette.setColor(QPalette::Text, Qt::red);
            opt.palette.setColor(QPalette::HighlightedText, Qt::red);
            QStyledItemDelegate::paint(painter, opt, index);
        } else {
            QStyledItemDelegate::paint(painter, option, index);
        }
    }
};

/*
class MyDelegate : public QStyledItemDelegate {
public:
    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const override {
        MarkableItem *item = static_cast<MarkableItem*>(index.internalPointer());
        if (item && item->isMarked) {
            painter->fillRect(option.rect, Qt::red); // zmień na swój kolor
        }
        QStyledItemDelegate::paint(painter, option, index);
    }
};
*/

class PanelWidget : public QTableView
{
private:
    FilePanel* panel;
public:
    PanelWidget(const QString& path, QWidget* parent = nullptr)
            : QTableView(parent), panel(panel)
    {
        panel = new FilePanel(path);
        MyDelegate *delegate = new MyDelegate;
        setItemDelegate(delegate);
        QStandardItemModel *model = new QStandardItemModel(panel->getFiles().count(), 3);
        setModel(model);
        setSelectionBehavior(QAbstractItemView::SelectRows);
        setEditTriggers(QAbstractItemView::NoEditTriggers);
        verticalHeader()->setVisible(false);
        updateFiles();
    }

    QString getTitle() {
        return panel->getPath().section('/',-1);
    }

    ~PanelWidget(){
        delete panel;
    }

    QStandardItemModel *model() const {
        return dynamic_cast<QStandardItemModel *>(QTableView::model());
    }

    void updateFiles() {
        model()->clear();
        QFileIconProvider iconProvider;
        QStringList headers;
        headers << "Name" << "Size" << "Time";
        model()->setHorizontalHeaderLabels(headers);
        for (int i = 0; i < panel->getFiles().count(); ++i) {
            const QFileInfo& fileInfo = panel->getFiles().at(i);

            MarkableItem* nameItem = new MarkableItem(fileInfo.fileName());
            MarkableItem* sizeItem = new MarkableItem(QString::number(fileInfo.size()));
            MarkableItem* dateItem = new MarkableItem(fileInfo.lastModified().toString());

            if (i % 2) {
                nameItem->isMarked = true;
                sizeItem->isMarked = true;
                dateItem->isMarked = true;
            }
            // Dodawanie elementów do widgetu
            model()->setItem(i, 0, nameItem);
            model()->setItem(i, 1, sizeItem);
            model()->setItem(i, 2, dateItem);

            nameItem->setIcon(iconProvider.icon(QFileInfo(fileInfo.filePath())));
        }
    }
};

#endif //TABLEWIDGET_PANELWIDGET_H
