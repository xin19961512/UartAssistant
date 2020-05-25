#ifndef UARTBASE_H
#define UARTBASE_H
//#include <QDialog>

class UartBase
{
//    Q_OBJECT
public:
    UartBase();

    void SetIsHexSend(bool bIsHexSend){m_bIsHexSend = bIsHexSend;}              // 是否以十六进制发送
    void SetIsHexDisplay(bool bIsHexDisplay){m_bIsHexDisplay = bIsHexDisplay;}  // 是否以十六进制显示

public:
    bool m_bIsHexSend = true;       // 是否以十六进制发送
    bool m_bIsHexDisplay = true;    // 是否以十六进制显示
};

#endif // UARTBASE_H
