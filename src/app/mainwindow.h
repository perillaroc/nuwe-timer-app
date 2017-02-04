#pragma once
#include <QMainWindow>
#include <QPointer>
#include <QSharedPointer>

#include <vector>
#include <memory>

QT_BEGIN_NAMESPACE
class QTimer;
class QStandardItemModel;
QT_END_NAMESPACE

namespace PythonEnv{
class PythonEngine;
}

namespace NuweTimer {

namespace Core{
class Node;
}

namespace App{

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void startTimer();
    void stopTimer();

private slots:
    void slotSwitchTimer(bool checked);

    void slotUpdateNodeTreeView(bool checked=false);

    void on_requeue_button_clicked();

private:
    void initNodeList();
    void checkTaskList();

    Ui::MainWindow *ui;

    QPointer<QTimer> timer_;
    float timer_interval_msec_;

    QSharedPointer<PythonEnv::PythonEngine> python_engine_;

    std::vector<std::shared_ptr<NuweTimer::Core::Node>> node_list_;
    QPointer<QStandardItemModel> node_tree_model_;
};
}
}

