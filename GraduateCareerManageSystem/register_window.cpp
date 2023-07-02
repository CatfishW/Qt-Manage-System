#include "register_window.h"
#include "ui_register_window.h"
#include<QGraphicsDropShadowEffect>
register_window::register_window(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::register_window)
{
    register_window::setWindowFlags(Qt::FramelessWindowHint);
    ui->setupUi(this);
    QGraphicsDropShadowEffect *shadow_effect = new QGraphicsDropShadowEffect(this);
    shadow_effect->setOffset(-5, 5);
    shadow_effect->setColor(Qt::gray);
    shadow_effect->setBlurRadius(8);
    ui->right_frame->setGraphicsEffect(shadow_effect);
}

register_window::~register_window()
{
    delete ui;
}


void register_window::on_close_button_2_clicked()
{
    register_window::close();
}

