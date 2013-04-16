#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <Qtime>
#include <QtCore/qmath.h>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

    
public:
    explicit MainWindow(QWidget *parent = 0);
   ~MainWindow();
    QTimer *timer_start;
    int countdown;
    float computeDistance(QPoint, QPoint);
    float computeFitts(float dist);
    void computeValues();
    float computeAvg(QList<float>,int);
    float computeDeviation(QList<float>,int);
    float computeErrorType(QList<float>,int);
    float computeIntervalConfidence(QList<float>,int);
    int computeError;
    float theoDeviation;
    int nb_test;
    int active_bool;
    QList<float> emp_values;
    QList<float> theo_values;
    
protected slots:
    void timeOut();

private slots:
    void on_startButton_clicked();
    void on_endButton_clicked();
    void incrementCountdown();
    void randomMoveButtons();
    int randInt(int,int);
    void reinitTest();
    void enableFrame();


private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
