#include "transparentwidget.h"

TransparentWidget::TransparentWidget(QWidget *parent) :
    QWidget(parent)
{
    setStyleSheet("* {"
                  "background: #ff0000;"
                  "}");
}
