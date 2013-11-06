#include "pixmapwidget.h"
#include "myglwidget.h"
#include "transparentwidget.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MyGLWidget* glWidget = new MyGLWidget;
//    glWidget->resize(640, 480);
//    glWidget->show();

    PixmapWidget pixmapWidget;
    pixmapWidget.setGlWidget(glWidget);

    const auto transparentWidget = new TransparentWidget(&pixmapWidget);
    //transparentWidget->resize(300, 300);
    //transparentWidget->show();


    pixmapWidget.addTransparentWidget(transparentWidget);

    pixmapWidget.resize(800, 800);
    pixmapWidget.show();

    QObject::connect(&pixmapWidget, SIGNAL(mousePressed(QPoint)), glWidget, SLOT(mousePress(QPoint)));
    QObject::connect(&pixmapWidget, SIGNAL(mouseMoved(QPoint)), glWidget, SLOT(mouseMove(QPoint)));

    return a.exec();
}
