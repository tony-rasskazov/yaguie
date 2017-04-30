#include "varianthelper.h"

#include <QRect>
#include <QVariant>


template< typename T >
T unpack( const QVariant& var, const T& defVal = T() ) {
    if( var.isValid() && var.canConvert< T >() ) {
        return var.value< T >();
    }
    return defVal;
}

/*
VariantHelper::VariantHelper(const QVariant &variant)
    :QVariant(variant)
{

}
*/

template <>
QString exVariantToString(QRect v) {
    return QString("(%1, %2, %3, %4)").arg(v.x()).arg(v.y()).arg(v.width()).arg(v.height());
}

template <>
QString exVariantToString(QVariant v) {
    return v.toString();
}

QString VariantHelper::toString() const
{
    return exVariantToString(value<QVariant>());
}
