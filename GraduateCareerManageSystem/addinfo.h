#ifndef ADDINFO_H
#define ADDINFO_H

#include <QWidget>
#include<QMessageBox>
#include<QMouseEvent>
namespace Ui {
class addinfo;
}

class addinfo : public QWidget
{
    Q_OBJECT

public:
    explicit addinfo(QWidget *parent = nullptr);
    ~addinfo();
signals:
    void datasignal(QString data1,QString data2,QString data3,QString data4,QString data5,QString type);
private slots:
    void on_back_btn_clicked();

    void on_confirm_btn_clicked();
    void on_radioButton_2_clicked();

    void on_radioButton_clicked();

protected:
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
private:
    Ui::addinfo *ui;
    QPoint m_dragPos;
};

#endif // ADDINFO_H
