#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    for(int i=0;i<5;i++)
    {
        arrx[i] = 90;
        arrq[i] = 90;
    }
    arrq[5] = 45;
    arrx[5] = 45;
    arrx[6] = static_cast<char>(255);

    ui->setupUi(this);
    QString temp = QString::number(90);
    //base
    ui->horizontalSlider->setMinimum(0);
    ui->horizontalSlider->setMaximum(180);
    ui->horizontalSlider->setValue(90); //initial value
    ui->label->setText(temp);

    //arm
    ui->horizontalSlider_2->setMinimum(0);
    ui->horizontalSlider_2->setMaximum(180);
    ui->horizontalSlider_2->setValue(90); //initial value
    ui->label_2->setText(temp);

    //forearm
    ui->horizontalSlider_3->setMinimum(50);
    ui->horizontalSlider_3->setMaximum(180);
    ui->horizontalSlider_3->setValue(90); //initial value
    ui->label_3->setText(temp);

    //Wrist Y
    ui->horizontalSlider_4->setMinimum(0);
    ui->horizontalSlider_4->setMaximum(180);
    ui->horizontalSlider_4->setValue(90); //initial value
    ui->label_4->setText(temp);

    //Wrist X
    ui->horizontalSlider_5->setMinimum(0);
    ui->horizontalSlider_5->setMaximum(180);
    ui->horizontalSlider_5->setValue(90); //initial value
    ui->label_5->setText(temp);

    //Gripper
    temp = QString::number(45);

    ui->horizontalSlider_6->setMinimum(0);
    ui->horizontalSlider_6->setMaximum(90);
    ui->horizontalSlider_6->setValue(45); //initial value
    ui->label_6->setText(temp);

    std::string str = "/dev/ttyACM0";
    communication.qinit(str);
    if(communication.returnStatus() >= 0)
    {
        timer = new QTimer(this);
        connect(timer, SIGNAL(timeout()), this, SLOT(send_block()));
        timer->start(40); //5FPS
    }

    qDebug() << "Status of Fd = " <<  communication.returnFdStatus();
    qDebug() << "Status of get terrmios = " <<  communication.returnStatus();
}

void MainWindow::send_block()
{
    if(communication.qwrite(arrx) < 0)
    {
        qDebug() << "Error %i from Write: %s\n" <<  errno << strerror(errno);
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_horizontalSlider_valueChanged(int value)
{
    QString temp = QString::number(value);
    ui->label->setText(temp);
    arrx[0] = static_cast<char>(value);
    arrq[0] = value;
}


void MainWindow::on_horizontalSlider_2_valueChanged(int value)
{
    bool dir; //true is when angle is rasing, false in opposite case
    static int q = 90;
    (value > q)? dir = true : dir = false;

    int alfa = 90 - value;
    int val_prim = 90 + alfa;
    int dif = val_prim - arrq[2];

    qDebug() << "val_prim = " << val_prim <<"   dif  = " << dif << "   dir = " << dir ;

    if((dir == 1 && dif > -70) || (dir == 0 && dif < 50) )
    {
        QString temp = QString::number(value);
        ui->label_2->setText(temp);
        arrx[1] = value;
        arrq[1] = value;
        q = value;
    }
    else
    {
        QString temp = QString::number(q);
        ui->label_2->setText(temp);
        ui->horizontalSlider_2->setValue(q);
    }
}


void MainWindow::on_horizontalSlider_3_valueChanged(int value)
{
    bool dir; //true is when angle is rasing, false in opposite case
    static int q = 90;
    (value > q)? dir = true : dir = false;

    int alfa = 90 - arrq[1];
    int val_prim = 90 + alfa;
    int dif = val_prim - value;

    qDebug() << "val_prim = " << val_prim <<"   dif  = " << dif << "   dir = " << dir ;

    if((dir == 1 && dif > -70) || (dir == 0 && dif < 50) )
    {
        QString temp = QString::number(value);
        ui->label_3->setText(temp);
        arrx[2] = value;
        arrq[2] = value;
        q = value;
    }
    else
    {
        QString temp = QString::number(q);
        ui->label_3->setText(temp);
        ui->horizontalSlider_3->setValue(q);
    }
}


void MainWindow::on_horizontalSlider_4_valueChanged(int value)
{
    QString temp = QString::number(value);
    ui->label_4->setText(temp);
    arrx[3] = value;
    arrq[3] = value;
}


void MainWindow::on_horizontalSlider_5_valueChanged(int value)
{
    QString temp = QString::number(value);
    ui->label_5->setText(temp);
    arrx[4] = value;
    arrq[4] = value;
}


void MainWindow::on_horizontalSlider_6_valueChanged(int value)
{
    QString temp = QString::number(value);
    ui->label_6->setText(temp);
    arrx[5] = value;
    arrq[5] = value;
}


void MainWindow::on_pushButton_clicked()
{
    QString temp = QString::number(90);
    //base
    ui->horizontalSlider->setValue(90); //initial value
    ui->label->setText(temp);
    ui->horizontalSlider->setValue(90);

    //arm
    ui->horizontalSlider_2->setValue(90); //initial value
    ui->label_2->setText(temp);
    ui->horizontalSlider_2->setValue(90);

    //forearm
    ui->horizontalSlider_3->setValue(90); //initial value
    ui->label_3->setText(temp);
    ui->horizontalSlider_3->setValue(90);

    //Wrist Y
    ui->horizontalSlider_4->setValue(90); //initial value
    ui->label_4->setText(temp);
    ui->horizontalSlider_4->setValue(90);

    //Wrist X
    ui->horizontalSlider_5->setValue(90); //initial value
    ui->label_5->setText(temp);
    ui->horizontalSlider_5->setValue(90);

    //Gripper
    temp = QString::number(45);
    ui->horizontalSlider_6->setValue(45); //initial value
    ui->label_6->setText(temp);
    ui->horizontalSlider_6->setValue(45);

    for(int i=0;i<5;i++)
    {
        arrx[i] = 90;
        arrq[i] = 90;
    }
    arrq[5] = 45;
    arrx[5] = 45;

}


