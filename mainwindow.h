#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "requestparsemodule.h"
#include "logmodule.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
private:
    Ui::MainWindow *ui;
    RequestParseModule *requestParseModule;
    LogModule *logModule;

public slots:
    void log(QString l);
};

#endif // MAINWINDOW_H
