#pragma once
#include <QMainWindow>
#include <QPointer>

QT_BEGIN_NAMESPACE
class QTimer;
QT_END_NAMESPACE

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void start();

private:
    void checkTaskList();

    Ui::MainWindow *ui;

    QPointer<QTimer> timer_;
    float timer_interval_msec_;
};
