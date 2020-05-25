#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QWidget>
#include <QtGui>
#include <QFileDialog>
#include <QMessageBox>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle(tr("串口助手"));

    ui->checkBox_Hex->setChecked(true);
    ui->checkBox_HexSend->setChecked(true);

    ui->pushButton_Send->setEnabled(false);


    QPalette pa;
    pa.setColor(QPalette::WindowText,Qt::red);
    ui->label_UartState->setPalette(pa);
    ui->label_UartState->setText(tr("串口未链接"));  // 设置串口链接状态


    m_DlgCom = new DlgCom(); 
    m_DlgCom->setWindowTitle(tr("配置串口"));

    m_DlgCom->SetMainUiPoint(ui); // 资源共享，使得m_DlgCom中可以调用mainwindow中的控件
    connect(ui->action_SetUart,SIGNAL(triggered()),this,SLOT(mainWindow_Dlgcom()));

    m_DlgAbout = new DlgAbout();
    m_DlgAbout->setWindowTitle(tr("关于"));
    connect(ui->menu_H, SIGNAL(aboutToShow()), this, SLOT(mainWindow_DlgAbout()));



}

MainWindow::~MainWindow()
{
    delete ui;
}

bool MainWindow::SaveAs()
{
    QString strFilPath;
    QString fileName = QFileDialog::getSaveFileName(this,tr("另存为"),strFilPath,tr("TXT文档(*.txt;所有文件(*.*)"));
    if(fileName.isEmpty())
        return false;

    if(!(fileName.endsWith(".txt",Qt::CaseInsensitive)))
    {
        fileName += ".txt";
    }
    QFile file(fileName);

    if(!file.open(QFile::WriteOnly|QFile::Text))
    {
        QMessageBox::critical(this,tr("critical"),tr("无法写入数据！"),QMessageBox::Yes);
        return false;
    }
    else
    {
        QTextStream out (&file);
        out<<ui->textBrowser_Display->toPlainText();  // 将控件内容移入txt中

        QMessageBox::information(this,tr("保存成功"),tr("保存成功"));
        return true;
    }
}

void MainWindow::mainWindow_Dlgcom()
{

    if(!m_DlgCom)
        return;

    m_DlgCom->exec();
}

void MainWindow::mainWindow_DlgAbout()
{
    if(!m_DlgAbout)
        return;

    m_DlgAbout->exec();
}

void MainWindow::on_checkBox_Hex_toggled(bool checked)
{
    if(!m_DlgCom)
        return;

    m_DlgCom->SetIsHexDisplay(checked);
}

void MainWindow::on_checkBox_HexSend_toggled(bool checked)
{
    if(!m_DlgCom)
        return;

    m_DlgCom->SetIsHexSend(checked);
}

void MainWindow::on_pushButton_Send_clicked()
{
    qDebug("开始发送消息");
    m_DlgCom->SendDataToUart();
}

void MainWindow::on_pushButton_Resize_clicked()
{
    qDebug("清空发送栏中的内容");
    ui->lineEdit_FrameHeader->clear();
    ui->textEdit_Data->clear();
    ui->lineEdit_CRC->clear();
    ui->lineEdit_FrameTail->clear();
}

void MainWindow::on_pushButton_Clear_clicked()
{
    ui->textBrowser_Display->clear();
}

void MainWindow::on_pushButton_Save_clicked()
{
    SaveAs();
}

void MainWindow::on_pushButton_Stop_clicked(bool checked)
{
    m_DlgCom->setStopDisplay(!m_DlgCom->m_bIsStopDisplay);

    if(m_DlgCom->m_bIsStopDisplay )
    {
        ui->pushButton_Stop->setText("继续");
    }
    else
    {
        ui->pushButton_Stop->setText("停止");
    }
}
