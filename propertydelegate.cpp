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

    ExVariant v(value);
    return v.toString();

}

