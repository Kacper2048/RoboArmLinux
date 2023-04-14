#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QTimer>
#include <QMainWindow>
#include "transmission.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    transmission communication;

    //todo control of the angle between forearm and arm

    ~MainWindow();

private slots:
    void on_horizontalSlider_valueChanged(int value);
    void on_horizontalSlider_2_valueChanged(int value);
    void on_horizontalSlider_3_valueChanged(int value);
    void on_horizontalSlider_4_valueChanged(int value);
    void on_horizontalSlider_5_valueChanged(int value);
    void on_horizontalSlider_6_valueChanged(int value);
    void send_block();
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    QTimer *timer;
    Ui::MainWindow *ui;
    char arrx[7]{}; //last container has 255 value as sign of end of block
                    //it is set in constructor of MainWindow
    int arrq[6]{};

};
#endif // MAINWINDOW_H
