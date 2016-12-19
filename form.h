// основное окно с информацией

#ifndef FORM_H
#define FORM_H

#include <QWidget>
#include "fbconnect.h"

namespace Ui {
class Form;
}

class Form : public QWidget
{
    Q_OBJECT
public:
    explicit Form(fbConnect * _fb, QWidget *parent = 0);
    ~Form();

private:
    Ui::Form *ui;
    fbConnect * fb;

    void setPDataToLabels();
    void on_listWidget_itemClicked(QListWidgetItem *item);

    QString my_name;
    QString my_id;
    QString my_email;
    QString photo_url;
    QString photo_url_for_news;
    QPixmap my_photo;
    QPixmap my_photo_for_news;
    QJsonArray friends_array;

    QJsonArray news_array;

    int current_news_index = 0;
    int current_view_index = 1;

    QString feed_info(QString id, QLabel *label,QLabel *label_2);

private slots:
    void set_friends();
    void set_news();
    void on_pushButton_2_clicked();
    void on_pushButton_clicked();

    void on_pushButton_3_clicked();

signals:
    void has_news();
    void has_friends();
};

#endif // FORM_H
