#include "query.h"
#include "ui_query.h"

query::query(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::query)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::FramelessWindowHint);
}

query::~query()
{
    delete ui;
}
void query::querydata_receive(QString data1,QString data2,QString data3,QString data4, QString data5,QString type){
    if(type == "company")
    {
        ui->result_1->setText(data1);
        ui->result_2->setText(data2);
        ui->result_3->setText(data3);
        ui->result_4->setText(data4);
        ui->result_5->setText(data5);
    }
    if(type == "student")
    {
        ui->query_1->setText("学生姓名");
        ui->query_2->setText("学号");
        ui->query_3->setText("是否考研");
        ui->query_4->setText("是否就业");
        ui->query_5->setText("专业");
        ui->result_1->setText(data1);
        ui->result_2->setText(data2);
        ui->result_3->setText(data3);
        ui->result_4->setText(data4);
        ui->result_5->setText(data5);
    }
}
void query::on_pushButton_clicked()
{
    this->close();
}

