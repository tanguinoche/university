#include "QComboBoxColor.h"
#include <iostream>

QComboBoxColor::QComboBoxColor(QWidget *parent) :
    QComboBox(parent)
{



}

void QComboBoxColor::textChanged(const QString & text) {
    std::cout << qPrintable(text) <<" has been selected" << std::endl;
}


QComboBoxColor::~QComboBoxColor()
{


}


