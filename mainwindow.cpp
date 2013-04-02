#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtGui/QMessageBox>
#include <QtCore/qmath.h>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    timer_start = new QTimer(); //Construct the timer
    timer_start->setInterval(1);
    connect(timer_start, SIGNAL(timeout()), this, SLOT(incrementCountdown()));
    countdown=0;

    //QTimer *timer_end=new QTimer(this);
    ui->setupUi(this);

    ui->endButton->setStyleSheet(
                "background-color: red; border-style: none;border-width: 0px;border-radius: 5px;border-color: blue;font: 14px;}"
                );
    ui->startButton->setStyleSheet(
                "background-color: green; border-style: none;border-width: 0px;border-radius: 5px;border-color: blue;font: 14px;}"
                );

    connect(ui->endButton,SIGNAL(clicked()),this,SLOT(startButtonClicked()));
}

MainWindow::~MainWindow()
{
    delete ui;
}



void MainWindow::on_startButton_clicked()
{
   timer_start->start();
   ui->startButton->setEnabled(false);
   ui->endButton->setEnabled(true);
}

void MainWindow::on_endButton_clicked()
{
    timer_start->stop();
    QString str;
    str.setNum(this->computeDistance(ui->endButton->pos(), ui->startButton->pos()));
    QMessageBox::information( this, "Information",str);
    countdown=0;
    nb_test+=1;
    if(nb_test == ui->nbTest_spinBox->value()){
        QMessageBox::information( this, "Information","Test is over");
        ui->mainFrame->setEnabled(false);
        nb_test=0;
    }else{
        this->randomMoveButtons();
    }

}

void MainWindow::incrementCountdown(){
    countdown+=1;
}

void  MainWindow::timeOut(){}
void  MainWindow::randomMoveButtons(){
    ui->startButton->setEnabled(true);
    ui->endButton->setEnabled(false );
    ui->startButton->setGeometry(randInt(0,500),randInt(0,400), ui->startButton->geometry().width(), ui->startButton->geometry().height());
    ui->endButton->setGeometry(randInt(0,500),randInt(0,400), ui->endButton->geometry().width(), ui->endButton->geometry().height());

}
int MainWindow::randInt(int low, int high)
    {
    // Random number between low and high
    return qrand() % ((high + 1) - low) + low;
    }

int MainWindow::computeDistance(QPoint btn1, QPoint btn2){
    return qSqrt(qPow(btn2.x()-btn1.x(),2)+qPow(btn2.y()-btn1.y(),2));
}

//int MainWindow::computeFitts(){

//}
