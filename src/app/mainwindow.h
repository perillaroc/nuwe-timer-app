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
    void on_timer_switch_pushbutton_toggled(bool checked);

    void slotUpdateNodeTreeView();

private:
    void initNodeList();
    void checkTaskList();

    Ui::MainWindow *ui;

    QPointer<QTimer> timer_;
    float timer_interval_msec_;

    QSharedPointer<PythonEnv::PythonEngine> python_engine_;

    std::vector<std::unique_ptr<NuweTimer::Core::Node>> node_list_;
    QPointer<QStandardItemModel> node_tree_model_;
};
}
}

