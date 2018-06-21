#ifndef CREATE_SMS_TASK_WIDGET_H
#define CREATE_SMS_TASK_WIDGET_H

#include <QWidget>

namespace Ui {
class CreateSmsTaskWidget;
}

class CreateSmsTaskWidget : public QWidget
{
    Q_OBJECT

public:
    explicit CreateSmsTaskWidget(QWidget *parent = 0);
    ~CreateSmsTaskWidget();

private:
    Ui::CreateSmsTaskWidget *ui;
};

#endif // CREATE_SMS_TASK_WIDGET_H
