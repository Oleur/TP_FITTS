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
    int computeDistance(QPoint, QPoint);
    int computeAverageTime;
    int computeDeviation();
    int deviation = 0;
    int computeError = 0;
    int sumSquare = 0;
    int nb_test = 1;
    
protected slots:
    void timeOut();

private slots:
    void on_startButton_clicked();
    void on_endButton_clicked();
    void incrementCountdown();
    void randomMoveButtons();
    int randInt(int,int);


private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
