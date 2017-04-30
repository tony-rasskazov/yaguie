#include "widget.h"
#include "ui_widget.h"

#include <QDebug>
#include <QMetaProperty>

#include <vector>
#include <utility>
#include <algorithm>

#include "propmodel.h"
#include "propertydelegate.h"

static void dump_props(QObject *o)
{
  auto mo = o->metaObject();

  auto dpn = o->dynamicPropertyNames();
  qDebug() << "# Dynamic properties of" << o << "#";
  for (auto &pn: dpn) {
      qDebug() << pn;
  }


  qDebug() << "## Properties of" << o << "##";
  do {
    qDebug() << "### Class" << mo->className() << "###";
    std::vector<std::pair<QString, QVariant> > v;

    v.reserve(mo->propertyCount() - mo->propertyOffset());
//    v.reserve(mo->propertyCount());

    //for (int i = 0; i < mo->propertyCount(); ++i) {
    for (int i = mo->propertyOffset(); i < mo->propertyCount(); ++i) {
        v.emplace_back(mo->property(i).name(), mo->property(i).read(o));
    }

    std::sort(v.begin(), v.end());

    for (auto &i : v) {
        qDebug() << i.first << "=>" << i.second;
    }
  } while ((mo = mo->superClass()));
}

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    setProperty("Yarrr", 100500);
    dump_props(this);

    ui->tableView->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);

    ui->tableView->setItemDelegate(new PropertyDelegate(ui->tableView));

    ui->tableView->setModel(new PropModel(this, ui->tableView));
}

Widget::~Widget()
{
    delete ui;
}

QString Widget::name() const
{
    return _name;
}

void Widget::setName(const QString &name)
{
    _name = name;
}

