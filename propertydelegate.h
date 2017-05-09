#ifndef PROPERTYDELEGATE_H
#define PROPERTYDELEGATE_H

#include  <QStyledItemDelegate>

class PropertyDelegate : public QStyledItemDelegate
{
public:
    PropertyDelegate(QWidget *parent);

    QString displayText(const QVariant &value, const QLocale &locale) const;
    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;

    /*
    QWidget * createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const;
    void setEditorData(QWidget *editor, const QModelIndex &index) const;
    void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const;
    QSize sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const;
    void updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const;
*/

};

#endif // PROPERTYDELEGATE_H
