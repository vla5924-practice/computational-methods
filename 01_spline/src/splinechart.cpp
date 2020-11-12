#include "splinechart.h"

SplineChart::SplineChart(QGraphicsItem  *parent) : QtCharts::QChart(parent)
{
    this->legend()->hide();

    p_spline_series = new QtCharts::QLineSeries();
    p_spline_series->setColor(QColorConstants::Blue);
    p_points_series = new QtCharts::QScatterSeries();
    p_points_series->setColor(QColorConstants::Blue);
    this->addSeries(p_spline_series);
    this->addSeries(p_points_series);

    p_axis_x = new QtCharts::QValueAxis();
    p_axis_x->setTitleText("x");
    this->addAxis(p_axis_x, Qt::AlignBottom);

    p_axis_y = new QtCharts::QValueAxis();
    p_axis_y->setTitleText("y");
    this->addAxis(p_axis_y, Qt::AlignLeft);

    p_spline_series->attachAxis(p_axis_x);
    p_spline_series->attachAxis(p_axis_y);
    p_points_series->attachAxis(p_axis_x);
    p_points_series->attachAxis(p_axis_y);

    m_min_x = m_min_y = std::numeric_limits<double>::max();
    m_max_x = m_max_y = -std::numeric_limits<double>::max();
}

SplineChart::~SplineChart()
{
    delete p_spline_series;
    delete p_points_series;
    delete p_axis_x;
    delete p_axis_y;
}

void SplineChart::load(const Spline& spline)
{
    p_points_series->clear();
    for (const auto& point : spline.points())
    {
        *p_points_series << point;
        if (point.x() < m_min_x)
            m_min_x = point.x();
        else if (point.x() > m_max_x)
            m_max_x = point.x();
        if (point.y() < m_min_y)
            m_min_y = point.y();
        else if (point.y() > m_max_y)
            m_max_y = point.y();
    }
    p_spline_series->clear();
    if (spline.points().size() >= SPLINE_COUNT_POINTS_MIN)
        for (size_t i = 1; i < spline.points().size(); i++)
        {
            const auto& pt = spline.points()[i];
            const auto& pt_prev = spline.points()[i - 1];
            for (qreal x = pt_prev.x(); x < pt.x(); x += 1. / SPLINECHART_STEP)
                *p_spline_series << QPointF(x, spline.interpolatedValue(i, x));
        }
    p_axis_x->setRange(m_min_x, m_max_x);
    p_axis_y->setRange(m_min_y, m_max_y);
}
