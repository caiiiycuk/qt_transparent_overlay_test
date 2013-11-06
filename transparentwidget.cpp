#include "transparentwidget.h"
#include "movablewidget.h"
#include <QPainter>

TransparentWidget::TransparentWidget(QWidget *parent) :
    QWidget(parent)
{
//    setStyleSheet("* {"
//                  "background: #ff0000;"
//                  "}");
    //    setBackgroundRole(QPalette::);

//    setAttribute(Qt::WA_TransparentForMouseEvents);
//    setMouseTracking(false);
//    setFocusPolicy(Qt::NoFocus);
//    setAttribute(Qt::WA_StyleSheet);
    new MovableWidget("", this);
}

void TransparentWidget::paintEvent(QPaintEvent *event)
{
//    QPainter painter(this);
//    painter.setBrush(QColor(0, 255, 0));
//    painter.drawRect(rect());
//    QWidget::paintEvent(event);
}
