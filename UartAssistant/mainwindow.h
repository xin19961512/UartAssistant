#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "dlgcom.h"
#include "dlgabout.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

    DlgCom *m_DlgCom = nullptr;
    DlgAbout *m_DlgAbout = nullptr;

private:
    bool SaveAs();

private slots:
    void mainWindow_Dlgcom();
    void mainWindow_DlgAbout();
    void on_checkBox_Hex_toggled(bool checked);
    void on_checkBox_HexSend_toggled(bool checked);
    void on_pushButton_Send_clicked();
    void on_pushButton_Resize_clicked();
    void on_pushButton_Clear_clicked();
    void on_pushButton_Save_clicked();
    void on_pushButton_Stop_clicked(bool checked);
};

#endif // MAINWINDOW_H
