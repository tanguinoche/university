#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTextEdit>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    void closeEvent (QCloseEvent *event);
    ~MainWindow();

private:
    QTextEdit *textEdit;
    bool textNeedsSave;
    bool continueOp();

private slots :
    void newFile();
    void openFile();
    void saveFile();
    void textChanged();
    void quit();

};


#endif // MAINWINDOW_H
