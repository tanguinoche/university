#include "DrawingZone.h"

#include <QPainter>
#include <QPen>
#include <QDebug>
#include <QColorDialog>


DrawingZone::DrawingZone(QWidget *parent) :
    QWidget(parent)
{
setMinimumSize(800,600);
initialX=0;
initialY=0;
finalX=0;
finalY=0;
indexList = 0;
isDragged=false;
isDrawingSmthg=false;
setMouseTracking(true);

curShape = "Rectangle";
curColor = new QColor(Qt::black);
pen = new QPen(*curColor, 1, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);
path = new QPainterPath();
tmpPath = new QPainterPath();
points = new QVector<QPoint>();

}

void DrawingZone::paintEvent(QPaintEvent *) {
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    int i;
    for(i=0; i<indexList; i++) {
         painter.setPen(pens.at(i));
         painter.drawPath(paths.at(i));
     }



    if(isDragged==true) {
        painter.setPen(*pen);
        painter.drawPath(*path);
        painter.drawPath(*tmpPath);
    }
}


void DrawingZone::mousePressEvent( QMouseEvent* e) {
    if (e->button() == Qt::LeftButton && isDrawingSmthg==false){
        isDragged=true;
        initialX = e->x();
        initialY = e->y();
        //Dans les cas où on ne bouge pas la souris, on aimerait ne rien voir :
        finalX = initialX;
        finalY = initialY;
        if(curShape.compare("Polyline")==0 || curShape.compare("Polygone")==0) {
            isDrawingSmthg=true;
        }

     }
    update();
}

void DrawingZone::mouseMoveEvent( QMouseEvent* e){
    if (isDragged==true){
        finalX = e->x();
        finalY = e->y();

        if(curShape.compare("Polyline")==0 || curShape.compare("Polygone")==0) {
           free(tmpPath);
           tmpPath = new QPainterPath();
           tmpPath->moveTo(initialX, initialY);
           tmpPath->lineTo(finalX, finalY);
        }else {
            free(path);
            path = new QPainterPath();
            if(curShape.compare("Rectangle")==0) {
                path->addRect(initialX, initialY, finalX-initialX, finalY-initialY);
            } else if(curShape.compare("Ellipse")==0) {
                path->addEllipse(initialX, initialY, finalX-initialX, finalY-initialX);
            } else if(curShape.compare("Line")==0) {
                path->moveTo(initialX, initialY);
                path->lineTo(finalX, finalY);
            } else { //Circle
                path->addEllipse(initialX, initialY, finalX-initialX, finalX-initialX);
            }
        }
        update();
     }
 }

void DrawingZone::mouseReleaseEvent( QMouseEvent* e){
    if (e->button() == Qt::LeftButton){

        finalX = e->x();
        finalY = e->y();

        //Maj liste si o a fait un undo, et qu'on redessine autre chose
        for(int i = paths.size(); i > indexList ; i--) {
            paths.removeLast();
            pens.removeLast();
        }
        if(curShape.compare("Polyline")==0 && isDrawingSmthg==true) {
            path->moveTo(initialX, initialY);
            path->lineTo(finalX, finalY);
            initialX = finalX;
            initialY = finalY;
        }else if(curShape.compare("Polygone")==0 && isDrawingSmthg==true) {
            path->moveTo(initialX, initialY);
            path->lineTo(finalX, finalY);
            initialX = finalX;
            initialY = finalY;
            QPoint *p = new QPoint(initialX, initialY);
            qDebug() << "on ajoute "<<*p;
            points->append(*p);
        }else {
            isDragged=false;
            //Ajout elem
            indexList++;
            QPen newPen = *pen;
            pens << newPen;
            QPainterPath newPath = *path;
            paths << newPath;
            free(path);
            path = new QPainterPath();
            pen = new QPen(*pen);
        }

        update();
     }
 }

void DrawingZone::mouseDoubleClickEvent(QMouseEvent*) {
    //Ajout elem
    indexList++;
    if(curShape.compare("Polyline")==0) {
        path->moveTo(initialX, initialY);
        path->lineTo(finalX, finalY);
        QPen newPen = *pen;
        pens << newPen;
        QPainterPath newPath = *path;
        paths << newPath;
        isDrawingSmthg=false;
        isDragged=false;
        free(path);
        path = new QPainterPath();
        pen = new QPen(*pen);
    }
    if(curShape.compare("Polygone")==0) {
        QPen newPen = *pen;
        pens << newPen;
        points->append(QPoint(finalX, finalY));
        QPainterPath *newPath = new QPainterPath();
        QPolygon *polygon = new QPolygon(*points);
        newPath->addPolygon(*polygon);
        newPath->closeSubpath();
        qDebug() <<"hellooo";
        paths << *newPath;
        isDrawingSmthg=false;
        isDragged=false;
        path = new QPainterPath();
        pen = new QPen(*pen);
        points = new QVector<QPoint>();
    }
    update();
}


void DrawingZone::chooseColor() {
    QColor color = QColorDialog::getColor();
    if(color.isValid()) {
        free(curColor);
        curColor = new QColor(color);
        pen->setColor(*curColor);
        qDebug() << curColor;
    }
}

void DrawingZone::penSizeChanged(int i) {
    pen->setWidth(i);
}

void DrawingZone::penStyleChanged(const QString& str) {
    if(str.compare("Solid Line")==0) {
        pen->setStyle(Qt::SolidLine);
    }else if(str.compare("Dash Line")==0) {
        pen->setStyle(Qt::DashLine);
    }else if(str.compare("Dot Line")==0) {
        pen->setStyle(Qt::DotLine);
    }else if(str.compare("Dash Dot Line")==0) {
        pen->setStyle(Qt::DashDotLine);
    }else{ //Dash Dot Dot Line
        pen->setStyle(Qt::DashDotDotLine);
    }
}

void DrawingZone::penCapStyleChanged(const QString& str) {
    if(str.compare("Square Cap")==0) {
        pen->setCapStyle(Qt::SquareCap);
    }else if(str.compare("Flat Cap")==0) {
        pen->setCapStyle(Qt::FlatCap);
    }else {//Round Cap
        pen->setCapStyle(Qt::RoundCap);
    }
}

void DrawingZone::penJoinStyleChanged(const QString& str) {
    if(str.compare("Bevel Join")==0) {
        pen->setJoinStyle(Qt::BevelJoin);
    }else if(str.compare("Miter Join")==0) {
        pen->setJoinStyle(Qt::MiterJoin);
    }else {//Round Join
        pen->setJoinStyle(Qt::RoundJoin);
    }
}

void DrawingZone::penShapeStyleChanged(const QString& str) {
    curShape = str;
}

void DrawingZone::undo() {
    if(indexList>0) { indexList--; }
    update();
}

void DrawingZone::redo() {
    if(indexList<paths.size()) { indexList++; }
    update();
}

void DrawingZone::clearAll() {

    //On n'a pas nettoyé la mémoire des objets ??
    indexList=0;
    pens.clear();
    paths.clear();
    update();
}

void DrawingZone::setPainterPath(const QRect & value) {
    path->addRect(value);
}

DrawingZone::~DrawingZone()
{

}
