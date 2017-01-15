#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QTimer>
#include <QDatetime>
#include <QtDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow{parent},
    ui{new Ui::MainWindow},
    timer_{new QTimer{this}},
    timer_interval_msec_{1000}
{
    ui->setupUi(this);
    timer_->setInterval(timer_interval_msec_);
    connect(timer_, &QTimer::timeout, this, &MainWindow::checkTaskList);
    start();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::start()
{
    timer_->start();
}

void MainWindow::checkTaskList()
{
    qDebug()<<"checkTaskList"<<QDateTime::currentDateTime();
}
