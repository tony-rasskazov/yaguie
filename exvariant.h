#ifndef EXVARIANT_H
#define EXVARIANT_H

#include <QVariant>

class ExVariant : public QVariant
{
public:
    ExVariant();
    ExVariant(const QVariant& orig);

    QString toString() const;
};

#endif // EXVARIANT_H
