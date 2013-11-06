#ifndef PIXMAPWIDGET_H
#define PIXMAPWIDGET_H

#include <QWidget>
#include <QStackedLayout>
#include <QVBoxLayout>
#include <QGLWidget>

class PixmapWidget : public QWidget
{
    Q_OBJECT

public:
    explicit PixmapWidget(QWidget *parent = 0);
    ~PixmapWidget();

    void addTransparentWidget(QWidget *);

    void setGlWidget(QGLWidget *);

public slots:
    void updatePixmap();

signals:
    void mouseReleased(QPoint);
    void mousePressed(QPoint);
    void mouseMoved(QPoint);

protected:
    virtual void paintEvent(QPaintEvent *);
    virtual void mousePressEvent(QMouseEvent *);
    virtual void mouseMoveEvent(QMouseEvent *);
    virtual void mouseReleaseEvent(QMouseEvent *);

private:
    QPixmap pix;
    QStackedLayout *mainLayout;
    QGLWidget *glWidget;
    QList<QWidget*> transparentWidgets;
};

#endif // PIXMAPWIDGET_H
