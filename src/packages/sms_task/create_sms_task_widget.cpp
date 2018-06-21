#include "create_sms_task_widget.h"
#include "ui_create_sms_task_widget.h"

CreateSmsTaskWidget::CreateSmsTaskWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CreateSmsTaskWidget)
{
    ui->setupUi(this);
}

CreateSmsTaskWidget::~CreateSmsTaskWidget()
{
    delete ui;
}
