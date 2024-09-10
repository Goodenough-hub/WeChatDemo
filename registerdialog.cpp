#include "registerdialog.h"
#include "ui_registerdialog.h"
#include "global.h"

RegisterDialog::RegisterDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::RegisterDialog)
{
    ui->setupUi(this);

    // 设置密码模式
    ui->pass_edit->setEchoMode(QLineEdit::Password);
    ui->comfirm_edit->setEchoMode(QLineEdit::Password);

    // 设置err_tip状态
    ui->err_tip->setProperty("state", "normal");
    repolish(ui->err_tip);
}

RegisterDialog::~RegisterDialog()
{
    delete ui;
}

void RegisterDialog::on_get_code_clicked()
{
    auto email = ui->email_edit->text();
    QRegularExpression regex(R"((\w+)(\.|_)?(\w*)@(\w+)(\.(\w+))+)");
    bool match = regex.match(email).hasMatch();
    if(match)
    {
        // 发送验证码
        showTip(tr("正在向邮箱发送验证码...\n请注意查收！"), true);
    }
    else
    {
        showTip(tr("邮箱地址不正确"), false);
    }
}

void RegisterDialog::showTip(QString str, bool b_ok)
{
    if(b_ok)
    {
        ui->err_tip->setProperty("state", "normal");
    }
    else
    {
        ui->err_tip->setProperty("state", "err");
    }
    ui->err_tip->setText(str);

    repolish(ui->err_tip); // 刷新
}

