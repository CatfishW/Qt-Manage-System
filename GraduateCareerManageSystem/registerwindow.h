#ifndef REGISTERWINDOW_H
#define REGISTERWINDOW_H

#include <QMainWindow>
#include<QMessageBox>
namespace Ui {
class RegisterWindow;
}

class RegisterWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit RegisterWindow(QWidget *parent = nullptr);
    ~RegisterWindow();
public:
protected:
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
private slots:
    void on_pushButton_clicked();

    void on_get_back_to_login_button_clicked();

    void on_reg_button_clicked();

private:
    Ui::RegisterWindow *ui;
    QPoint      m_dragPos;
};

#endif // REGISTERWINDOW_H
