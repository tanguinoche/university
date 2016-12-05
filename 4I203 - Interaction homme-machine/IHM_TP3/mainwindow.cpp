#include "mainwindow.h"
#include <QVBoxLayout>
#include <QScrollArea>
#include <QPushButton>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    QWidget *container = new QWidget(this);
    setCentralWidget(container);
    QVBoxLayout *vLayout = new QVBoxLayout();
    container->setLayout(vLayout);
    QHBoxLayout *hLayout = new QHBoxLayout();

    //Galerie de templates : ScrollArea contains Widget contains Layout
    QScrollArea *templateScroll = new QScrollArea();
    QWidget *templateWidget = new QWidget();
    QHBoxLayout *hTemplateLayout = new QHBoxLayout();
    templateWidget->setLayout(hTemplateLayout);
    templateScroll->setWidget(templateWidget);
    templateScroll->setWidgetResizable(true);

    vLayout->addWidget(templateScroll);
    vLayout->addLayout(hLayout);
    QPushButton *left = new QPushButton();
    QPushButton *right = new QPushButton();
    hLayout->addWidget(left);
    hLayout->addWidget(right);

    //Serie de boutons pour test le scroll
    QPushButton *first = new QPushButton();
    QPushButton *second = new QPushButton();
    QPushButton *third = new QPushButton();
    QPushButton *fourth = new QPushButton();
    QPushButton *fifth = new QPushButton();
    QPushButton *sixth = new QPushButton();
    QPushButton *seventh = new QPushButton();
    QPushButton *eighth = new QPushButton();
    hTemplateLayout->addWidget(first);
    hTemplateLayout->addWidget(second);
    hTemplateLayout->addWidget(third);
    hTemplateLayout->addWidget(fourth);
    hTemplateLayout->addWidget(fifth);
    hTemplateLayout->addWidget(sixth);
    hTemplateLayout->addWidget(seventh);
    hTemplateLayout->addWidget(eighth);
}

MainWindow::~MainWindow()
{

}
