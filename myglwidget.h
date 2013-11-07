#ifndef MYGLWIDGET_H
#define MYGLWIDGET_H

#include <QGLWidget>

class QtLogo;

class MyGLWidget : public QGLWidget
{
    Q_OBJECT

public:
    MyGLWidget(QWidget *parent = 0);
    ~MyGLWidget();

    QSize minimumSizeHint() const;
    QSize sizeHint() const;

public slots:
    void setXRotation(int angle);
    void setYRotation(int angle);
    void setZRotation(int angle);

    void mousePress(QPoint);
    void mouseMove(QPoint);

signals:
    void xRotationChanged(int angle);
    void yRotationChanged(int angle);
    void zRotationChanged(int angle);

protected:
    void initializeGL();
    void paintGL();
    void resizeGL(int width, int height);

    void setVisible(bool visible);

private:
    QtLogo *logo;
    int xRot;
    int yRot;
    int zRot;
    QPoint lastPos;
    QColor qtOne;
    QColor qtTwo;
};


#endif // MYGLWIDGET_H
