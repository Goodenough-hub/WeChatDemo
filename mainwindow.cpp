#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // 设置应用程序图标
    setWindowIcon(QIcon(":/img/icon/wechat-logo.png"));

    // 把logindialog设置到主界面上
    _login_dlg = new LoginDialog();
    setCentralWidget(_login_dlg);
    _login_dlg->show();

    // 创建和注册消息链接
    connect(_login_dlg, &LoginDialog::switchRegister, this, &MainWindow::SlotSwitchReg);
    _reg_dlg = new RegisterDialog();
}

MainWindow::~MainWindow()
{
    delete ui;

    if(_login_dlg)
    {
        delete _login_dlg;
        _login_dlg = nullptr;
    }

    if(_reg_dlg)
    {
        delete _reg_dlg;
        _reg_dlg = nullptr;
    }
}

void MainWindow::SlotSwitchReg()
{
    setCentralWidget(_reg_dlg);
    _login_dlg->hide();
    _reg_dlg->show();
}
