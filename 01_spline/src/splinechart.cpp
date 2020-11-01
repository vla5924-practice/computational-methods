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

    min_x = max_x = min_y = max_y = 0;
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
    for (auto i = spline.points().begin(); i != spline.points().end(); i++)
    {
        *p_points_series << *i;

        if (i->x() < min_x)
        {
            min_x = i->x();
        }
        else if (i->x() > max_x)
        {
            max_x = i->x();
        }
        if (i->y() < min_y)
        {
            min_y = i->y();
        }
        else if (i->y() > max_y)
        {
            max_y = i->y();
        }
    }

    p_spline_series->clear();
    if (spline.points().size() > 2)
    {
        for (size_t i = 0; i < spline.points().size() - 1; i++)
        {
            for (qreal j = spline.points()[i].x(); j < spline.points()[i + 1].x(); j += ( spline.points()[i + 1].x() - spline.points()[i].x()) / 100)
            {
                double a = spline.a()[i];
                double b = spline.a()[i];
                double c = spline.a()[i];
                double d = spline.a()[i];
                double x = spline.points()[i + 1].x();
                double value = a + b * (j - x) + c * (j - x) * (j - x) + d * (j - x) * (j - x) * (j - x);
                *p_spline_series << QPointF(j, value);
            }
        }
    }

    p_axis_x->setRange(min_x, max_x);
    p_axis_y->setRange(min_y, max_y);

}
