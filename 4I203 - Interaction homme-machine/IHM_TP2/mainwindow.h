#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include "DrawingZone.h"
#include <QColor>
#include<QComboBox>
#include <QPen>
#include <QPushButton>
#include <QLabel>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private :
    DrawingZone *drawingZone;
    QSlider *penSize;
    QPen *pen;
    void toolBar();

};

#endif // MAINWINDOW_H
