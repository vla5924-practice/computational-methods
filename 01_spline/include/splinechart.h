#pragma once

#include <limits>

#include <QChart>
#include <QLineSeries>
#include <QScatterSeries>
#include <QValueAxis>

#include "spline.h"

constexpr double SPLINECHART_STEP = 100.;

class SplineChart : public QtCharts::QChart
{
    Q_OBJECT

protected:
    QtCharts::QLineSeries    *p_spline_series;
    QtCharts::QScatterSeries *p_points_series;

    QtCharts::QValueAxis *p_axis_x;
    QtCharts::QValueAxis *p_axis_y;

    qreal m_min_x;
    qreal m_max_x;
    qreal m_min_y;
    qreal m_max_y;

public:
    explicit SplineChart(QGraphicsItem *parent = nullptr);
    ~SplineChart();

    void load(const Spline& spline);
};
