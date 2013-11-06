#ifndef MYGLWIDGET_H
#define MYGLWIDGET_H

#include <QGLWidget>

class QtLogo;

//! [0]
class MyGLWidget : public QGLWidget
{
    Q_OBJECT

public:
    MyGLWidget(QWidget *parent = 0);
    ~MyGLWidget();

    QSize minimumSizeHint() const;
    QSize sizeHint() const;
//! [0]

//! [1]
public slots:
    void setXRotation(int angle);
    void setYRotation(int angle);
    void setZRotation(int angle);

    void mousePress(QPoint);
    void mouseMove(QPoint);
    void mouseRelease(QPoint);

signals:
    void xRotationChanged(int angle);
    void yRotationChanged(int angle);
    void zRotationChanged(int angle);

    void mouseReleased();
//! [1]

//! [2]
protected:
    void initializeGL();
    void paintGL();
    void resizeGL(int width, int height);

//! [2]

//! [3]
private:
    QtLogo *logo;
    int xRot;
    int yRot;
    int zRot;
    QPoint lastPos;
    QColor qtGreen;
    QColor qtPurple;
};
//! [3]


#endif // MYGLWIDGET_H
