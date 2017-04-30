#ifndef VARIANTHELPER_H
#define VARIANTHELPER_H

#include <QVariant>

class VariantHelper : public QVariant
{
public:
    //VariantHelper(const QVariant& variant);

    QString toString() const;

};

template <typename T>
QString exVariantToString(T v);


#endif // VARIANTHELPER_H
