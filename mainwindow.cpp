#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
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
    computeAverageTime += countdown;
    int tmp_average = computeAverageTime/nb_test;

    sumSquare += qPow((countdown - tmp_average),2);
    deviation = qSqrt(sumSquare/nb_test);

    QString str_dist;
    QString str_averageTime;
    QString str_deviation;
    str_averageTime.setNum(tmp_average);
    str_dist.setNum(this->computeDistance(ui->endButton->pos(), ui->startButton->pos()));
    str_deviation.setNum(deviation);
    ui->average_moy->setText(str_averageTime+" ms");
    ui->average_ec_type->setText(str_deviation);
    QMessageBox::information( this, "Time",str_dist);

    countdown=0;
    nb_test+=1;
    if(nb_test == ui->nbTest_spinBox->value()+1){
        QMessageBox::information( this, "Information","Test is over");
        ui->mainFrame->setEnabled(false);
        nb_test=1;
    }else{
        this->randomMoveButtons();
    }

}

void MainWindow::incrementCountdown(){
    countdown++;
}

void  MainWindow::timeOut(){}
void  MainWindow::randomMoveButtons(){
    ui->startButton->setEnabled(true);
    ui->endButton->setEnabled(false );
    ui->startButton->setGeometry(randInt(0,500),randInt(0,400), randInt(50,100), randInt(30, 90));
    ui->endButton->setGeometry(randInt(0,500),randInt(0,400), randInt(50,100), randInt(30, 90));

}
int MainWindow::randInt(int low, int high)
    {
    // Random number between low and high
    return qrand() % ((high + 1) - low) + low;
    }

int MainWindow::computeDistance(QPoint btn1, QPoint btn2){
    return qSqrt(qPow(btn2.x()-btn1.x(),2)+qPow(btn2.y()-btn1.y(),2));
}

int MainWindow::computeDeviation() {
    return 0;
}

//int MainWindow::computeFitts(){

//}
