#ifndef REGISTERDIALOG_H
#define REGISTERDIALOG_H

#include <QDialog>
#include "global.h"

namespace Ui {
class RegisterDialog;
}

class RegisterDialog : public QDialog
{
    Q_OBJECT

public:
    explicit RegisterDialog(QWidget *parent = nullptr);
    ~RegisterDialog();

private slots:
    void on_get_code_clicked();
    void slot_reg_mod_finish(ReqID id, QString res, ErrorCodes err);

private:
    void initHttpHandlers();
    Ui::RegisterDialog *ui;
    void showTip(QString str, bool b_ok);
    QMap<ReqID, std::function<void(const QJsonObject&)>> _handlers; // id与函数对象的映射
};

#endif // REGISTERDIALOG_H
