#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "check_task.h"
#include "python_engine.h"


#include <QThreadPool>
#include <QTimer>
#include <QDatetime>
#include <QtDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow{parent},
    ui{new Ui::MainWindow},
    thread_pool_{new QThreadPool{this}},
    timer_{new QTimer{this}},
    timer_interval_msec_{1000},
    python_engine_{QSharedPointer<PythonEnv::PythonEngine>{new PythonEnv::PythonEngine{this}}}
{
    ui->setupUi(this);

    python_engine_->setPythonDistributionDir("D:/windroc/project/2017/timer/playground/python/python36-x64");
    python_engine_->setPythonExecutableProgramPath("D:/windroc/project/2017/timer/playground/python/python36-x64/python.exe");

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
    CheckTask *task = new CheckTask{python_engine_};
    CheckTaskRunner *runner = new CheckTaskRunner{task};
    runner->run();
}
