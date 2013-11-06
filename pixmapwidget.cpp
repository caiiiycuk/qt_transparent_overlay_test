#include <QMouseEvent>
#include <QDebug>

#include "pixmapwidget.h"

PixmapWidget::PixmapWidget(QWidget *parent) :
    QWidget(parent), glWidget(0)
{
    setAttribute(Qt::WA_OpaquePaintEvent);
    setAttribute(Qt::WA_NoSystemBackground);
    mainLayout = new QStackedLayout(this);
    mainLayout->setStackingMode(QStackedLayout::StackAll);
    setLayout(mainLayout);
}

PixmapWidget::~PixmapWidget()
{
}

void PixmapWidget::addTransparentWidget(QWidget *newWidget) {
    mainLayout->addWidget(newWidget);
    transparentWidgets << newWidget;

    qDebug() << newWidget->styleSheet();
//    newWidget->setStyleSheet(newWidget->styleSheet());
//    newWidget->hide();
}

void PixmapWidget::setGlWidget(QGLWidget *newGlWidget) {
    mainLayout->removeWidget(glWidget);
    delete glWidget;
    mainLayout->insertWidget(0, newGlWidget);
    glWidget = newGlWidget;
}

void PixmapWidget::updatePixmap() {
    if (!glWidget) {
        return;
    }

    pix = QPixmap::fromImage(glWidget->grabFrameBuffer());
    glWidget->hide();
    update();
}

void PixmapWidget::paintEvent(QPaintEvent *event)
{
    {
        QPainter painter(this);
        painter.drawPixmap(0, 0, pix);
        painter.drawText(50, 50, "PixmapWidget");
    }
    QWidget::paintEvent(event);
}


void PixmapWidget::mousePressEvent(QMouseEvent *event)
{
    if (glWidget) {

        foreach(const auto widget, transparentWidgets) {
            widget->hide();
        }

        glWidget->show();
    }

    emit mousePressed(event->pos());
    grabMouse();
}

void PixmapWidget::mouseMoveEvent(QMouseEvent *event)
{
    emit mouseMoved(event->pos());
}

void PixmapWidget::mouseReleaseEvent(QMouseEvent *event) {
    updatePixmap();

    foreach(const auto widget, transparentWidgets) {
        widget->show();
        qDebug() << widget->size();
//        mainLayout->setCurrentWidget(widget);
    }
    emit mouseReleased(event->pos());
    releaseMouse();
}
