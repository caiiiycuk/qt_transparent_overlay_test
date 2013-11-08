#include "movablewidget.h"
#include <QMouseEvent>
#include <cmath>
#include <QPainter>
#include <QPushButton>
#include <QWebView>

QColor GRADIENT_0(247, 247, 247);
QColor GRADIENT_1(218, 218, 218);

MovableWidget::MovableWidget(const QString & text, QWidget * parent, Qt::WindowFlags f) :
    QLabel(text, parent, f)
{
    setAttribute(Qt::WA_NoSystemBackground);
    resize(QSize(300, 300));

//    QPushButton * label = new QPushButton(this);
//    label->setText("AFJWKFLQWJFL");
    QWebView *webView = new QWebView(this);


    webView->resize(640, 480);
    webView->page()->settings()->setAttribute(QWebSettings::PluginsEnabled, true);
    webView->setUrl(QUrl("http://novokuznetsk.4geo.ru/3d/"));
    webView->show();
}


void MovableWidget::mousePressEvent(QMouseEvent *event)
{
    offset = event->pos();
    event->accept();
}

void MovableWidget::mouseMoveEvent(QMouseEvent *event)
{
    if(event->buttons() & Qt::LeftButton)
    {
        this->move(mapToParent(event->pos() - offset));
        event->accept();
    }
}

void MovableWidget::paintEvent(QPaintEvent*) {
    int shadow = 3;

    QPoint centerCard = rect().center();

    QPainterPath arrow;

    QPointF arrowTarget = rect().bottomRight();
    qreal arrowSize = 100;

    QRectF internalCard(QPointF(0, 0),
                        QSizeF(rect().size() - QSizeF(arrowSize, arrowSize)));

    qreal arrowGuideX1 = arrowTarget.x();
    qreal arrowGuideY1 = arrowTarget.y();

    qreal arrowGuideX2 = centerCard.x();
    qreal arrowGuideY2 = centerCard.y();

    qreal a = 90;
    if (arrowGuideX1 != arrowGuideX2) {
        qreal k = (arrowGuideY1 - arrowGuideY2) / (arrowGuideX1 - arrowGuideX2);
        a = atan(k) * 180 / M_PI;
    }

    arrow.moveTo(arrowTarget);
    arrow.lineTo(
                arrowGuideX2
                + 100
                * cos((a - 90) * (M_PI / 180)),
                arrowGuideY2
                + 100
                * sin((a - 90) * (M_PI / 180)));
    arrow.lineTo(
                arrowGuideX2
                + 100
                * cos((a + 90) * (M_PI / 180)),
                arrowGuideY2
                + 100
                * sin((a + 90) * (M_PI / 180)));
    arrow.lineTo(arrowTarget);

    QPainterPath path;

    path.setFillRule(Qt::WindingFill);
    path.addRoundedRect(internalCard.x(), internalCard.y(),
                        internalCard.width() - shadow, internalCard.height() - shadow,
                        5, 5,
                        Qt::AbsoluteSize);

    QPainterPath cardPath = path.united(arrow);

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.setRenderHint(QPainter::TextAntialiasing, true);
    painter.setRenderHint(QPainter::SmoothPixmapTransform, false);
    painter.setRenderHint(QPainter::NonCosmeticDefaultPen, false);

    painter.setCompositionMode(QPainter::CompositionMode_SourceOver);

    // shadow
    cardPath.translate(shadow, shadow);
    painter.fillPath(cardPath, QColor(255, 0, 0));
    cardPath.translate(-shadow, -shadow);

    painter.setPen(QColor(0, 0, 0));
    painter.fillPath(cardPath, QColor(255, 255, 255));

    QPainterPath topPath;
    topPath.addRect(internalCard.x(), internalCard.y(),
                    internalCard.width() - shadow, 19);
    topPath = path.intersected(topPath);
    painter.fillPath(topPath, QColor(127, 127, 127));

    QLinearGradient gradient(internalCard.x(), internalCard.y() + 19,
                             internalCard.x(), internalCard.y() + 19 + 23);
    gradient.setColorAt(0, GRADIENT_0);
    gradient.setColorAt(1, GRADIENT_1);

    QPainterPath top2Path;
    top2Path.addRect(internalCard.x(), internalCard.y() + 19,
                     internalCard.width() - shadow, 23);
    top2Path = path.intersected(top2Path);
    painter.fillPath(top2Path, QBrush(gradient));

    painter.drawPath(cardPath);
}
