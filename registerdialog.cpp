#include "registerdialog.h"
#include "ui_registerdialog.h"
#include "global.h"
#include "httpmgr.h"

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

    connect(HttpMgr::GetInstance().get(), &HttpMgr::sig_reg_mod_finish, this, &RegisterDialog::slot_reg_mod_finish); // 获取HttpMgr的裸指针
    initHttpHandlers();
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

void RegisterDialog::slot_reg_mod_finish(ReqID id, QString res, ErrorCodes err)
{
    if(err != ErrorCodes::SUCCESS){
        showTip(tr("网络请求错误"), false);
        return;
    }

    // 解析Json 字符串，res转化为QByteArray
    QJsonDocument jsonDoc = QJsonDocument::fromJson(res.toUtf8());
    if(jsonDoc.isNull()){
        showTip(tr("json解析失败"), false);
        return;
    }

    if(!jsonDoc.isObject()){
        showTip(tr("json解析失败"), false);
        return;
    }

    _handlers[id](jsonDoc.object());
    return;
}

void RegisterDialog::initHttpHandlers()
{
    // 注册获取验证码回包的逻辑
    _handlers.insert(ReqID::ID_GET_VARIFY_CODE, [this](const QJsonObject& jsonObj){
        int error = jsonObj["error"].toInt();
        if(error != ErrorCodes::SUCCESS)
        {
            showTip(tr("参数错误"), false);
            return;
        }

        auto email = jsonObj["email"].toString();
        showTip(tr("验证码已经发送到邮箱，注意查收"), true);
        qDebug() << "email is " << email;
    });
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

