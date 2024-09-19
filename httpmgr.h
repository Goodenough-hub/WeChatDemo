#ifndef HTTPMGR_H
#define HTTPMGR_H
#include "singleton.h"
#include <QString>
#include <QUrl>
#include <QObject>
#include <QNetworkAccessManager>
#include <QJsonObject>
#include <QJsonDocument>

//CRTP 奇异递归模板模式 https://blog.csdn.net/sinat_21107433/article/details/123145236  静态多样性与动态多样性：https://www.cnblogs.com/Leo_wl/p/3667870.html
class HttpMgr:public QObject, public Singleton<HttpMgr>, public std::enable_shared_from_this<HttpMgr>
{
    Q_OBJECT // 使用QT的元对象系统
public:
    ~HttpMgr();
    void PostHttpReq(QUrl url, QJsonObject json, ReqID req_id, Modules mod);
private:
    friend class Singleton<HttpMgr>;
    HttpMgr();
    QNetworkAccessManager _manager;

private slots: // 私有的槽函数，仅供自己使用
    void slot_http_finish(ReqID id, QString res, ErrorCodes err, Modules mod);
signals:
    void sig_http_finish(ReqID id, QString res, ErrorCodes err, Modules mod);
    void sig_reg_mod_finish(ReqID id, QString res, ErrorCodes err);
};

#endif // HTTPMGR_H
