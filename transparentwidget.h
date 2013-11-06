#ifndef TRANSPARENTWIDGET_H
#define TRANSPARENTWIDGET_H

#include <QWidget>

class TransparentWidget : public QWidget
{
    Q_OBJECT
public:
    explicit TransparentWidget(QWidget *parent = 0);

signals:

public slots:

protected:
    virtual void paintEvent(QPaintEvent *);

};

#endif // TRANSPARENTWIDGET_H
