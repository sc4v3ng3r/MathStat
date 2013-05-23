#include "Histogram.h"
#include <QtGui/qtoolbar.h>
#include <QtGui/qstyle.h>
#include <Qt/qaction.h>
#include <qwt/qwt_plot_canvas.h>
Histogram::Histogram(QWidget* parent): QwtPlot(parent) // qwidget
  , m_histograms(QString())// give a name
  , m_state(Absolute)
{
 setWindowTitle("Histogram");
 
 this->setAxisTitle(QwtPlot::xBottom,"Width");
 this->setAxisTitle(QwtPlot::yLeft,"Frequency Absolute");
 this->setMinimumSize(400,300);
 this->setMaximumSize(600,500);
 this->setAutoReplot(true);
 setAutoFillBackground(true);
 setPalette(Qt::gray);
 canvas()->setPalette(Qt::white);
 m_histograms.setBrush(QBrush(Qt::red));
 m_histograms.attach(this);
}

void Histogram::setState(const Histogram::GraphicType& state)
{ m_state = state;  emit stateChanged(m_state); return; }

void Histogram::setNewSamples(const QVector< QwtIntervalSample >& intervals)
{
  m_histograms.setSamples(intervals);
  return;
}

Histogram::GraphicType Histogram::state() const
{
  return m_state;
}

Histogram::~Histogram(){}
