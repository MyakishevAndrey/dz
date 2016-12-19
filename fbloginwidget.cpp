#include "fbloginwidget.h"
#include "ui_fbloginwidget.h"


fbLoginWidget::fbLoginWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::fbLoginWidget)
{
    ui->setupUi(this);
    web = new QWebEngineView(this);
    web->hide();

    //когда изменяется url
    connect(web, SIGNAL(urlChanged(QUrl)), this, SLOT(urlChanged(QUrl)));


}

fbLoginWidget::~fbLoginWidget()
{
    delete ui;
}

void fbLoginWidget::on_pb1_clicked()
{

    web->show();
    QUrl url = QUrl(QString("https://www.facebook.com/v2.8/dialog/oauth?client_id=%1&response_type=token&scope=email,public_profile,user_likes,user_friends,user_posts,publish_actions&redirect_uri=http://localhost/").arg(APP_ID));


    web->load(url);

    if(new_user) web->page()->profile()->cookieStore()->deleteAllCookies();

    new_user = false;

}

void fbLoginWidget::urlChanged(QUrl _url)
{
    if(_url.toString().indexOf("access_token=") != -1)
    {
        web->close();

        QString str = _url.toString().remove("#");

        QUrl nurl(str);
        QUrlQuery querry(nurl);

        emit token_get(querry);
    }
}

void fbLoginWidget::on_pb2_clicked()
{
    new_user = true;
    emit ui->pb1->clicked();
}
