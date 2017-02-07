#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <core/node.h>
#include <core/sms_task.h>
#include <core/sms_checker.h>
#include <core/time_trigger.h>

#include <python_env/python_engine.h>

#include <QStandardItemModel>
#include <QTimer>
#include <QDatetime>
#include <QVariant>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QFile>
#include <QByteArray>
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
    connect(timer_, &QTimer::timeout, [=](){
        slotUpdateNodeTreeView();
    });

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

    //root->removeRows(0, root->rowCount());

    for(int i=0; i<node_list_.size(); i++)
    {
        auto node = node_list_[i];
        if(root->rowCount() > i)
        {
            QStandardItem* name_item = root->child(i, 0);
            auto store_node = name_item->data(Qt::UserRole + 10).value<std::shared_ptr<Node>>();
            if(store_node != node)
            {
                name_item->setText(QString::fromStdString(node->name()));
                name_item->setData(QVariant::fromValue<std::shared_ptr<Node>>(node), Qt::UserRole + 10);

                QStandardItem* trigger_item = root->child(i, 1);
                trigger_item->setText(QString::fromStdString(node->trigger()->toString()));
            }
            QStandardItem *state_item = root->child(i, 2);
            state_item->setText(QString::fromStdString(NodeState::toString(node->state())));
        }
        else
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

    }
    qDebug()<<"[MainWindow::slotUpdateNodeTreeView] update tree done.";
}

void MainWindow::on_requeue_button_clicked()
{
    for(auto &node: node_list_)
    {
        node->requeue();
    }
}

void MainWindow::initNodeList()
{
    QString python_script_path = QApplication::applicationDirPath() + "/nwpc-sms-collector/sms_collector.py";
    QString node_config_file_path = QApplication::applicationDirPath() + "/nwpc-sms-collector/conf/node.conf.json";

    QFile node_config_file{node_config_file_path};
    if(!node_config_file.open(QIODevice::ReadOnly)) {
        qCritical("Couldn't open save file.");
        return;
    }
    QByteArray node_config_data = node_config_file.readAll();
    QJsonDocument node_config_document = QJsonDocument::fromJson(node_config_data);

    QJsonObject root = node_config_document.object();
    QJsonObject tree = root["tree"].toObject();
    QJsonArray children = tree["children"].toArray();

    for(int i=0; i<children.size(); i++)
    {
        QJsonObject child = children[i].toObject();

        QString name = child["name"].toString();
        shared_ptr<Node> node = make_shared<Node>(name.toStdString());

        QJsonObject trigger = child["trigger"].toArray()[0].toObject();
        QString trigger_type = trigger["type"].toString();
        if(trigger_type == "time")
        {
            QString trigger_time = trigger["time"].toString();
            unique_ptr<Trigger> trigger{new TimeTrigger{QTime::fromString(trigger_time, "hh:mm:ss")}};
            node->setTrigger(trigger);
        }

        QJsonObject task = child["task"].toObject();
        QString task_type = task["type"].toString();
        if(task_type!="SmsTask")
        {
            qCritical()<<"[MainWindow::initNodeList] task type is not supported:"<< task_type;
            continue;
        }

        QString task_category = task["category"].toString();

        if(task_category == "variable")
        {
            QJsonObject task_data = task["data"].toObject();

            QJsonObject auth = task_data["auth"].toObject();
            QJsonObject server = task_data["server"].toObject();

            QJsonObject variable = task_data["variables"].toArray()[0].toObject();

            shared_ptr<SmsVariableChecker> checker = make_shared<SmsVariableChecker>(
                    variable["path"].toString(),
                    variable["type"].toString(),
                    variable["name"].toString(),
                    variable["value"].toString()
            );

            QStringList arguments;
            arguments<<task_category;
            arguments<<"--host=" + auth["host"].toString();
            arguments<<"--port=" + auth["port"].toString();
            arguments<<"--user=" + auth["user"].toString();
            arguments<<"--password=" + auth["password"].toString();
            arguments<<"--sms-server=" + server["sms_server"].toString();
            arguments<<"--sms-user=" + server["sms_user"].toString();
            arguments<<"--sms-password=" + server["sms_password"].toString();
            arguments<<"--node-path=" + variable["path"].toString();

            QPointer<SmsTask> sms_task = new SmsTask{
                    python_engine_,
                    python_script_path,
                    arguments
            };
            sms_task->addVariableChecker(checker);

            node->setTask(static_cast<QPointer<Task>>(sms_task));
        }
        else
        {
            qCritical()<<"[MainWindow::initNodeList] task category is not supported:"<<task_category;
            continue;
        }

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

