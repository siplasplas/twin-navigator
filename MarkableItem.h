#ifndef TWINNAVIGATOR_MARKABLEITEM_H
#define TWINNAVIGATOR_MARKABLEITEM_H

#include <QStandardItem>

class MarkableItem : public QStandardItem {
public:
    MarkableItem(const QString &text) : QStandardItem(text), isMarked(false) {}
    bool isMarked;
};

#endif //TWINNAVIGATOR_MARKABLEITEM_H
