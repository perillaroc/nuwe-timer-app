#pragma once

#include <QObject>
#include <QString>
#include <QFuture>

namespace PythonEnv{

class PythonCommand;

class PythonEngine : public QObject
{
    Q_OBJECT
public:
    explicit PythonEngine(QObject *parent = 0);
    ~PythonEngine();

    QString pythonDistributionDir() const;
    void setPythonDistributionDir(const QString &pythonDistributionDir);

    QString pythonExecutableProgramPath() const;
    void setPythonExecutableProgramPath(const QString &pythonExecutableProgramPath);


    PythonCommand *createPythonCommand();
    QFuture<void> executePythonScript(PythonCommand *command, const QString &script_path, const QStringList &argument_list);

    void runPythonScript(PythonCommand *command, const QString &script_path, const QStringList &argument_list);

signals:

public slots:

private:
    QString python_distribution_dir_;
    QString python_executable_program_path_;

};

}
