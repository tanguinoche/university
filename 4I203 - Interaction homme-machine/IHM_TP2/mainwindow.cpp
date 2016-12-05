#include "mainwindow.h"
#include "Transitions.h"
#include <QPushButton>
#include <QtGui>
#include <QLabel>
#include <QComboBox>
#include <QDebug>
#include <QMenuBar>
#include <QAction>
#include <QToolBar>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{


    //Initiaize DrawingZone
    drawingZone = new DrawingZone(this);
    toolBar();

    //Pen Width
    QLabel *labelWidth = new QLabel("width :");
    penSize = new QSlider(Qt::Horizontal, this);
    penSize->setRange(1, 99);
    penSize->setValue(1);

    //Pen Style
    QLabel *labelStyle = new QLabel("style :");
    QComboBox *comboStyle = new QComboBox(this);
    comboStyle->addItem("Solid Line");
    comboStyle->addItem("Dash Line");
    comboStyle->addItem("Dot Line");
    comboStyle->addItem("Dash Dot Line");
    comboStyle->addItem("Dash Dot Dot Line");

    //Pen Cap Style
    QLabel *labelCapStyle = new QLabel("cap style :");
    QComboBox *comboCapStyle = new QComboBox(this);
    comboCapStyle->addItem("Square Cap");
    comboCapStyle->addItem("Flat Cap");
    comboCapStyle->addItem("Round Cap");

    //Pen Join Style
    QLabel *labelJoinStyle = new QLabel("join style :");
    QComboBox *comboJoinStyle = new QComboBox(this);
    comboJoinStyle->addItem("Bevel Join");
    comboJoinStyle->addItem("Miter Join");
    comboJoinStyle->addItem("Round Join");

    //QPainterPath Shape
    QLabel *labelShapeStyle = new QLabel("Shape style :");
    QComboBox *comboShapeStyle = new QComboBox(this);
    comboShapeStyle->addItem("Rectangle");
    comboShapeStyle->addItem("Ellipse");
    comboShapeStyle->addItem("Circle");
    comboShapeStyle->addItem("Polyline");
    comboShapeStyle->addItem("Polygone");
    comboShapeStyle->addItem("Line");


    //Undo redo ClearAll
    QPushButton *undo = new QPushButton("Undo");
    QPushButton *redo = new QPushButton("Redo");
    QPushButton *clearAll = new QPushButton("Clear All");
    //Create Window, layouts
    QWidget *window = new QWidget(this);
    QVBoxLayout * v_layout = new QVBoxLayout( );

    v_layout->addWidget(labelWidth);
    v_layout->addWidget(penSize);
    //v_layout->addWidget(labelColor);
    //v_layout->addWidget(comboColor);
    v_layout->addWidget(labelStyle);
    v_layout->addWidget(comboStyle);
    v_layout->addWidget(labelCapStyle);
    v_layout->addWidget(comboCapStyle);
    v_layout->addWidget(labelJoinStyle);
    v_layout->addWidget(comboJoinStyle);
    v_layout->addWidget(labelShapeStyle);
    v_layout->addWidget(comboShapeStyle);
    v_layout->addWidget(undo);
    v_layout->addWidget(redo);
    v_layout->addWidget(clearAll);

    v_layout->addStretch();
    QHBoxLayout * h_layout = new QHBoxLayout( );

    h_layout->addWidget(drawingZone);
    h_layout->addLayout(v_layout);
    window->setLayout(h_layout);
    setCentralWidget(window);

   //Connect widgets
   QObject::connect(penSize, SIGNAL(valueChanged(int)), drawingZone, SLOT(penSizeChanged(int)));
   //QObject::connect(comboColor, SIGNAL(currentIndexChanged(QString)), drawingZone, SLOT(penColorChanged(const QString&)));
   QObject::connect(comboStyle, SIGNAL(currentIndexChanged(QString)), drawingZone, SLOT(penStyleChanged(const QString&)));
   QObject::connect(comboCapStyle, SIGNAL(currentIndexChanged(QString)), drawingZone, SLOT(penCapStyleChanged(const QString&)));
   QObject::connect(comboJoinStyle, SIGNAL(currentIndexChanged(QString)), drawingZone, SLOT(penJoinStyleChanged(const QString&)));
   QObject::connect(comboShapeStyle, SIGNAL(currentIndexChanged(QString)), drawingZone, SLOT(penShapeStyleChanged(const QString&)));
   QObject::connect(undo, SIGNAL(clicked()), drawingZone, SLOT(undo()));
   QObject::connect(redo, SIGNAL(clicked()), drawingZone, SLOT(redo()));
   QObject::connect(clearAll, SIGNAL(clicked()), drawingZone, SLOT(clearAll()));

}

void MainWindow::toolBar() {

    QMenuBar *menuBar = this->menuBar();
    QMenu *fileMenu = menuBar->addMenu(tr("&File"));


    QAction *newF = new QAction(QIcon(":/img/new.png"), tr("&New"), this);
    newF->setShortcut(tr("Ctrl+N"));
    newF->setToolTip(tr("New File"));
    fileMenu->addAction(newF);
    //connect(newF, SIGNAL(triggered()), this, SLOT(newF()));


    QAction *open = new QAction(QIcon(":/img/open.png"), tr("&Open"), this);
    open->setShortcut(tr("Ctrl+O"));
    open->setToolTip(tr("Open File"));
    fileMenu->addAction(open);
    //connect(open, SIGNAL(triggered()), this, SLOT(open()));

    QAction *save = new QAction(QIcon(":/img/save.png"), tr("&Save"), this);
    save->setShortcut(tr("Ctrl+S"));
    save->setToolTip(tr("Save File"));
    fileMenu->addAction(save);
    //connect(save, SIGNAL(triggered()), this, SLOT(save()));

    QAction *pen = new QAction(QIcon(":/img/pen_line.png"), tr("&Pen"), this);
    pen->setToolTip(tr("Set pen"));
    fileMenu->addAction(pen);

    QAction *brush = new QAction(QIcon(":/img/brush_line.png"), tr("&Brush"), this);
    brush->setToolTip(tr("Set brush"));
    fileMenu->addAction(brush);

    QAction *color = new QAction(QIcon(":/img/color_picker.png"), tr("&Color Picker"), this);
    color->setToolTip(tr("Set color"));
    fileMenu->addAction(color);
    connect(color, SIGNAL(triggered()), drawingZone, SLOT(chooseColor()));

    QToolBar* newToolBar = addToolBar(tr("New"));
    newToolBar->addAction(newF);
    QToolBar* openToolBar = addToolBar(tr("Open"));
    openToolBar->addAction(open);
    QToolBar* saveToolBar = addToolBar(tr("Save"));
    saveToolBar->addAction(save);
    QToolBar* penToolBar = addToolBar(tr("Pen"));
    penToolBar->addAction(pen);
    QToolBar* brushToolBar = addToolBar(tr("Brush"));
    brushToolBar->addAction(brush);
    QToolBar* colorToolBar = addToolBar(tr("Color Picker"));
    colorToolBar->addAction(color);
}



MainWindow::~MainWindow()
{

}
