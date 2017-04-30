#include "exvariant.h"

#include <QRect>
#include <QSize>
#include <QRegion>

#include <QDebug>

inline QString _toString(QVariant v) {
    return v.toString();
}

inline QString _toString(QRect v) {
    return QString("{%1,%2 %3x%4}").arg(v.x()).arg(v.y()).arg(v.width()).arg(v.height());;
}

inline QString _toString(QSize v) {
    return QString("[%1x%2]").arg(v.width()).arg(v.height());;
}

inline QString _toString(QSizeF v) {
    return QString("[%1x%2]").arg(v.width()).arg(v.height());;
}

inline QString _toString(QPoint v) {
    return QString("(%1,%2)").arg(v.x()).arg(v.y());;
}

inline QString _toString(QRegion v) {
    QString s;
    foreach (QRect r, v.rects()) {
        s += _toString(r);
    }
    return QString("(%1)").arg(s);
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
    case QMetaType::QSizeF : {
        return _toString(value<QSizeF>());
    } break;
    case QMetaType::QPoint : {
        return _toString(value<QPoint>());
    } break;
    case QMetaType::QRegion : {
        return _toString(value<QRegion>());
    } break;
    }

    return _toString((QVariant)*this);
}

