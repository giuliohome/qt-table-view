#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "mymodel.h"
#include <QDebug>

// from https://forum.qt.io/topic/17971/qtableview-doesn-t-show-any-data/3
// The problem is that you are creating the model on the stack. As soon as pModel goes out of scope, it is destroyed again.
MyModel myModel;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->tableView->setModel(&myModel);
    qDebug() << "model set!";
}

MainWindow::~MainWindow()
{
    delete ui;
}

int count = 0;
void MainWindow::on_pushButton_clicked()
{
    count++;
    myModel.setCount(2 + count);
    ui->label->setText(("clicked " + std::to_string( count ) + "!").c_str());
}
