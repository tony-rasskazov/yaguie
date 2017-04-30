#include "propmodel.h"

#include <QList>
#include <QVariant>

#include <QMetaProperty>

#include <QDebug>

#include "exvariant.h"

#define RANGE(i, min, max) (i <= min) || (i >= max) ? 1 : 0

PropModel::PropModel(QObject *target, QObject *parent)
    : QAbstractItemModel(parent)
    , _obj(target)
{
    _headers << "name" << "value" << "typeName" << "typeId" << "flags" << "revision";

}

QVariant PropModel::headerData(int section, Qt::Orientation orientation, int role) const
{

    if (role != Qt::DisplayRole || orientation != Qt::Horizontal) return QVariant();

    return _headers.at(section);
}

QModelIndex PropModel::index(int row, int column, const QModelIndex &parent) const
{
//    qDebug() << "PropModel::index" << row << column << parent;

    //if ( !(RANGE(column, 0, 2)) )
//    if (column < 0 || column > 2 )
//        return QModelIndex();

    auto mo = _obj->metaObject();

    //if ( !RANGE(row, 0, mo->propertyCount() - 1) )
    if (row < 0 || row > mo->propertyCount() - 1)
        return QModelIndex();


//    qDebug() << "PropModel::index createIndex" << row << column << parent;
    return createIndex(row, column);
}

QModelIndex PropModel::parent(const QModelIndex &index) const
{
//    qDebug() << "PropModel::parent" << index;
    return QModelIndex();
}

int PropModel::rowCount(const QModelIndex &parent) const
{
//    qDebug() << "PropModel::rowCount" << parent;

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

    return _headers.count();
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

    QMetaProperty mp = mo->property(index.row());

    switch (index.column()) {
    case 0:
        return mp.name();
        break;
    case 1: {

        return QVariant(mp.read(_obj));
//        return ExVariant(mp.read(_obj)).toString();
        //return _obj->property(mp.name());
    } break;
    case 2:
        return mp.typeName();
        break;
    case 3:
        return (uint)mp.type();
        break;
    case 4: {
        QString flags;

        flags += mp.isConstant() ? "C" : "";
        flags += mp.isDesignable() ? "D" : "";
        flags += mp.isEditable() ? "E" : "";
        flags += mp.isEnumType() ? "e" : "";
        flags += mp.isFinal() ? "F" : "";
        flags += mp.isFlagType() ? "f" : "";
        flags += mp.isReadable() ? "R" : "";
        flags += mp.isResettable() ? "r" : "";
        flags += mp.isScriptable() ? "S" : "";
        flags += mp.isStored() ? "s" : "";
        flags += mp.isUser() ? "U" : "";
        flags += mp.isValid() ? "V" : "";
        flags += mp.isWritable() ? "W" : "";
        flags += mp.read(_obj).isNull() ? "N" : "";

        return flags;

    } break;
    case 5:
        return mp.revision();
        break;
    default:
        return QVariant();
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

    Qt::ItemFlags flags = Qt::ItemIsSelectable | Qt::ItemIsEnabled;


    if (index.column() == 1)
        flags |= Qt::ItemIsEditable;
    return flags;
}
