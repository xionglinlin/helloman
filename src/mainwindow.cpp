#include "mainwindow.h"
#include <QFile>
#include <QTextStream>
#include <QLabel>
#include <QMainWindow>
#include <QResizeEvent>
#include <QWidget>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setFixedSize(600, 400);

    // 读取文件内容
    QString name = "...";
    QFile file("/tmp/hello_man.conf");
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream in(&file);
        QString line = in.readLine();
        if (!line.isEmpty()) {
            name = line.trimmed();
        }
        file.close();
    }

    // 创建标签并设置为中心控件
    QLabel *label = new QLabel(QString("hello %1").arg(name), this);
    label->setAlignment(Qt::AlignCenter);
    label->setStyleSheet("font-size: 32px;");
    setCentralWidget(label);
}

MainWindow::~MainWindow()
{

}
