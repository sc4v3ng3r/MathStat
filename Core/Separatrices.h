#ifndef SEPARATRICES_H
#define SEPARATRICES_H

#include "Number.h"
#include <Qt/qobject.h>

class SampleSpaceModel;
class StatClass;

class Separatrices : public QObject {
  
private:
  
  Q_OBJECT
  Number m_mode;
  Number m_averageBySum;
  Number m_averageByHalfPoint;
  Number m_median;
  Number m_quartil;
  Number m_decil;
  Number m_percentil;
  Number m_variance;
  Number const *m_width;
  QList<StatClass> const *  m_statClasses;
  QList<Number> const *m_rol;
  
  
  inline void setAverageBySum(const QList<Number>& rol);
  inline void setAverageByHalfPoint(const QList<StatClass>& statisticClasses, const uint rolSize);
  inline void setMedian(const QList<StatClass>& statisticClasses, const uint modalClassIndex, 
			const uint rolSize, const Number& h);
  void setMode(const QList<StatClass>& statisticClasses, const uint modalClassIndex, const Number& h);
  void setVariance(const QList<Number>& rol);
  void clear();

public:
  
  Separatrices(const QList<Number>& rol, const QList<StatClass>& statisticClasses, 
	       const uint modalClassIndex, const Number& h,QObject *parent = 0);
  Separatrices(const Separatrices& s, QObject* parent=0);
  virtual ~Separatrices();
  
  Number mode() const;
  Number variance() const;
  
  Number median() const;
  Number quartil(const int q);
  Number decil(const int d);
  Number percentis(const int p);
  
  Number averageBySum() const;
  Number averageByHalfPoint() const;
  void redefine(const QList<Number>& rol, const QList<StatClass>& statisticClasses,
		const uint modalClassIndex, const Number& h);
  /*
public Q_SLOTS:
  
Q_SIGNALS:
  */
};
#endif