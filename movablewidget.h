#ifndef MOVABLEWIDGET_H
#define MOVABLEWIDGET_H

#include <QLabel>

class MovableWidget : public QLabel
{
    Q_OBJECT
public:
    explicit MovableWidget(const QString & text, QWidget * parent = 0, Qt::WindowFlags f = 0);
    
signals:
    
public slots:

protected:
    virtual void mousePressEvent(QMouseEvent *event);
    virtual void mouseMoveEvent(QMouseEvent *event);
    virtual void paintEvent(QPaintEvent*);

private:
    QPoint offset;
    
};

#endif // MOVABLEWIDGET_H
