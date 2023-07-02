#include "loginwindow.h"
#include "ui_loginwindow.h"
#include"mainwindow.h"

LoginWindow::LoginWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::LoginWindow)
{
    ui->setupUi(this);
    ui->username_combobox->setEditable(true);

}

LoginWindow::~LoginWindow()
{
    delete ui;
}

void LoginWindow::on_close_button_clicked()
{
    LoginWindow::close();
}

void LoginWindow::on_minimize_button_clicked()
{
    LoginWindow::showMinimized();
}

void LoginWindow::on_Login_button_clicked()
{

    QString username,password;
    username = ui->username_combobox->currentText();
    password = ui->password_lineedit->text();
    if (username == "" && password == "")
    QMessageBox::warning(this,"","用户名与密码不能为空");
    else if(username=="")
    QMessageBox::warning(this,"","用户名不能为空");
    else if (password=="")
    QMessageBox::warning(this,"","密码不能为空");



    QSqlQuery query;
    query.exec(QString("SELECT * FROM user WHERE username='%1' AND password='%2'").arg(username).arg(password));
    // 检查是否有匹配的用户
    if (username != "" && password != ""){
       if (query.next()) {
           this->close();
           //static QMovie movie("loading.gif");
           //QLabel *label = new QLabel(this);
           //label->setMovie(&movie);
           //movie.start();
           //label->show();
           main_win.show();
       } else {
           QMessageBox::warning(this, tr("错误"), tr("用户名或密码不正确"));
       }
    }
}

void LoginWindow::on_Register_button_clicked()
{
    reg_win.setWindowFlags(Qt::FramelessWindowHint);
    this->hide();
    QPropertyAnimation *animation = new QPropertyAnimation();
    animation->setTargetObject(reg_win.centralWidget());
    animation->setDuration(2000);
    QGraphicsOpacityEffect* m_pOpacity = new QGraphicsOpacityEffect();
    reg_win.centralWidget()-> setGraphicsEffect(m_pOpacity);
    m_pOpacity->setOpacity(1);
    animation->setTargetObject(m_pOpacity);
    animation->setPropertyName("opacity");
    animation->setStartValue(0);
    animation->setEndValue(1);
    animation->start();
    reg_win.show();
    reg_win.centralWidget()->setGraphicsEffect(m_pOpacity);
}
//拖拽操作
void LoginWindow::mousePressEvent(QMouseEvent *event)
    {
        if (event->button() == Qt::LeftButton) {
            m_dragPos = event->globalPos() - frameGeometry().topLeft();
            event->accept();
        }
    }

void LoginWindow::mouseMoveEvent(QMouseEvent *event)
    {
        if (event->buttons() & Qt::LeftButton) {
            move(event->globalPos() - m_dragPos);
            event->accept();
        }
    }

void LoginWindow::mouseReleaseEvent(QMouseEvent *event)
    {
        if (event->button() == Qt::LeftButton) {
            m_dragPos = QPoint();
            event->accept();
        }
    }








