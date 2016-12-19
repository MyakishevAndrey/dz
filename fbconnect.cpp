#include "fbconnect.h"

fbConnect::fbConnect()
{
    appId = APP_ID;
    version = APP_VERSION;
    manager = new QNetworkAccessManager(this);
    apiProtocol = "https://graph.facebook.com";
}

QJsonObject fbConnect::fbRequest(QString _method, QString _args)
{
    QString reqStr = "%1/%2/%3/%4"; //1 - domain, 2-version, 3-method, 4-args
    reqStr = reqStr.arg(apiProtocol, version, _method, _args);
    QJsonObject obj = sentRequest(reqStr);
    return obj;
}

//SLOT
void fbConnect::token_get(QUrlQuery _qurl)
{
    token = "OAuth " + _qurl.queryItemValue("access_token");
    emit ready();
}

QJsonObject fbConnect::ObjectFromString(const QString &in)
{
    QJsonObject obj;

    QJsonDocument doc = QJsonDocument::fromJson(in.toUtf8());

    // check validity of the document
    if(!doc.isNull())
    {
        if(doc.isObject())
        {
            obj = doc.object();
        }
        else
        {
            qDebug() << "Document is not an object" << endl;
        }
    }
    else
    {
        qDebug() << "Invalid JSON...\n" << in << endl;
    }

    return obj;
}

QJsonObject fbConnect::sentRequest(const QString &in)
{
    QUrl url(in);
    QNetworkRequest request(url);
    request.setRawHeader(QByteArray("Authorization"), QByteArray(token.toStdString().c_str()));
    QNetworkReply* reply = manager->get(request);

    QEventLoop loop;
    connect(reply, SIGNAL(finished()), &loop, SLOT(quit()));
    loop.exec();

    if(reply->error() != QNetworkReply::NoError){
        qDebug() <<  reply->errorString();
        reply->deleteLater();
        return QJsonObject();
    }
    QByteArray content = reply->readAll();

    QString  str = QString::fromUtf8(content.data(), content.size());

    QJsonObject  jobj  =  ObjectFromString(str);
    isReplyCorrect(jobj);
    reply->deleteLater();
    return jobj;
}

QPixmap fbConnect::fbRequestForPicture(const QString &in)
{
    QUrl url(in);
    QNetworkRequest request(url);
    QNetworkReply* reply = manager->get(request);

    QEventLoop loop;
    connect(reply, SIGNAL(finished()), &loop, SLOT(quit()));
    loop.exec();

    if(reply->error() != QNetworkReply::NoError){
        qDebug() <<  reply->errorString();
        reply->deleteLater();
        return QPixmap();
    }

    QByteArray jpegData = reply->readAll();
    QPixmap pixmap(100,100);
    pixmap.loadFromData(jpegData);

    reply->deleteLater();
    return pixmap;
}

QJsonObject fbConnect::fbPostMessage(QString texxt)
{
    QString str = "https://graph.facebook.com/v2.8/me/feed";
    QUrl url(str);
    QNetworkRequest request(url);
    request.setRawHeader(QByteArray("Authorization"), QByteArray(token.toStdString().c_str()));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "text");
    QString text;
    if(texxt.isEmpty())
    {text = "message=test+message+new";}
    else {text = QString("message=")+texxt;}
    qDebug() << text;
    QNetworkReply* reply = manager->post(request, text.toStdString().c_str());

    QEventLoop loop;
    connect(reply, SIGNAL(finished()), &loop, SLOT(quit()));
    loop.exec();

    if(reply->error() != QNetworkReply::NoError){
        qDebug() <<  reply->errorString();
        reply->deleteLater();
        return QJsonObject();
    }

    QByteArray data = reply->readAll();
    QString strData = QString::fromUtf8(data);

    qDebug() << strData;

    reply->deleteLater();
    return QJsonObject();
}

bool fbConnect::isReplyCorrect(const QJsonObject &obj)
{
    if(!obj["error"].isObject()) return true;
    return false;
}
