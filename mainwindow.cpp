#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QMessageBox>
#include <QProcess>
#include <QDesktopServices>
#include <QUrl>


MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setFixedSize(geometry().width(),geometry().height());
    this->setWindowTitle("The 2LSCMP");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    file1Name = QFileDialog::getOpenFileName(
             this,
             tr("Please Select Input File"),
             "C://",
             tr("Text File (*.txt);;All Files (*.*)")
             );
    ui->lineEdit->setText(file1Name);
    ui->pushButton_2->setEnabled(true);
}

void MainWindow::on_pushButton_2_clicked()
{
    //printsomething();
    QObject *Parsing;
    QString program = "Parsing.exe";
    QStringList arguments;
    arguments = (QStringList)file1Name;
    QProcess *myProcess = new QProcess(Parsing);
    myProcess->start(program, arguments);

    QString str;

    str = file1Name;
    str.truncate(str.lastIndexOf("."));
    str.append("-Out.csv");
    QMessageBox::information(this, tr("Weeee!, Archivo Creado"), str);

    //QDesktopServices::openUrl(QUrl(str,QUrl::TolerantMode));

}
