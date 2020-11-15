#include "splinechart.h"

constexpr double SPLINECHART_STEP = 0.01;

SplineChart::SplineChart(QGraphicsItem  *parent) : QtCharts::QChart(parent)
{
    this->legend()->hide();

    p_spline_series = new QtCharts::QLineSeries();
    p_spline_series->setColor(QColorConstants::Blue);
    p_points_series = new QtCharts::QScatterSeries();
    p_points_series->setColor(QColorConstants::Blue);
    p_axis_h_series = new QtCharts::QLineSeries();
    p_axis_h_series->setPen(QColor(0, 0, 0));
    p_axis_h_series->setOpacity(0.3);
    p_axis_v_series = new QtCharts::QLineSeries();
    p_axis_v_series->setPen(QColor(0, 0, 0));
    p_axis_v_series->setOpacity(0.3);
    this->addSeries(p_spline_series);
    this->addSeries(p_points_series);
    this->addSeries(p_axis_h_series);
    this->addSeries(p_axis_v_series);

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
    p_axis_h_series->attachAxis(p_axis_x);
    p_axis_h_series->attachAxis(p_axis_y);
    p_axis_v_series->attachAxis(p_axis_x);
    p_axis_v_series->attachAxis(p_axis_y);

    m_min_x = m_min_y = std::numeric_limits<double>::max();
    m_max_x = m_max_y = -std::numeric_limits<double>::max();

    connect(p_points_series, &QtCharts::QScatterSeries::hovered, this, &SplineChart::showPointLabels);
}

SplineChart::~SplineChart()
{
    delete p_spline_series;
    delete p_points_series;
    delete p_axis_h_series;
    delete p_axis_v_series;
    delete p_axis_x;
    delete p_axis_y;
}

void SplineChart::load(const Spline& spline)
{
    clear();
    emit proceed(1, 3, "Drawing points");
    for (const auto& point : spline.points())
    {
        p_points_series->append(point);
        if (point.x() < m_min_x)
            m_min_x = point.x();
        else if (point.x() > m_max_x)
            m_max_x = point.x();
        if (point.y() < m_min_y)
            m_min_y = point.y();
        else if (point.y() > m_max_y)
            m_max_y = point.y();
    }
    emit proceed(2, 3, "Rendering curve");
    if (spline.available())
        for (size_t i = 1; i < spline.points().size(); i++)
        {
            const auto& pt = spline.points()[i];
            const auto& pt_prev = spline.points()[i - 1];
            for (qreal x = pt_prev.x(); x < pt.x(); x += SPLINECHART_STEP)
            {
                double y = spline.interpolatedValue(i, x);
                p_spline_series->append(x, y);
                if (y < m_min_y)
                    m_min_y = y;
                else if (y > m_max_y)
                    m_max_y = y;
            }
        }
    emit proceed(3, 3, "Drawing axes");
    resetRanges();
    emit proceed(4, 3, "Finished");
}

void SplineChart::clear()
{
    p_points_series->clear();
    p_spline_series->clear();
    p_axis_h_series->clear();
    p_axis_v_series->clear();
}

void SplineChart::showPointLabels(const QPointF&, bool hovered)
{
    p_points_series->setPointLabelsVisible(hovered);
}

void SplineChart::resetRanges()
{
    qreal x_delta = (m_max_x - m_min_x) * 0.1;
    qreal y_delta = (m_max_y - m_min_y) * 0.1;
    p_axis_x->setRange(m_min_x - x_delta, m_max_x + x_delta);
    p_axis_y->setRange(m_min_y - y_delta, m_max_y + y_delta);
    p_axis_h_series->append(m_min_x - x_delta, 0);
    p_axis_h_series->append(m_max_x + x_delta, 0);
    p_axis_v_series->append(0, m_min_y - y_delta);
    p_axis_v_series->append(0, m_max_y + y_delta);
}
