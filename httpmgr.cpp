#include "httpmgr.h"

HttpMgr::~HttpMgr()
{

}

HttpMgr::HttpMgr()
{
    connect(this, &HttpMgr::sig_http_finish, this, &HttpMgr::slot_http_finish);
}

// 向指定的URL发送HTTP POST请求
void HttpMgr::PostHttpReq(QUrl url, QJsonObject json, ReqID req_id, Modules mod)
{
    QByteArray data = QJsonDocument(json).toJson();
    QNetworkRequest request(url);
    // 设置请求头的内容类型为"application/json"，内容长度为JSON数据的长度
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    request.setHeader(QNetworkRequest::ContentLengthHeader, QByteArray::number(data.length()));

    // 获取当前对象的共享引用计数。可以确保对象的所有权被正确地共享和管理，避免了潜在的内存安全问题。
    auto self = shared_from_this(); // 共享引用计数

    QNetworkReply* reply = _manager.post(request, data); // 发送POST请求，将返回的QNetworkReply对象存储在reply指针中
    connect(reply, &QNetworkReply::finished, [self, reply, req_id, mod](){
        // 处理错误情况
        if(reply->error() != QNetworkReply::NoError){
            qDebug() << reply->errorString();
            // 发送信号通知完成
            emit self->sig_http_finish(req_id, "", ErrorCodes::ERR_NETWORK, mod);
            reply->deleteLater();
            return;
        }

        // 无错误
        QString res = reply->readAll();
        // 发送信号通知完成
        emit self->sig_http_finish(req_id, res, ErrorCodes::SUCCESS, mod);
        reply->deleteLater();
        return;
    });
}

void HttpMgr::slot_http_finish(ReqID id, QString res, ErrorCodes err, Modules mod)
{
    if(mod == Modules::REGISTERMOD){
        //发送信号通知指定模块http的响应结束了
        emit sig_reg_mod_finish(id, res, err);
    }
}
