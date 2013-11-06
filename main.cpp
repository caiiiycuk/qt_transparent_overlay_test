#include "pixmapwidget.h"
#include "myglwidget.h"
#include "transparentwidget.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MyGLWidget* glWidget = new MyGLWidget;
    glWidget->resize(640, 480);
    glWidget->show();


    const auto transparentWidget = new TransparentWidget;
    transparentWidget->resize(300, 300);
    transparentWidget->show();


    PixmapWidget pixmapWidget;
    pixmapWidget.setGlWidget(glWidget);




    pixmapWidget.addTransparentWidget(transparentWidget);


    pixmapWidget.resize(300, 300);
    pixmapWidget.show();



//    QObject::connect(w2, SIGNAL(mouseReleased()), &w, SLOT(updatePixmap()));
    QObject::connect(&pixmapWidget, SIGNAL(mouseReleased(QPoint)), glWidget, SLOT(mouseRelease(QPoint)));
    QObject::connect(&pixmapWidget, SIGNAL(mousePressed(QPoint)), glWidget, SLOT(mousePress(QPoint)));
    QObject::connect(&pixmapWidget, SIGNAL(mouseMoved(QPoint)), glWidget, SLOT(mouseMove(QPoint)));

    return a.exec();
}
