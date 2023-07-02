#ifndef QUERY_H
#define QUERY_H

#include <QDialog>
//#include<mainwindow.h>
namespace Ui {
class query;
}

class query : public QDialog
{
    Q_OBJECT

public:
    explicit query(QWidget *parent = nullptr);
    ~query();

private slots:
    void on_pushButton_clicked();
public slots:
    void querydata_receive(QString data1,QString data2,QString data3,QString data4, QString data5,QString type);
private:
    Ui::query *ui;
    //MainWindow *main_win;
};

#endif // QUERY_H
