#include "form.h"
#include "ui_form.h"

Form::Form(fbConnect *_fb, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Form)
{
    ui->setupUi(this);

    show();
    fb = _fb;

    connect(this, SIGNAL(has_news()), this, SLOT(set_news()));
    connect(this, SIGNAL(has_friends()), this, SLOT(set_friends()));

    QJsonObject profileData = fb->fbRequest("me", "?fields=id,name,email,picture");
    QJsonObject feed = fb->fbRequest("me/feed", "");
    QJsonObject friends = fb->fbRequest("me/taggable_friends", "");
    friends_array = friends["data"].toArray();
    photo_url = profileData["picture"].toObject()["data"].toObject()["url"].toString();
    //qDebug() << friends;
    QPixmap photo = fb->fbRequestForPicture(photo_url);
    my_photo = photo;
    QSize PicSize(100, 100);
    my_photo = my_photo.scaled(PicSize,Qt::KeepAspectRatio,Qt::SmoothTransformation);
    my_name = profileData["name"].toString();
    my_id = profileData["id"].toString();
    my_email = profileData["email"].toString();
    news_array = feed["data"].toArray();
    auto a=news_array.size();
    for(int i{0}; i < 4-a%4; i++){
    news_array.push_back(QJsonValue());
    }
    setPDataToLabels();
}

Form::~Form()
{
    delete ui;
}

void Form::setPDataToLabels()
{
    ui->l_username->setText(my_name);
    ui->l_id1->setText(my_id);
    ui->l_email->setText(my_email);
    ui->l_photo->setPixmap(my_photo);

    emit has_news();
    emit has_friends();
}

void Form::set_friends()
{
    for (int i=0;i<friends_array.size();i++)
    {
        ui->listWidget->addItem(friends_array[i].toObject()["name"].toString());

    }
}

QString Form::feed_info(QString id, QLabel * label,QLabel * label_2)
{
    QJsonObject news = fb->fbRequest(id, "?fields=picture,story");
    if(news.isEmpty()) return QString();
    photo_url_for_news = news["picture"].toString();
    QPixmap photo = fb->fbRequestForPicture(photo_url_for_news);
    my_photo_for_news = photo;
    QSize PicSize(100, 100);
    my_photo_for_news = my_photo_for_news.scaled(PicSize,Qt::KeepAspectRatio,Qt::SmoothTransformation);
    label->setPixmap(my_photo_for_news);
    label_2->setText(news["story"].toString());
    return QString();
}

void Form::set_news()
{
    feed_info(news_array[current_news_index].toObject()["id"].toString(),ui->ph_1,ui->ln_1);
    feed_info(news_array[current_news_index+1].toObject()["id"].toString(),ui->ph_2,ui->ln_2);
    feed_info(news_array[current_news_index+2].toObject()["id"].toString(),ui->ph_3,ui->ln_3);
    feed_info(news_array[current_news_index+3].toObject()["id"].toString(),ui->ph_4,ui->ln_4);

if (!news_array[current_news_index].toObject()["message"].toString().isEmpty())
    ui->ln_1->setText(news_array[current_news_index].toObject()["message"].toString());
if (!news_array[current_news_index+1].toObject()["message"].toString().isEmpty())
    ui->ln_2->setText(news_array[current_news_index+1].toObject()["message"].toString());
if (!news_array[current_news_index+2].toObject()["message"].toString().isEmpty())
    ui->ln_3->setText(news_array[current_news_index+2].toObject()["message"].toString());
if (!news_array[current_news_index+3].toObject()["message"].toString().isEmpty())
    ui->ln_4->setText(news_array[current_news_index+3].toObject()["message"].toString());
}


void Form::on_pushButton_2_clicked()
{
    if(current_news_index + 4 > news_array.size()-1) return;
    current_news_index +=4;
    current_view_index += 1;
    ui->label_6->setText(QString::number(current_view_index));
    ui->ln_1->clear(); ui->ph_1->clear();
    ui->ln_2->clear(); ui->ph_2->clear();
    ui->ln_3->clear(); ui->ph_3->clear();
    ui->ln_4->clear(); ui->ph_4->clear();
    emit has_news();
}

void Form::on_pushButton_clicked()
{
    if(current_news_index == 0) return;
    current_news_index -= 4;
    current_view_index -=1;
    ui->label_6->setText(QString::number(current_view_index));
    emit has_news();
}

void Form::on_listWidget_itemClicked(QListWidgetItem *item)
{
    //qDebug() << "ok";
}

void Form::on_pushButton_3_clicked()
{
    fb->fbPostMessage(ui->le_post->text());
    QJsonObject feed = fb->fbRequest("me/feed", "");
    news_array = feed["data"].toArray();
    emit has_news();
}
