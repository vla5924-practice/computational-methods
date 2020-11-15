#pragma once

#include <limits>

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
    QtCharts::QLineSeries    *p_axis_h_series;
    QtCharts::QLineSeries    *p_axis_v_series;
    QtCharts::QScatterSeries *p_points_series;

    QtCharts::QValueAxis *p_axis_x;
    QtCharts::QValueAxis *p_axis_y;

    qreal m_min_x;
    qreal m_max_x;
    qreal m_min_y;
    qreal m_max_y;

    void resetRanges();

public:
    explicit SplineChart(QGraphicsItem *parent = nullptr);
    ~SplineChart();

    void load(const Spline& spline);

public slots:
    void showPointLabels(const QPointF&, bool hovered);
    void clear();

signals:
    void proceed(int current, int total, const QString& message);
};
