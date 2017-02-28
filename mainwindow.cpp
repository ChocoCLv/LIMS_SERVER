#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    requestParseModule = new RequestParseModule();
    logModule = LogModule::getInstance();

    connect(logModule,SIGNAL(log(QString)),this,SLOT(log(QString)));
}

MainWindow::~MainWindow()
{
    delete ui;
    delete requestParseModule;
}

void MainWindow::log(QString l)
{
    ui->textEdit->append(l);
}
