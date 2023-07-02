#ifndef LOGINWINDOW_H
#define LOGINWINDOW_H

#include <QMainWindow>
#include"registerwindow.h"
#include<QtSql>
#include"mainwindow.h"
#include<QMouseEvent>
#include<QGraphicsOpacityEffect>
#include <QMovie>
#include<QMessageBox>
namespace Ui {
class LoginWindow;
}

class LoginWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit LoginWindow(QWidget *parent = nullptr);
    ~LoginWindow();
public:
    RegisterWindow reg_win;
    MainWindow main_win;
private slots:
    void on_close_button_clicked();

    void on_minimize_button_clicked();

    void on_Login_button_clicked();

    void on_Register_button_clicked();


protected:
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
private:
    Ui::LoginWindow *ui;
    QPoint      m_dragPos;
};

#endif // LOGINWINDOW_H
