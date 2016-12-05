#include "strokedrawer.h"

StrokeDrawer::StrokeDrawer()
{
}

QPolygonF StrokeDrawer::getStroke() {
    return this->gesture;
}

void StrokeDrawer::setStroke(QPolygonF gesture) {
    this->gesture = gesture;
}



void StrokeDrawer::clearStroke() {
  this->gesture = QPolygonF();
}

void StrokeDrawer::paintEvent(QPaintEvent * paintEvent) {
    QPen pen;
    pen.setWidth(2);
    pen.setColor(Qt::blue);
    pen.setStyle(Qt::SolidLine);
    QWidget::paintEvent(paintEvent);
    QPainter painter(this);
    painter.setPen(pen);
    painter.drawPolyline(this->gesture);
}

QSize StrokeDrawer::sizeHint() const {
  QRectF r = (this->gesture).boundingRect();
  int max = qMax(r.width(),r.height());
  return QSize(max,max);
}

QSize StrokeDrawer::minimumSizeHint() const {
  QRectF r = this->gesture.boundingRect();
  int max = qMax(r.width(),r.height());
  return QSize(max,max);
}
