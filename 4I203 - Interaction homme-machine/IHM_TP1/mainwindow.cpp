#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QFileDialog>
#include <QTextStream>
#include <QMessageBox>
#include <QCloseEvent>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{

    QMenuBar *menuBar = this->menuBar();
    QMenu *fileMenu = menuBar->addMenu(tr("&File"));

    /*NOUVEAU FICHIER*/
    QAction *newf = new QAction(QIcon(":/images/new.png"), tr("&New"), this);
    newf->setShortcut(tr("Ctrl+N"));
    newf->setToolTip(tr("New File"));
    fileMenu->addAction(newf);
    connect(newf, SIGNAL(triggered()), this, SLOT(newFile()));
    QToolBar* newToolBar = addToolBar(tr("File"));
    newToolBar->addAction(newf);

    /*OUVRIR FICHIER*/
    QAction *open = new QAction(QIcon(":/images/open.png"), tr("&Open"), this);
    open->setShortcut(tr("Ctrl+O"));
    open->setToolTip(tr("Open File"));
    fileMenu->addAction(open);
    connect(open, SIGNAL(triggered()), this, SLOT(openFile()));
    QToolBar* openToolBar = addToolBar(tr("File"));
    openToolBar->addAction(open);

    /*SAUVEGARDER FICHIER*/
    QAction *save = new QAction(QIcon(":/images/save.png"), tr("&Save"), this);
    save->setShortcut(tr("Ctrl+S"));
    save->setToolTip(tr("Save File"));
    fileMenu->addAction(save);
    connect(save, SIGNAL(triggered()), this, SLOT(saveFile()));
    QToolBar* saveToolBar = addToolBar(tr("Save"));
    saveToolBar->addAction(save);

    /*QUITTER APPLICATION*/
    QAction *quit = new QAction(QIcon(":/images/quit.png"), tr("&Quit"), this);
    quit->setShortcut(tr("Ctrl+Q"));
    quit->setToolTip(tr("Quit App"));
    fileMenu->addAction(quit);
    connect(quit, SIGNAL(triggered()), this, SLOT(quit()));
    QToolBar* quitToolBar = addToolBar(tr("Quit"));
    quitToolBar->addAction(quit);

    /*EDITEUR DE TEXTE*/
    textEdit = new QTextEdit(this);
    connect(textEdit, SIGNAL(textChanged()), this, SLOT(textChanged()));
    textNeedsSave=false;
    setCentralWidget(textEdit);


}

MainWindow::~MainWindow()
{

}

//Problème : Le signal textChanged est émit lors de plusieurs évènements comme la modification de la taille de la fenêtre..
void MainWindow::textChanged() {
    qDebug() << "signal textChanged emitted" <<endl;
    textNeedsSave=true;
}
bool MainWindow::continueOp() {
    if(textNeedsSave==true) {
        QMessageBox msgBox;
        msgBox.setText("Vos modifications n'ont pas été enregistrées.");
        msgBox.setInformativeText("Abandonner les modifications en cours et ouvrir un nouveau fichier ?");
        msgBox.setStandardButtons(QMessageBox::Cancel | QMessageBox::Save | QMessageBox::Ok);
        msgBox.setDefaultButton(QMessageBox::Save);
        int retVal = msgBox.exec();
        if(retVal==QMessageBox::Ok) {
            textNeedsSave=false;
            return true;
        } else if(retVal==QMessageBox::Save) {
            saveFile();
            textNeedsSave=false;
            return true;
        } else { //Cancel
            return false;
        }
    } else { //No need to save, no changes.
        return true;
    }
}

void MainWindow::newFile() {
    if(continueOp()==true) {
        textEdit->clear();
    }

}

void MainWindow::openFile() {
    if(continueOp()==true) {
        QString fileName =
         QFileDialog::getOpenFileName( this,
         tr("Open Html file"),           // titre
         "/home/",            // répertoire initial
         tr("HTML Files (*.htm *.html)") // filtre
         );
        QFile file(fileName);
        file.open(QIODevice::ReadOnly | QIODevice::Text);
        QTextStream stream(&file);
        QString line = stream.readAll();
        textEdit->setHtml(line);
        file.close();
    }
}

void MainWindow::saveFile() {
    QString fileName =
     QFileDialog::getSaveFileName( this,
     tr("Save Html file"),           // titre
     "/home/",            // répertoire initial
     tr("HTML Files (*.htm *.html)") // filtre
     );
     QFile file(fileName);
     file.open(QIODevice::WriteOnly | QIODevice::Text);
     file.write(qPrintable(textEdit->toHtml()));
     file.close();
     textNeedsSave=false;
}

void MainWindow::quit() {
    QMessageBox msgBox;
    msgBox.setText("Vous allez quitter l'application");
    msgBox.setInformativeText("Êtes-vous sûr ?");
    msgBox.setStandardButtons(QMessageBox::Ok | QMessageBox::Cancel);
    msgBox.setDefaultButton(QMessageBox::Cancel);
    int retVal = msgBox.exec();
    if(retVal==QMessageBox::Ok)
        qApp->quit();
}

void MainWindow::closeEvent (QCloseEvent *event)
{
    QMessageBox msgBox;
    msgBox.setText("Vous allez quitter l'application");
    msgBox.setInformativeText("Êtes-vous sûr ?");
    msgBox.setStandardButtons(QMessageBox::Ok | QMessageBox::Cancel);
    msgBox.setDefaultButton(QMessageBox::Cancel);
    int retVal = msgBox.exec();
    if(retVal==QMessageBox::Ok) {
        event->accept();
    } else {
        event->ignore();
    }
}

