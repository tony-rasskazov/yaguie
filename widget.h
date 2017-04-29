#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

    Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged)

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

    QString name() const;
    void setName(const QString &name);

signals:
    void nameChanged();


private:
    Ui::Widget *ui;

    QString _name;
};

#endif // WIDGET_H
