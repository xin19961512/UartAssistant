#include "dlgcom.h"
#include "ui_dlgcom.h"
#include <QMessageBox>
#include <QDebug>
#include <QSerialPortInfo>


DlgCom::DlgCom(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DlgCom)
{
    ui->setupUi(this);

    auto listPorts = QSerialPortInfo::availablePorts();
    // 动态填充当前所有可用Ports
    for(auto &pInfo :listPorts)
    {
        QString strPortsName = pInfo.portName();
        ui->comboBox_Com->addItem(strPortsName);
    }
}

DlgCom::~DlgCom()
{
    delete ui;
}

bool DlgCom::OpenUart()
{
    auto strComName = ui->comboBox_Com->currentText();
    m_myCom = new Win_QextSerialPort(strComName,QextSerialBase::EventDriven); // readyRead不产生信号的处理办法，创建mycom时使用EventDriven模式

    // [MXX 2020-05-15]
    // 上面的方法不管用，使用Timer后可以进入槽函数，说明是信号ReadyRead出了问题，暂时不处理
//    QTimer *timer = new QTimer(this);
//    connect(timer, SIGNAL(timeout()), this, SLOT(ReadyMyCom()));
//    timer->start(1000); // 每隔1s

    // 串口数据同步读取至主窗口
    connect(m_myCom, SIGNAL(readyRead()), this, SLOT(ReadyMyCom()));

    // 设置波特率
    m_myCom->setBaudRate((BaudRateType)ui->comboBox_Pote->currentText().toInt());
    // 设置校验值
    switch (ui->comboBox_Check->currentIndex())
    {
    case 0:
        m_myCom->setParity(PAR_NONE);
        break;
    case 1:
        m_myCom->setParity(PAR_EVEN);
        break;
    case 2:
        m_myCom->setParity(PAR_ODD);
        break;
    case 3:
        m_myCom->setParity(PAR_MARK);
        break;
    case 4:
        m_myCom->setParity(PAR_SPACE);
        break;
    default:
        m_myCom->setParity(PAR_NONE);
        qDebug("校验值设置失败，默认为NONE");
        break;
    };

    // 设置数据值
    m_myCom->setDataBits((DataBitsType)ui->comboBox_Data->currentText().toInt());
    // 设置停止位
    switch (ui->comboBox_Stop->currentIndex())
    {
    case 0:
        m_myCom->setStopBits(STOP_1);
        break;
    case 1:
        m_myCom->setStopBits(STOP_1_5);
        break;
    case 2:
        m_myCom->setStopBits(STOP_2);
        break;
    default:
        m_myCom->setStopBits(STOP_1);
        qDebug("停止位设置失败，默认为1Bit");
    };

    if(!m_myCom->open(QIODevice::ReadWrite))
    {
        QMessageBox::warning(this,tr("Warning"),tr("打开串口失败"),QMessageBox::Default);
        return false;
    }

    return true;
}

void DlgCom::SendDataToUart()
{
    if(!m_myCom->isOpen())
        return;

    QString strData = m_pMainUi->lineEdit_FrameHeader->displayText();
    strData += m_pMainUi->textEdit_Data->toPlainText();
    strData += m_pMainUi->lineEdit_CRC->displayText();
    strData += m_pMainUi->lineEdit_FrameTail->displayText();

    if(strData.isEmpty())
        return;

    QByteArray byteData = "";
    if(m_bIsHexSend)
    {
        byteData = QByteArray::fromHex(strData.toLatin1().data());
    }
    else
    {
        byteData = strData.toLatin1();
    }
    m_myCom->write(byteData);
}

void DlgCom::on_pushButton_OK_clicked()
{   
    if(m_myCom)
        delete m_myCom;  // 为了防止重复上次的设定，因为每次点击确定，都会在下面重新设置串口参数

    if(OpenUart())
    {
        this->close();

        QPalette pa;
        pa.setColor(QPalette::WindowText,Qt::blue);
        m_pMainUi->label_UartState->setPalette(pa);
        m_pMainUi->label_UartState->setText(tr("%1串口已链接").arg(ui->comboBox_Com->currentText()));

        m_pMainUi->pushButton_Send->setEnabled(true);
    }
}
// 读取函数
void DlgCom::ReadyMyCom()
{
//    qDebug("正在读取数据");
    QByteArray byte_Data = m_myCom->readAll();  // 读取数据
    QString strDisplay; // 显示数据
    if(m_bIsHexDisplay)
    {
        QString str = byte_Data.toHex().data();
        str = str.toUpper();
        for(int i = 0; i<str.length();i += 2)
        {
            QString strByte = str.mid(i,2);
            strDisplay += strByte;   // 写俩数
            strDisplay += " ";       // 隔一个空格
        }
    }
    else
    {
        strDisplay = QString(byte_Data);
    }

    // 如果为真，则不停止显示数据
    if(!m_bIsStopDisplay)
    {
        m_pMainUi->textBrowser_Display->insertPlainText(strDisplay);
    }

}
