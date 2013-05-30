#ifndef HISTOGRAM_H
#define HISTOGRAM_H

#include <qwt/qwt_plot.h>
#include <qwt/qwt_plot_histogram.h>
#include <qwt/qwt_interval.h>
#include <qwt/qwt_plot_curve.h>

class Histogram : public QwtPlot{
  Q_OBJECT
    
public:
  /* this enum is for state of histogram, it say what kind of graphic must be showed*/
  enum GraphicType{ Absolute=2, Relative=4, Percents=6 };
 
  Histogram(QWidget* parent=0);
  virtual ~Histogram();
  Histogram::GraphicType state() const;
  void setState(const Histogram::GraphicType& state);
 // int state() const;
  
public Q_SLOTS:
  void setNewSamples(const QVector < QwtIntervalSample >& intervals);

Q_SIGNALS:
  void stateChanged(Histogram::GraphicType newState);

private:
  QwtPlotHistogram m_histograms;
  QwtPlotCurve m_curve;
  Histogram::GraphicType m_state;
  
  void setMark(/*const QVector<QwtIntervalSample>& intervals*/);
};
#endif