#include "addinfo.h"
#include "ui_addinfo.h"

addinfo::addinfo(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::addinfo)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::FramelessWindowHint);
    ui->radioButton->setChecked(true);
}

addinfo::~addinfo()
{
    delete ui;
}

void addinfo::on_back_btn_clicked()
{
    this->close();
}


void addinfo::on_confirm_btn_clicked()
{
    //QString data = ui->company_or_student_name->toPlainText();
    QString data1 = ui->company_or_student_name->toPlainText();
    QString data2 = ui->companytype_or_major->toPlainText();
    QString data3 = ui->admitreq_or_exam->toPlainText();
    QString data4 = ui->hirenum_or_stuid->toPlainText();
    QString data5 = ui->publisher_or_ifjob->toPlainText();
    bool check_company = ui->radioButton->isChecked();
    bool check_stu = ui->radioButton_2->isChecked();
    if (data1 == NULL or data2 == NULL or data3 == NULL or data4 == NULL or data5 == NULL)
        QMessageBox::warning(this,"警告","所有信息内容都不能为空");
    else if(data1!=NULL and data2!=NULL and data3!=NULL and data4!=NULL and data5!=NULL and check_company == true)

        {QString type = "company";emit datasignal(ui->company_or_student_name->toPlainText(),ui->companytype_or_major->toPlainText(),ui->admitreq_or_exam->toPlainText(),ui->hirenum_or_stuid->toPlainText(),ui->publisher_or_ifjob->toPlainText(),type);
        QMessageBox::information(this,"提示","企业信息上传成功");this->hide();}
    else if(data1!=NULL and data2!=NULL and data3!=NULL and data4!=NULL and data5!=NULL and check_stu == true)
        {QString type = "student";emit datasignal(ui->company_or_student_name->toPlainText(),ui->companytype_or_major->toPlainText(),ui->admitreq_or_exam->toPlainText(),ui->hirenum_or_stuid->toPlainText(),ui->publisher_or_ifjob->toPlainText(),type);
        QMessageBox::information(this,"提示","学生信息上传成功");this->hide();}
}
//拖拽操作
void addinfo::mousePressEvent(QMouseEvent *event)
    {
        if (event->button() == Qt::LeftButton) {
            m_dragPos = event->globalPos() - frameGeometry().topLeft();
            event->accept();
        }
    }

void addinfo::mouseMoveEvent(QMouseEvent *event)
    {
        if (event->buttons() & Qt::LeftButton) {
            move(event->globalPos() - m_dragPos);
            event->accept();
        }
    }

void addinfo::mouseReleaseEvent(QMouseEvent *event)
    {
        if (event->button() == Qt::LeftButton) {
            m_dragPos = QPoint();
            event->accept();
        }
    }


void addinfo::on_radioButton_2_clicked()
{
    ui->admitreq_or_exam_label->setText("是否考研");
    ui->company_or_student_name_label->setText("学生姓名");
    ui->companytype_or_major_label->setText("专业");
    ui->hirenum_or_stuid_label->setText("学号");
    ui->publisher_or_ifjob_label->setText("是否就业");
}


void addinfo::on_radioButton_clicked()
{
    ui->admitreq_or_exam_label->setText("学历要求");
    ui->company_or_student_name_label->setText("公司名");
    ui->companytype_or_major_label->setText("企业类型");
    ui->hirenum_or_stuid_label->setText("招聘人数");
    ui->publisher_or_ifjob_label->setText("发布人");
}

