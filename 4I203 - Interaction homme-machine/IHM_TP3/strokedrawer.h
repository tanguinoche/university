#ifndef STROKEDRAWER_H
#define STROKEDRAWER_H

#include <QPolygonF>
#include <QPainter>
#include <QWidget>
#include <qmath.h>
#include "QPen"


class StrokeDrawer : public QWidget
{
public:
    StrokeDrawer();
    QPolygonF getStroke();
    void setStroke(QPolygonF);
    void clearStroke();
    void paintEvent(QPaintEvent*);
    QSize sizeHint() const;
    QSize minimumSizeHint() const;

private:
    QPolygonF gesture;
};

#endif // STROKEDRAWER_H
