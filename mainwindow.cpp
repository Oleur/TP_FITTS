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
    computeAverageTime = 0;
    computeError = 0;

    ui->setupUi(this);
    ui->startButton->setEnabled(false);
    ui->endButton->setEnabled(false);
    ui->endButton->setStyleSheet(
                "background-color: red; border-style: none;border-width: 0px;border-radius: 5px;border-color: blue;font: 14px;}"
                );
    ui->startButton->setStyleSheet(
                "background-color: green; border-style: none;border-width: 0px;border-radius: 5px;border-color: blue;font: 14px;}"
                );

    connect(ui->endButton,SIGNAL(clicked()),this,SLOT(startButtonClicked()));
    connect(ui->nbTest_spinBox, SIGNAL(valueChanged(int)),this,SLOT(enableFrame()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::enableFrame(){
    ui->mainFrame->setEnabled(true);
    ui->startButton->setEnabled(true);
}

void MainWindow::on_startButton_clicked()
{
   timer_start->start();
   ui->startButton->setEnabled(false);
   ui->endButton->setEnabled(true);
   if(active_bool==false){
       ui->nbTest_spinBox->setEnabled(false);
       this->setNbTest(ui->nbTest_spinBox->value());
       ui->progressBar->setEnabled(true);
       ui->progression_label->setEnabled(true);
       ui->progressBar->setRange(0,nb_test);
       ui->progressBar->setValue(0);
   }
   active_bool=true;
}

void MainWindow::on_endButton_clicked()
{
    timer_start->stop();
    computeAverageTime += countdown;
    int tmp_average = computeAverageTime/nb_test;

    sumSquare += qPow((countdown - tmp_average),2);
    deviation = qSqrt(sumSquare/nb_test);
    computeError = deviation/qSqrt(nb_test);

    QString str_dist;
    QString str_averageTime;
    QString str_deviation;
    QString str_err_type;

    str_averageTime.setNum(tmp_average);
    str_dist.setNum(this->computeDistance(ui->endButton->pos(), ui->startButton->pos()));
    str_deviation.setNum(deviation);
    str_err_type.setNum(computeError);
    ui->average_moy->setText(str_averageTime+" ms");
    ui->average_ec_type->setText(str_deviation+" ms");
    ui->average_err_type->setText(str_err_type);

    countdown=0;
    nb_test-=1;
    ui->progressBar->setValue(ui->progressBar->value()+1);
    ui->progression_label->setText(QString::number(ui->progressBar->value())+" essais");
    if(nb_test == 0){
        this->reinitTest();
    }else{
        this->randomMoveButtons();
    }

}

void MainWindow::incrementCountdown(){
    countdown++;
}

void MainWindow::reinitTest(){
    nb_test=1;
    active_bool = false;
    ui->startButton->setEnabled(true);
    ui->endButton->setEnabled(false);
    ui->nbTest_spinBox->setValue(0);
    ui->nbTest_spinBox->setEnabled(true);
    ui->mainFrame->setEnabled(false);
    ui->progressBar->setValue(0);
    ui->progression_label->setText("0 essais");
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

//int MainWindow::computeFitts(){

//}

void MainWindow::setNbTest(int a){
    this->nb_test=a;
}

int MainWindow::getNbTest(){
    return this->nb_test;
}
