// обеспечивает интерфейс входа

#ifndef FBLOGINWIDGET_H
#define FBLOGINWIDGET_H

#include <QWidget>
#include <QWebEngineView>
#include <QWebEnginePage>
#include <QWebEngineProfile>
#include <QWebEngineCookieStore>
#include <QUrlQuery>
#include <QUrl>

#define APP_ID  "1813896548883742"


namespace Ui {
class fbLoginWidget;
}

class fbLoginWidget : public QWidget
{
    Q_OBJECT

public:
    explicit fbLoginWidget(QWidget *parent = 0);
    ~fbLoginWidget();

signals:
    void token_get(QUrlQuery _qurl);
private slots:
    void on_pb1_clicked();
    void urlChanged(QUrl _url);

    void on_pb2_clicked();

private:
    Ui::fbLoginWidget *ui;
    QWebEngineView * web;

    bool new_user = false;
};

#endif // FBLOGINWIDGET_H
