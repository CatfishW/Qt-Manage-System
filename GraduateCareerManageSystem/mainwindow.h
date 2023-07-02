#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include<QMouseEvent>
#include <QFile>
#include <QTextStream>
#include <QtCore/QPropertyAnimation>
#include <QtCharts>
#include<QGraphicsScene>
#include<addinfo.h>
#include<query.h>
#include<QtDebug>
#include<delete_dia.h>
#include<QtSql>
#include<D:\qtexercise\LinearRegression.h>
#include<addinfo.h>
//#include "predictedchart.h"
QT_CHARTS_USE_NAMESPACE
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
//public:
//    QSqlDatabase db;
signals:
    void querydata(QString data1,QString data2,QString data3,QString data4, QString data5,QString type);
private slots:
    void on_close_btn_clicked();

    void on_maxmize_btn_clicked();

    void on_minimize_btn_clicked();

    void on_menu_btn_clicked();

    void on_add_btn_clicked();

    void updatechart();

    void AddData(QString data1,QString data2,QString data3,QString data4,QString data5,QString type);

    void on_query_btn_company_clicked();

    void on_query_btn_student_clicked();

    void on_delete_file_btn_clicked();

    void deletedata_receive(QString data1,QString data2);

    void datapredict();

    void on_data_btn_clicked();

protected:
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
private:
    Ui::MainWindow *ui;
    QPoint m_dragPos;
    addinfo *info_win;
    query *query_win1,*query_win2;
    delete_dia *delete_win;
    QLineSeries *series_postgraduate;
    QLineSeries *series_student;
    int student_count,post_graduate_count,graduate_count;
    QValueAxis *axisX_postgraduate;
    QValueAxis *axisY_postgraduate;
    QValueAxis *axisX_student;
    QValueAxis *axisY_student;
    LinearRegression *LR;
    bool timer_stop = false;
    //PredictedChart *predchart;
};
#endif // MAINWINDOW_H
