#include "propmodel.h"

#include <QList>
#include <QVariant>

#include <QMetaProperty>

#include <QDebug>

#define RANGE(i, min, max) (i <= min) || (i >= max) ? 1 : 0

PropModel::PropModel(QObject *target, QObject *parent)
    : QAbstractItemModel(parent)
    , _obj(target)
{
}

QVariant PropModel::headerData(int section, Qt::Orientation orientation, int role) const
{

    if (role != Qt::DisplayRole || orientation != Qt::Horizontal) return QVariant();

//    qDebug() << "PropModel::headerData" << section << role << orientation;

    QList<QVariant> h;
    h << "name" << "value" << "type";
    return h.at(section);
}

QModelIndex PropModel::index(int row, int column, const QModelIndex &parent) const
{
//    qDebug() << "PropModel::index" << row << column << parent;

    //if ( !(RANGE(column, 0, 2)) )
    if (column < 0 || column > 2 )
        return QModelIndex();

    auto mo = _obj->metaObject();

    //if ( !RANGE(row, 0, mo->propertyCount() - 1) )
    if (row < 0 || row > mo->propertyCount() - 1)
        return QModelIndex();


//    qDebug() << "PropModel::index createIndex" << row << column << parent;
    return createIndex(row, column, row);
}

QModelIndex PropModel::parent(const QModelIndex &index) const
{
//    qDebug() << "PropModel::parent" << index;
    return QModelIndex();
}

int PropModel::rowCount(const QModelIndex &parent) const
{
    qDebug() << "PropModel::rowCount" << parent;

    if (!parent.isValid()) {
        auto mo = _obj->metaObject();
        return mo->propertyCount();
    } else {
        return 0;
    }
}

int PropModel::columnCount(const QModelIndex &parent) const
{
//    qDebug() << "PropModel::columnCount" << parent;

//    if (!parent.isValid())
//        return 0;

    return 3;
}

QVariant PropModel::data(const QModelIndex &index, int role) const
{
//    qDebug() << "PropModel::data" << index;

    if (!index.isValid())
        return QVariant();

    if (role != Qt::DisplayRole && role != Qt::EditRole)
        return QVariant();

    //if ( !RANGE(index.column(), 0, 2) )
    //    return QVariant();

    auto mo = _obj->metaObject();

    //if ( !RANGE(index.row(), 0, mo->propertyCount()) )
    //    return QVariant();

    switch (index.column()) {
    case 0:
        return mo->property(index.row()).name();
        break;
    case 1:
        return mo->property(index.row()).read(this);
        break;
    case 2:
        return mo->property(index.row()).typeName();
        break;
    }
    return QVariant();
}

bool PropModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
//    qDebug() << "PropModel::setData";
    if (data(index, role) != value) {
        // FIXME: Implement me!
        emit dataChanged(index, index, QVector<int>() << role);
        return true;
    }
    return false;
}

Qt::ItemFlags PropModel::flags(const QModelIndex &index) const
{
//    qDebug() << "PropModel::flags" << index;
    if (!index.isValid())
        return Qt::NoItemFlags;

    return Qt::ItemIsSelectable;// Editable; // FIXME: Implement me!
}
