#pragma once

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
