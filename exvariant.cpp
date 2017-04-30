#include "exvariant.h"

#include <QRect>
#include <QSize>

#include <QDebug>

template <typename T>
inline QString _toString(T v) {
    return v.toString();
}

template <>
inline QString _toString(QRect v) {
    return QString("(%1,%2,%3,%4)").arg(v.x()).arg(v.y()).arg(v.width()).arg(v.height());;
}

template <>
inline QString _toString(QSize v) {
    return QString("(%1,%2)").arg(v.width()).arg(v.height());;
}

template <>
inline QString _toString(QPoint v) {
    return QString("(%1,%2)").arg(v.x()).arg(v.y());;
}


ExVariant::ExVariant()
    :QVariant()
{

}

ExVariant::ExVariant(const QVariant &orig)
    :QVariant(orig)
{

}

QString ExVariant::toString() const
{

    switch (type()) {
    case QMetaType::QRect : {
        return _toString(value<QRect>());
    } break;
    case QMetaType::QSize : {
        return _toString(value<QSize>());
    } break;
    case QMetaType::QPoint : {
        return _toString(value<QPoint>());
    } break;
    }

    return _toString((QVariant)*this);
}

