#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>

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
