#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFile>
#include <QTextStream>
#include <QDebug>
#include <QDirIterator>
#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{

    QString dir = QFileDialog::getExistingDirectory(this, tr("Open Directory"),
                                                 "/home",
                                                 QFileDialog::ShowDirsOnly
                                                 | QFileDialog::DontResolveSymlinks);

    QDirIterator it(dir, QStringList() << "*.h", QDir::Files, QDirIterator::Subdirectories);
    while (it.hasNext())
        qDebug() << it.next();

    //https://stackoverflow.com/questions/37024306/qt-prepend-text-to-file
    QFile sfile("file.test");
    sfile.open(QFile::ReadOnly | QFile::Text);
    QByteArray buffer = sfile.readAll();
    sfile.close();
    sfile.open(QFile::WriteOnly | QFile::Text);
    QTextStream out(&sfile);
    out << ui->textEdit->toPlainText().toLatin1() <<endl;
    out << buffer;
     out << "#endif";
}
