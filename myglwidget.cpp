#include "myglwidget.h"

#include <QtGui>
#include <QtOpenGL>

#include <math.h>

#include "qtlogo.h"

#ifndef GL_MULTISAMPLE
#define GL_MULTISAMPLE  0x809D
#endif

MyGLWidget::MyGLWidget(QWidget *parent)
    : QGLWidget(QGLFormat(), parent)
{
    logo = 0;
    xRot = 0;
    yRot = 0;
    zRot = 0;

    qtOne = QColor::fromRgb(255, 255, 255);
    qtTwo = QColor::fromRgb(0, 0, 0);

    setAttribute(Qt::WA_TransparentForMouseEvents);
    setMouseTracking(false);
    setFocusPolicy(Qt::NoFocus);
}

MyGLWidget::~MyGLWidget()
{
}

QSize MyGLWidget::minimumSizeHint() const
{
    return QSize(50, 50);
}

QSize MyGLWidget::sizeHint() const
{
    return QSize(400, 400);
}

static void qNormalizeAngle(int &angle)
{
    while (angle < 0)
        angle += 360 * 16;
    while (angle > 360 * 16)
        angle -= 360 * 16;
}

void MyGLWidget::setXRotation(int angle)
{
    qNormalizeAngle(angle);
    if (angle != xRot) {
        xRot = angle;
        emit xRotationChanged(angle);
        updateGL();
    }
}

void MyGLWidget::setYRotation(int angle)
{
    qNormalizeAngle(angle);
    if (angle != yRot) {
        yRot = angle;
        emit yRotationChanged(angle);
        updateGL();
    }
}

void MyGLWidget::setZRotation(int angle)
{
    qNormalizeAngle(angle);
    if (angle != zRot) {
        zRot = angle;
        emit zRotationChanged(angle);
        updateGL();
    }
}

void MyGLWidget::initializeGL()
{
    logo = new QtLogo(this, 64);

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glShadeModel(GL_SMOOTH);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

    static GLfloat lightPosition[4] = { 0.5, 5.0, 7.0, 1.0 };
    glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);
}

void MyGLWidget::paintGL()
{
    qglClearColor(qtOne);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    glTranslatef(0.0, 0.0, -10.0);
    glRotatef(xRot / 16.0, 1.0, 0.0, 0.0);
    glRotatef(yRot / 16.0, 0.0, 1.0, 0.0);
    glRotatef(zRot / 16.0, 0.0, 0.0, 1.0);

    logo->setColor(qtTwo);
    logo->draw();
}

void MyGLWidget::resizeGL(int width, int height)
{
    int side = qMin(width, height);
    glViewport((width - side) / 2, (height - side) / 2, side, side);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
#ifdef QT_OPENGL_ES_1
    glOrthof(-0.5, +0.5, -0.5, +0.5, 4.0, 15.0);
#else
    glOrtho(-0.5, +0.5, -0.5, +0.5, 4.0, 15.0);
#endif
    glMatrixMode(GL_MODELVIEW);
}

void MyGLWidget::setVisible(bool visible)
{
    if (visible) {
        qtOne.setRed(255 - qtOne.red());
        qtOne.setGreen(255 - qtOne.green());
        qtOne.setBlue(255 - qtOne.blue());

        qtTwo.setRed(255 - qtTwo.red());
        qtTwo.setGreen(255 - qtTwo.green());
        qtTwo.setBlue(255 - qtTwo.blue());
    }

    QGLWidget::setVisible(visible);
}

void MyGLWidget::mousePress(QPoint pos)
{
    lastPos = pos;
}

void MyGLWidget::mouseMove(QPoint pos)
{
    int dx = pos.x() - lastPos.x();
    int dy = pos.y() - lastPos.y();

    setXRotation(xRot + 8 * dy);
    setYRotation(yRot + 8 * dx);
    lastPos = pos;
}
