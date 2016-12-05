#ifndef QCOMBOBOXCOLOR_H
#define QCOMBOBOXCOLOR_H


#include <QComboBox>
#include <QHash>



class QComboBoxColor : public QComboBox
{
    Q_OBJECT

public:
    QComboBoxColor(QWidget *parent = 0);
    ~QComboBoxColor();


public slots :
    void textChanged(const QString & text);


};

#endif // QCOMBOBOXCOLOR_H
