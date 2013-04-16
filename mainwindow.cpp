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
    nb_test=1;
    countdown=0;
    ui->setupUi(this);
    ui->startButton->setEnabled(false);
    ui->endButton->setEnabled(false);
    ui->mainFrame->setEnabled(false);
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
   ui->endButton->setText("Click");
   ui->startButton->setText("");

   if(active_bool==false){
       ui->nbTest_spinBox->setEnabled(false);
       ui->progressBar->setEnabled(true);
       ui->progression_label->setEnabled(true);

       ui->progressBar->setRange(0,ui->nbTest_spinBox->value());
       ui->progressBar->setValue(0);
   }
   active_bool=true;
}

void MainWindow::on_endButton_clicked()
{
    timer_start->stop();
    emp_values << countdown;

    float dist = this->computeDistance(ui->endButton->pos(), ui->startButton->pos());
    float fitts = this->computeFitts(dist);
    theo_values << fitts;

    countdown=0;
    nb_test+=1;
    ui->progressBar->setValue(ui->progressBar->value()+1);
    ui->progression_label->setText(QString::number(ui->progressBar->value())+" essais restants");
    ui->endButton->setText("");
    ui->startButton->setText("Click");


    if(nb_test == ui->nbTest_spinBox->value()+1){
        QMessageBox::information(this,"Information","Test terminé :)",QMessageBox::Ok);
        this->reinitTest();
    }else{
        this->randomMoveButtons();
    }

}

void MainWindow::incrementCountdown(){
    countdown++;
}

void MainWindow::reinitTest(){
    this->computeValues();
    emp_values.clear();
    theo_values.clear();
    nb_test=1;
    countdown=0;
    active_bool = false;
    ui->startButton->setEnabled(true);
    ui->endButton->setEnabled(false);
    ui->nbTest_spinBox->setValue(0);
    ui->nbTest_spinBox->setEnabled(true);
    ui->mainFrame->setEnabled(false);
    ui->progressBar->setValue(0);
    ui->progression_label->setText("0 essais restants");
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

float MainWindow::computeDistance(QPoint btn1, QPoint btn2){
    return qSqrt(qPow(btn2.x()-btn1.x(),2)+qPow(btn2.y()-btn1.y(),2));
}

float MainWindow::computeFitts(float dist){
    int i =100; //0.1 s
    int time_click = 200; //0.2s in ms
    return i*qLn((2*dist)/ui->endButton->width())+2*time_click;
}

void MainWindow::computeValues(){
    ui->average_moy->setText(QString::number(computeAvg(emp_values,nb_test)));
    ui->average_ec_type->setText(QString::number(computeDeviation(emp_values,nb_test)));
    ui->average_err_type->setText(QString::number(computeErrorType(emp_values,nb_test)));

    ui->theo_avg_label->setText(QString::number(computeAvg(theo_values,nb_test)));
    ui->theo_deviation_label->setText(QString::number(computeDeviation(theo_values,nb_test)));
    ui->theo_err_label->setText(QString::number(computeErrorType(theo_values,nb_test)));

    ui->ecart_label->setText("Ecart théorie-pratique "+QString::number(computeAvg(theo_values,nb_test)-computeAvg(emp_values,nb_test)));
}

float MainWindow::computeAvg(QList<float> list, int n){
    float sum = 0;
    QList<float>::iterator i;
    //Sum all the elements
    for (i = list.begin(); i != list.end(); ++i){
      sum += *i;
    }

    float avg = sum/n;
    return avg;
}

 float MainWindow::computeDeviation(QList<float> list,int n){
    float sumSquare=0;
    QList<float>::iterator i;
    float avg = computeAvg(list,n);
    for (i = list.begin(); i != list.end(); ++i){
        sumSquare += (*i-avg)*(*i-avg);
    }

    float deviation = qSqrt(sumSquare)/n;
    return deviation;
 }

float MainWindow::computeErrorType(QList<float> list ,int n){
    return (computeDeviation(list,n)/qSqrt(n));
}
