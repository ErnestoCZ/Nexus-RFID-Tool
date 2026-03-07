#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QTableWidget>
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>
#include <QString>
#include "common_defs.h"


constexpr int BLOCKS_COUNT = 4;
constexpr int SECTOR_COUNT = 16;


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->widget = new QTableWidget(this);
    ui->cb_blockSelector->setPlaceholderText("Block number");
    ui->cb_sectorSelector->setPlaceholderText("Sector number");
    for (int var = 0; var < 16; ++var) {
        ui->cb_sectorSelector->addItem(QString::number(var),var);
    }
    for (int var = 0; var < 4; ++var) {
        ui->cb_blockSelector->addItem(QString::number(var),var);
    }
    ui->cb_blockSelector->addItem("ALL", QVariant::fromValue(SELECTOR::ALL));
    ui->cb_sectorSelector->addItem("ALL", QVariant::fromValue(SELECTOR::ALL));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pb_scanDevices_clicked()
{

    ui->cb_serialDevices->clear();
    auto portList = QSerialPortInfo::availablePorts();
    foreach (const auto &port, portList) {
        if(port.manufacturer().length() > 0)
        ui->cb_serialDevices->addItem(port.portName() + "\t" + port.description() + port.manufacturer());

    }

}


void MainWindow::on_pb_openDevices_clicked()
{

}


void MainWindow::on_pb_readCommand_clicked()
{

}


void MainWindow::on_pb_writeCommand_clicked()
{

}

