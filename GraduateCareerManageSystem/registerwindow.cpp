#include "registerwindow.h"
#include "ui_registerwindow.h"
#include<QGraphicsDropShadowEffect>
#include<QPropertyAnimation>
#include"loginwindow.h"

RegisterWindow::RegisterWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::RegisterWindow)
{
    ui->setupUi(this);
}

RegisterWindow::~RegisterWindow()
{
    delete ui;
}

void RegisterWindow::on_pushButton_clicked()
{
    RegisterWindow::close();
}


void RegisterWindow::on_get_back_to_login_button_clicked()
{
    LoginWindow *log_win = new LoginWindow;
    log_win->setWindowFlags(Qt::FramelessWindowHint);
    log_win->show();
    this->close();
}


void RegisterWindow::on_reg_button_clicked()
{
    QString username = ui->user_line_edit->text();
    QString password = ui->password_line_edit->text();
    QSqlQuery query;
    query.prepare("INSERT INTO user (username, password) VALUES (:username, :password)");
    query.bindValue(":username", username);
    query.bindValue(":password", password);
    if (!query.exec()) {
            QMessageBox::warning(this, tr("错误"), tr("注册失败"));
            return;
        }
    // 显示注册成功消息
    QMessageBox::information(this, tr("成功"), tr("注册成功"));
    this->close();
    LoginWindow *log_win = new LoginWindow;
    log_win->setWindowFlags(Qt::FramelessWindowHint);
    log_win->show();
}
//拖拽操作
void RegisterWindow::mousePressEvent(QMouseEvent *event)
    {
        if (event->button() == Qt::LeftButton) {
            m_dragPos = event->globalPos() - frameGeometry().topLeft();
            event->accept();
        }
    }

void RegisterWindow::mouseMoveEvent(QMouseEvent *event)
    {
        if (event->buttons() & Qt::LeftButton) {
            move(event->globalPos() - m_dragPos);
            event->accept();
        }
    }

void RegisterWindow::mouseReleaseEvent(QMouseEvent *event)
    {
        if (event->button() == Qt::LeftButton) {
            m_dragPos = QPoint();
            event->accept();
        }
    }

