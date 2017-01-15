#pragma once

#include <QRunnable>

class CheckTask : public QRunnable
{
public:
    CheckTask();
    ~CheckTask();

    void run();
};
