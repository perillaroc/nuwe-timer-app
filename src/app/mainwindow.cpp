#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <core/node.h>
#include <core/sms_task.h>
#include <core/time_trigger.h>

#include <python_env/python_engine.h>

#include <QTimer>
#include <QDatetime>
#include <QtDebug>

using namespace std;
using namespace NuweTimer::Core;
using namespace NuweTimer::App;

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

    initNodeList();
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

void MainWindow::initNodeList()
{

    QString python_script_path = QApplication::applicationDirPath() + "/nwpc-sms-collector/sms_collector.py";
    {
        QStringList arguments;
        arguments<<"variable";
        arguments<<"--host=10.20.49.131";
        arguments<<"--port=22";
        arguments<<"--user=nwp";
        arguments<<"--password=nwpop";
        arguments<<"--sms-server=nwpc_op";
        arguments<<"--sms-user=nwp";
        arguments<<"--sms-password=1";
        arguments<<"--node-path=/grapes_meso_v4_1";

        QPointer<Task> task = new SmsTask{
                python_engine_,
                python_script_path,
                arguments
        };
        unique_ptr<Trigger> trigger{new TimeTrigger{QTime(0,0,0)}};

        unique_ptr<Node> node{new Node};
        node->setTrigger(trigger);
        node->setTask(task);

        node_list_.push_back(std::move(node));
    }
    {
        QStringList arguments;
        arguments<<"variable";
        arguments<<"--host=10.20.49.131";
        arguments<<"--port=22";
        arguments<<"--user=nwp";
        arguments<<"--password=nwpop";
        arguments<<"--sms-server=nwpc_op";
        arguments<<"--sms-user=nwp";
        arguments<<"--sms-password=1";
        arguments<<"--node-path=/gmf_grapes_gfs_v2_0";

        QPointer<Task> task = new SmsTask{
                python_engine_,
                python_script_path,
                arguments
        };
        unique_ptr<Trigger> trigger{new TimeTrigger{QTime(0,0,0)}};

        unique_ptr<Node> node{new Node};
        node->setTrigger(trigger);
        node->setTask(task);

        node_list_.push_back(std::move(node));
    }
}

void MainWindow::checkTaskList()
{
    QDateTime current_date_time = QDateTime::currentDateTime();
    qDebug()<<"[MainWindow::checkTaskList]"<<current_date_time;

    if(current_date_time.time().second()%10 == 0)
    {
        for(auto &task: node_list_)
        {
            if(task->resolveDepencies())
            {
                task->run();
            }
        }
    }
}


