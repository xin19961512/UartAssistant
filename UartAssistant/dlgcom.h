#ifndef DLGCOM_H
#define DLGCOM_H

#include <QDialog>
#include "Qextserial/win_qextserialport.h"
#include "User/uartbase.h"
#include "Ui_MainWindow.h"

namespace Ui {
class DlgCom;
}

class DlgCom : public QDialog,public UartBase
{
    Q_OBJECT

public:
    explicit DlgCom(QWidget *parent = 0);
    ~DlgCom();
public:
    Win_QextSerialPort *m_myCom = nullptr;
    void SetMainUiPoint(Ui::MainWindow *pMainUi){m_pMainUi = pMainUi;}

    void setStopDisplay(bool IsStopDisplay){m_bIsStopDisplay = IsStopDisplay;}
public:
    bool OpenUart(); // 打开串口
    void SendDataToUart(); // 发送数据到串口

private slots:
    void on_pushButton_OK_clicked();
    void ReadyMyCom();  // 接收来自串口对的数据

private:
    Ui::DlgCom *ui;
    Ui::MainWindow *m_pMainUi;

public:
    bool m_bIsStopDisplay = false; // false显示数字，ture，不显示数字
};

#endif // DLGCOM_H
