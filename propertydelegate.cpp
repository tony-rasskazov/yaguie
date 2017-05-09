#include "propertydelegate.h"

#include <QDebug>

#include <QPainter>
#include <QPalette>

#include <QByteArray>
#include <QDataStream>

#include "exvariant.h"

PropertyDelegate::PropertyDelegate(QWidget *parent)
    : QStyledItemDelegate(parent)
{

}

QString PropertyDelegate::displayText(const QVariant &value, const QLocale &locale) const
{
    if (value.canConvert<QString>()) {
        return QStyledItemDelegate::displayText(value, locale);
    } else {
        ExVariant v(value);
        return v.toString();
    }

}

void PropertyDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    if (index.data().isNull()) {
        painter->drawText(option.rect, "[null]", QTextOption(Qt::AlignVCenter | Qt::AlignLeft));
    }

    QVariant var(index.data());

    if (var.canConvert<QCursor>()) {
        QCursor c = var.value<QCursor>();

        qDebug() << c.pixmap().isNull()
                 << c.bitmap()
                 << c.mask();

        QString s("[cursor]");
        painter->drawText(option.rect, s, QTextOption(Qt::AlignVCenter | Qt::AlignLeft));

        painter->drawPixmap(0,0,c.pixmap());

    } else if (var.canConvert<QPalette>()) {
        QPalette p = var.value<QPalette>();

        QString s("[palette]");
        painter->drawText(option.rect, s, QTextOption(Qt::AlignVCenter | Qt::AlignLeft));

    } else {
        QStyledItemDelegate::paint(painter, option, index);
    }
}

