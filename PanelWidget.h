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
#include <QKeyEvent>
#include <QDebug>
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

class PanelWidget : public QTableView
{
Q_OBJECT
private:
    FilePanel* panel;
    QWidget* mainWidget;
public:
    PanelWidget(QWidget* mainWidget, const QString& path, QWidget* parent = nullptr)
            : QTableView(parent), panel(panel)
    {
        this->mainWidget = mainWidget;
        panel = new FilePanel(path);
        MyDelegate *delegate = new MyDelegate;
        setItemDelegate(delegate);
        int isUp = 1;
        QStandardItemModel *model = new QStandardItemModel(panel->getFiles().count()+isUp, 3);
        setModel(model);
        setSelectionMode(QAbstractItemView::SingleSelection);
        setSelectionBehavior(QAbstractItemView::SelectRows);
        setEditTriggers(QAbstractItemView::NoEditTriggers);
        verticalHeader()->setVisible(false);
        updateFiles();
        selectRow(0);
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
        QStandardItem *upItem = new QStandardItem("..");
        model()->setItem(0, 0, upItem);
        int isUp = 1;
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
            model()->setItem(i+isUp, 0, nameItem);
            model()->setItem(i+isUp, 1, sizeItem);
            model()->setItem(i+isUp, 2, dateItem);

            nameItem->setIcon(iconProvider.icon(QFileInfo(fileInfo.filePath())));
        }
    }
private:
    void goSelected() {
        QItemSelectionModel *selectionModel = this->selectionModel();
        QModelIndexList selectedRows = selectionModel->selectedRows();
        int isUp = 1;
        if (!selectedRows.isEmpty()) {
            int selectedRow = selectedRows.first().row();
            if (selectedRow>=isUp) {
                QFileInfo fileInfo = panel->getFiles()[selectedRow-isUp];
                qDebug() << fileInfo.canonicalFilePath();
            } else {

            }
        }
    }
protected:
    void keyPressEvent(QKeyEvent *event) override {
        if(event->key() == Qt::Key_Enter || event->key() == Qt::Key_Return) {
            qDebug() << "Enter pressed";
            goSelected();
        } else  if (event->key() == Qt::Key_Tab) {
            emit changePanelSignal();
        }
        else QTableView::keyPressEvent(event);
    }

    void focusInEvent(QFocusEvent* event) override;

    void mouseDoubleClickEvent(QMouseEvent* event) override {
        qDebug() << "Double click";
        goSelected();
    }
signals:
    void changePanelSignal();
};

#endif //TABLEWIDGET_PANELWIDGET_H
