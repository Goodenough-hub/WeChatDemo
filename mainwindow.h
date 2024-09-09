#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "logindialog.h"
/**********************************************************************************************************************
*
* @file         mainwindow.h
* @brief        主窗口
*
* @author       Goodenough
* @data         2024/09/09
* @history
**********************************************************************************************************************/
QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    LoginDialog *_login_dlg;
};
#endif // MAINWINDOW_H
