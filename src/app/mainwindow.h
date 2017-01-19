#pragma once
#include <QMainWindow>
#include <QPointer>
#include <QSharedPointer>

QT_BEGIN_NAMESPACE
class QTimer;
QT_END_NAMESPACE

namespace PythonEnv{
class PythonEngine;
}

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

private:
    void checkTaskList();

    Ui::MainWindow *ui;

    QPointer<QTimer> timer_;
    float timer_interval_msec_;

    QSharedPointer<PythonEnv::PythonEngine> python_engine_;
};
