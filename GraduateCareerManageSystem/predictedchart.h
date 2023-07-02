#ifndef PREDICTEDCHART_H
#define PREDICTEDCHART_H

#include <QWidget>
#include <QtCharts>
namespace Ui {
class PredictedChart;
}

class PredictedChart : public QWidget
{
    Q_OBJECT

public:
    explicit PredictedChart(QWidget *parent = nullptr);
    ~PredictedChart();

private:
    Ui::PredictedChart *ui;
    QLineSeries *series_postgraduate;
    QValueAxis *axisX_postgraduate;
    QValueAxis *axisY_postgraduate;
};

#endif // PREDICTEDCHART_H
