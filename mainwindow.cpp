#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

     connect(logModule,SIGNAL(log(QString)),this,SLOT(log(QString)));

    requestParseModule = new RequestParseModule();
    requestParseModule->start();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::log(QString l)
{
    ui->textEdit->append(l);
}
