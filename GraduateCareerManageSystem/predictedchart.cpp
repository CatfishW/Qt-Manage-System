#include "predictedchart.h"
#include "ui_predictedchart.h"

PredictedChart::PredictedChart(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PredictedChart)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::FramelessWindowHint);
    QChart *chart_predicted_postgraduate = new QChart();
    chart_predicted_postgraduate->addSeries(series_postgraduate);
    chart_predicted_postgraduate->setTitle("考研数据可视化");
    axisX_postgraduate = new QValueAxis();
    axisX_postgraduate->setRange(0, 50);
    axisX_postgraduate->setTitleText("学生人数");
    axisX_postgraduate->setLabelFormat("%d");
    axisY_postgraduate = new QValueAxis();
    axisY_postgraduate->setRange(0, 50);
    axisY_postgraduate->setTitleText("考研人数");
    axisY_postgraduate->setLabelFormat("%d");
    chart_predicted_postgraduate->addAxis(axisX_postgraduate, Qt::AlignBottom);
    chart_predicted_postgraduate->addAxis(axisY_postgraduate, Qt::AlignLeft);
    series_postgraduate = new QLineSeries();
    series_postgraduate->attachAxis(axisX_postgraduate);
    series_postgraduate->attachAxis(axisY_postgraduate);
}
PredictedChart::~PredictedChart()
{
    delete ui;
}
