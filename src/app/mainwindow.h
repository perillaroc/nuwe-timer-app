#pragma once
#include <QMainWindow>
#include <QPointer>
#include <QSharedPointer>
#include <QSystemTrayIcon>

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
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;

    void startTimer();
    void stopTimer();

protected:
    void closeEvent(QCloseEvent *event) Q_DECL_OVERRIDE;

private slots:
    void slotSwitchTimer(bool checked);

    void slotUpdateNodeTreeView(bool checked=false);

    void slotSystemTrayIconActivated(QSystemTrayIcon::ActivationReason reason);
    void slotSystemTrayIconMessageClicked();

    void on_requeue_button_clicked();

private:
    void createMenus();
    void createActions();
    void createTrayIcon();
    void initNodeList();
    void checkTaskList();

    Ui::MainWindow *ui;

    QPointer<QMenu> tray_icon_menu_;
    QPointer<QAction> quit_action_;
    QPointer<QAction> restore_action_;
    QPointer<QSystemTrayIcon> tray_icon_;
    QPointer<QMenu> app_menu_;

    QPointer<QTimer> timer_;
    int timer_interval_msec_;

    QSharedPointer<PythonEnv::PythonEngine> python_engine_;

    std::vector<std::shared_ptr<NuweTimer::Core::Node>> node_list_;
    QPointer<QStandardItemModel> node_tree_model_;
};
}
}

