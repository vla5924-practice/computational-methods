#pragma once

#include <QChart>

#include <QLineSeries>
#include <QScatterSeries>
#include <QValueAxis>

#include "spline.h"

class SplineChart : public QtCharts::QChart
{
    Q_OBJECT

protected:
    QtCharts::QLineSeries    *p_spline_series;
    QtCharts::QScatterSeries *p_points_series;

    QtCharts::QValueAxis *p_axis_x;
    QtCharts::QValueAxis *p_axis_y;

    qreal min_x;
    qreal max_x;
    qreal min_y;
    qreal max_y;

public:
    explicit SplineChart(QGraphicsItem *parent = nullptr);
    ~SplineChart();

    void load(const Spline& spline);
};
