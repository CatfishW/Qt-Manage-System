#ifndef DELETE_DIA_H
#define DELETE_DIA_H

#include <QDialog>
#include<QMessageBox>
#include<QMouseEvent>
namespace Ui {
class delete_dia;
}

class delete_dia : public QDialog
{
    Q_OBJECT

public:
    explicit delete_dia(QWidget *parent = nullptr);
    ~delete_dia();
signals:
    void deletedata(QString data1,QString data2);
private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();
protected:
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
private:
    Ui::delete_dia *ui;
    QPoint m_dragPos;
};

#endif // DELETE_DIA_H
