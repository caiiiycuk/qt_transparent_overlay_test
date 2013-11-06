#include <QMouseEvent>
#include <QDebug>

#include "pixmapwidget.h"

PixmapWidget::PixmapWidget(QWidget *parent) :
    QWidget(parent), glWidget(0)
{
//    setAttribute(Qt::WA_OpaquePaintEvent);
//    setAttribute(Qt::WA_NoSystemBackground);
    layout = new QVBoxLayout;
//    layout->setStackingMode(QStackedLayout::StackAll);
    setLayout(layout);
}

PixmapWidget::~PixmapWidget()
{
}

void PixmapWidget::addTransparentWidget(QWidget *newWidget) {
//    layout->addWidget(newWidget);

    layout->insertWidget(0, newWidget);

//    newWidget->show();
//    newWidget->raise();
    //transparentWidgets << newWidget;
    //newWidget->hide();
}

void PixmapWidget::setGlWidget(QGLWidget *newGlWidget) {
//    layout->removeWidget(glWidget);
    delete glWidget;
//    layout->insertWidget(0, newGlWidget);
    glWidget = newGlWidget;
}

void PixmapWidget::updatePixmap() {
    if (!glWidget) {
        return;
    }

    pix = QPixmap::fromImage(glWidget->grabFrameBuffer());
//    glWidget->hide();
    update();
}

void PixmapWidget::paintEvent(QPaintEvent *event)
{
//    {QPainter painter(this);
//    painter.drawPixmap(0, 0, pix);
//    painter.drawText(50, 50, "PixmapWidget");
//    }
    QWidget::paintEvent(event);
}


void PixmapWidget::mousePressEvent(QMouseEvent *event)
{
//    if (glWidget) {

//        foreach(const auto widget, transparentWidgets) {
//            //widget->hide();
//        }

//        glWidget->show();
//    }

    emit mousePressed(event->pos());
}
//! [9]

//! [10]
void PixmapWidget::mouseMoveEvent(QMouseEvent *event)
{
    emit mouseMoved(event->pos());
}

void PixmapWidget::mouseReleaseEvent(QMouseEvent *event) {
    updatePixmap();

//    foreach(const auto widget, transparentWidgets) {
//        widget->show();
//        qDebug() << widget->size();
//        layout->setCurrentWidget(widget);
//    }
    emit mouseReleased(event->pos());
}
