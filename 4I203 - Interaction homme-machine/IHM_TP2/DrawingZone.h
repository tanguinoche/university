#ifndef DRAWINGZONE_H
#define DRAWINGZONE_H

#include <QWidget>
#include <QMouseEvent>
#include <QColor>
#include <QLine>
#include <QPen>

class DrawingZone : public QWidget
{
    Q_OBJECT

public:
    DrawingZone(QWidget *parent = 0);
    ~DrawingZone();

    void mousePressEvent( QMouseEvent* e);
    void mouseReleaseEvent( QMouseEvent* e);
    void mouseMoveEvent( QMouseEvent* e);
    void mouseDoubleClickEvent(QMouseEvent* e);
    void setPen(QPen *pen);

    QPen *pen;
    QPainterPath *path;
    QPainterPath *tmpPath;
    int initialX;
    int initialY;
    int finalX;
    int finalY;
    bool isDrawingSmthg;

    void setPainterPath(const QRect & value);

protected :
    bool isDragged;
    void paintEvent(QPaintEvent *e);

public slots :
    void chooseColor();
    void penSizeChanged(int i);
    void penStyleChanged(const QString& str);
    void penCapStyleChanged(const QString&);
    void penJoinStyleChanged(const QString&);
    void penShapeStyleChanged(const QString&);
    void undo();
    void redo();
    void clearAll();

private :
    QList<QPen> pens;
    QList<QPainterPath> paths;
    QVector<QPoint> *points;
    int indexList;

    QString curShape;
    QColor *curColor;
};

#endif // DRAWINGZONE_H
