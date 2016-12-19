//основное окно

#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include "fbconnect.h"
#include "fbloginwidget.h"
#include "form.h"

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();
public slots:
    void on_fb_ready();
private:
    Ui::Widget *ui;
    fbConnect * fb;
    fbLoginWidget * fblogin;
    Form * form;
};

#endif // WIDGET_H
