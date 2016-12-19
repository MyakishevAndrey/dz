#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    setFixedSize(size());


    fb = new fbConnect();
    fblogin = new fbLoginWidget(this);

    connect(fblogin, SIGNAL(token_get(QUrlQuery)), fb, SLOT(token_get(QUrlQuery)));
    connect(fb, SIGNAL(ready()), this, SLOT(on_fb_ready()));
}

Widget::~Widget()
{
    delete ui;
    delete fb;
}

void Widget::on_fb_ready()
{
    fblogin->close();
    form = new Form(fb, this);
}
