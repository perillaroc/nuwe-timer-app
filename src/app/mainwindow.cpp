#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <core/node.h>
#include <core/sms_task.h>
#include <core/time_trigger.h>

#include <python_env/python_engine.h>

#include <QStandardItemModel>
#include <QTimer>
#include <QDatetime>
#include <QVariant>
#include <QtDebug>

using namespace std;
using namespace NuweTimer::Core;
using namespace NuweTimer::App;

Q_DECLARE_SMART_POINTER_METATYPE(std::shared_ptr)
Q_DECLARE_METATYPE(std::shared_ptr<Node>)

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow{parent},
    ui{new Ui::MainWindow},
    timer_{new QTimer{this}},
    timer_interval_msec_{1000},
    python_engine_{QSharedPointer<PythonEnv::PythonEngine>{new PythonEnv::PythonEngine{this}}},
    node_tree_model_{new QStandardItemModel{this}}
{
    ui->setupUi(this);

    python_engine_->setPythonDistributionDir("D:/windroc/project/2017/timer/playground/python/python36-x64");
    python_engine_->setPythonExecutableProgramPath("D:/windroc/project/2017/timer/playground/python/python36-x64/python.exe");

    node_tree_model_->setHorizontalHeaderLabels(QStringList()<<"name"<<"trigger");
    ui->node_tree_view->setModel(node_tree_model_);

    timer_->setInterval(timer_interval_msec_);
    connect(timer_, &QTimer::timeout, this, &MainWindow::checkTaskList);
//    connect(timer_, &QTimer::timeout, [=](){
//        slotUpdateNodeTreeView();
//    });

    connect(ui->timer_switch_pushbutton, &QPushButton::toggled, this, &MainWindow::slotSwitchTimer);
    connect(ui->update_pushbutton, &QPushButton::clicked, this, &MainWindow::slotUpdateNodeTreeView);

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

void MainWindow::slotSwitchTimer(bool checked)
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

void MainWindow::slotUpdateNodeTreeView(bool checked)
{
    Q_UNUSED(checked);
    QStandardItem* root = node_tree_model_->invisibleRootItem();
    root->removeRows(0, root->rowCount());

    for(auto &node: node_list_)
    {
        QStandardItem* name_item = new QStandardItem();
        name_item->setText(QString::fromStdString(node->name()));
        name_item->setData(QVariant::fromValue<std::shared_ptr<Node>>(node), Qt::UserRole + 10);

        QStandardItem* trigger_item = new QStandardItem();
        trigger_item->setText(QString::fromStdString(node->trigger()->toString()));

        QStandardItem* state_item = new QStandardItem();
        state_item->setText(QString::fromStdString(NodeState::toString(node->state())));

        root->appendRow(QList<QStandardItem*>()<<name_item<<trigger_item<<state_item);
    }
    qDebug()<<"[MainWindow::slotUpdateNodeTreeView] update tree done.";
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

        shared_ptr<Node> node = make_shared<Node>("grapes_meso_v4_1");
        node->setTrigger(trigger);
        node->setTask(task);

        node_list_.push_back(node);
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

        shared_ptr<Node> node = make_shared<Node>("gmf_grapes_gfs_v2_0");
        node->setTrigger(trigger);
        node->setTask(task);

        node_list_.push_back(node);
    }

    for(auto &node: node_list_)
    {
        node->begin();
    }

    slotUpdateNodeTreeView();
}

void MainWindow::checkTaskList()
{
    QDateTime current_date_time = QDateTime::currentDateTime();
    qDebug()<<"[MainWindow::checkTaskList]"<<current_date_time;

    if(current_date_time.time().second()%10 == 0)
    {
        for(auto &task: node_list_)
        {
            if(task->resolveDependencies())
            {
                task->run();
            }
        }
    }
}
