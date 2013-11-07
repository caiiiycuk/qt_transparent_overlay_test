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

    pix = glWidget->grabFrameBuffer();
    glWidget->hide();
    repaint();
}

void PixmapWidget::paintEvent(QPaintEvent *event)
{
    QWidget::paintEvent(event);
    QPainter painter(this);
    painter.drawImage(0, 0, pix);
    painter.drawText(50, 50, "PixmapWidget");
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
    emit mouseReleased(event->pos());
    releaseMouse();

    glWidget->repaint();

    updatePixmap();

    foreach(const auto widget, transparentWidgets) {
        widget->show();
    }
}
