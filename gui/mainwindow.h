#pragma once

#include <QMainWindow>
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>

QT_BEGIN_NAMESPACE
namespace Ui {
    class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pb_scanDevices_clicked();

    void on_pb_openDevices_clicked();

    void on_pb_readCommand_clicked();

    void on_pb_writeCommand_clicked();

private:
    Ui::MainWindow *ui;
    QSerialPort m_serialPort{};
};
