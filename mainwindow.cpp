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
}

MainWindow::~MainWindow()
{
    delete ui;
}
