#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    requestParseModule = new RequestParseModule();
    QByteArray b;
    requestParseModule->parseRequest(b);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete requestParseModule;
}
