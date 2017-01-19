#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "check_task.h"
#include "python_engine.h"

#include <QTimer>
#include <QDatetime>
#include <QtDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow{parent},
    ui{new Ui::MainWindow},
    timer_{new QTimer{this}},
    timer_interval_msec_{1000},
    python_engine_{QSharedPointer<PythonEnv::PythonEngine>{new PythonEnv::PythonEngine{this}}}
{
    ui->setupUi(this);

    python_engine_->setPythonDistributionDir("D:/windroc/project/2017/timer/playground/python/python36-x64");
    python_engine_->setPythonExecutableProgramPath("D:/windroc/project/2017/timer/playground/python/python36-x64/python.exe");

    timer_->setInterval(timer_interval_msec_);
    connect(timer_, &QTimer::timeout, this, &MainWindow::checkTaskList);

    ui->timer_switch_pushbutton->setChecked(true);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::startTimer()
{
    timer_->start();
}

void MainWindow::stopTimer()
{
    timer_->stop();
}

void MainWindow::on_timer_switch_pushbutton_toggled(bool checked)
{
    if(checked)
    {
        startTimer();
        ui->timer_switch_pushbutton->setText("Stop Timer");
    }
    else
    {
        stopTimer();
        ui->timer_switch_pushbutton->setText("Start Timer");
    }
}

void MainWindow::checkTaskList()
{
    QDateTime current_date_time = QDateTime::currentDateTime();
    qDebug()<<"[MainWindow::checkTaskList]"<<current_date_time;
    if(current_date_time.time().second()%10 == 0)
    {
        CheckTask *task = new CheckTask{python_engine_};
        task->run();
    }
}


