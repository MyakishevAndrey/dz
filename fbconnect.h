// Обеспечивает связь с сервером fb

#ifndef FBCONNECT_H
#define FBCONNECT_H

#define APP_ID  "1813896548883742"
#define APP_VERSION "v2.8"

#include <QObject>
#include <QPointer>
#include <QNetworkAccessManager>
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonValue>
#include <QJsonDocument>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QEventLoop>
#include <QByteArray>
#include <QUrl>
#include <QUrlQuery>
#include <QLabel>
#include <QListWidget>
#include <QListWidgetItem>

class fbConnect : public QObject
{
    Q_OBJECT
public:
    explicit fbConnect();
    QJsonObject fbRequest(QString _method, QString _args);
    QPixmap fbRequestForPicture(const QString &in);
    QJsonObject fbPostMessage(QString texxt);
signals:
    void ready(); // посылаем главному окну
public slots:
    void token_get(QUrlQuery _qurl);
private:
    QString apiProtocol;
    QString appId;
    QString token;
    QString version;

    QPointer<QNetworkAccessManager> manager;

    QJsonObject ObjectFromString(const QString& in);
    QJsonObject sentRequest(const QString& in);

    bool isReplyCorrect(const QJsonObject & obj);



};

#endif // FBCONNECT_H
