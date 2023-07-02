#include "delete_dia.h"
#include "ui_delete_dia.h"

delete_dia::delete_dia(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::delete_dia)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::FramelessWindowHint);
}
delete_dia::~delete_dia()
{
delete_dia ui;
}

void delete_dia::on_pushButton_clicked()
{
    this->close();
}


void delete_dia::on_pushButton_2_clicked()
{
    QString data1 = ui->company_name->text();
    QString data2 = ui->student_id->text();
    if (data1 == "" and data2 == "")
        QMessageBox::warning(this,"提示","刪除的信息不能为空");
    emit deletedata(data1,data2);
    this->close();
}
//拖拽操作
void delete_dia::mousePressEvent(QMouseEvent *event)
    {
        if (event->button() == Qt::LeftButton) {
            m_dragPos = event->globalPos() - frameGeometry().topLeft();
            event->accept();
        }
    }

void delete_dia::mouseMoveEvent(QMouseEvent *event)
    {
        if (event->buttons() & Qt::LeftButton) {
            move(event->globalPos() - m_dragPos);
            event->accept();
        }
    }

void delete_dia::mouseReleaseEvent(QMouseEvent *event)
    {
        if (event->button() == Qt::LeftButton) {
            m_dragPos = QPoint();
            event->accept();
        }
    }

