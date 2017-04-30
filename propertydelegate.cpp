#include "propertydelegate.h"

#include <QDebug>

#include "exvariant.h"

PropertyDelegate::PropertyDelegate(QWidget *parent)
    : QStyledItemDelegate(parent)
{

}

QString PropertyDelegate::displayText(const QVariant &value, const QLocale &locale) const
{
    //qDebug


    if (value.canConvert<QString>()) {
        qDebug() << "1" << value << value.toString();
        return QStyledItemDelegate::displayText(value, locale);
    } else {
        ExVariant v(value);
        qDebug() << "2" << value << v << v.toString();
        return v.toString();
    }

}

