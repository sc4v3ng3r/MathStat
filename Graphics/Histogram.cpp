#include "Histogram.h"
#include <QtGui/qtoolbar.h>
#include <QtGui/qstyle.h>
#include <Qt/qaction.h>
#include <QPointF>
#include <qwt/qwt_plot_canvas.h>

Histogram::Histogram(QWidget* parent): QwtPlot(parent) // qwidget
  , m_histograms(QString())// give a name
  , m_state(Absolute)
  , m_curve("CurveTest")
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
 setMark();
}

void Histogram::setState(const Histogram::GraphicType& state)
{ m_state = state;  emit stateChanged(m_state); return; }

void Histogram::setNewSamples(const QVector< QwtIntervalSample >& intervals)
{
  m_histograms.setSamples(intervals);
  setMark();
  return;
}

Histogram::GraphicType Histogram::state() const
{
  return m_state;
}

Histogram::~Histogram(){ }

void Histogram::setMark(/*const QVector< QwtIntervalSample >& intervals*/)
{
  /*
  QPointF x(3,9);
  QVector<QPointF> list;
  
  list.append(x);
  m_curve.setSamples(list);
  m_curve.setBrush(Qt::black);
  m_curve.setBaseline(15.6);
  m_curve.setTitle("Teste de Curva caralho!");
  m_curve.attach(this);
 //delete m_curve;

  */
}
