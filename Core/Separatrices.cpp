#include "Separatrices.h"
#include "../Models/SampleSpaceModel.h"
#include "StatClass.h"
#include <Qt/qdebug.h>
#include <math.h>

Separatrices::Separatrices(const QList<Number>& rol, const QList< StatClass >& statisticClasses,
			   const uint modalClassIndex, const Number& h,QObject* parent): QObject(parent), m_averageBySum(0) 
  , m_averageByHalfPoint(0)
  , m_mode(0)
  , m_median(0)
  , m_quartil(0)
  , m_decil(0)
  , m_percentil(0)
  , m_variance(0)
{
  setAverageBySum(rol);
  setAverageByHalfPoint(statisticClasses, rol.size());
  setMedian(statisticClasses,modalClassIndex,rol.size(), h);
  setMode(statisticClasses, modalClassIndex,h);
  setVariance(rol);
}

Separatrices::Separatrices(const Separatrices& s, QObject* parent): QObject(parent)
  , m_averageByHalfPoint(s.m_averageByHalfPoint)
  , m_averageBySum(s.m_averageBySum)
  , m_mode(s.m_mode)
  , m_median(s.m_median)
  , m_quartil(s.m_quartil)
  , m_decil(s.m_decil)
  , m_percentil(s.m_percentil)
{

}

void Separatrices::setAverageByHalfPoint(const QList< StatClass >& statisticClasses, const uint rolSize)
{
  m_averageByHalfPoint = 0;
  for(QList<StatClass>::const_iterator it = statisticClasses.constBegin();
    it != statisticClasses.constEnd(); it++)
      m_averageByHalfPoint = m_averageByHalfPoint + ( (*it).halfPoint() * (*it).absoluteFrequency());
    
  m_averageByHalfPoint = m_averageByHalfPoint / rolSize;
  return;
}

void Separatrices::setAverageBySum(const QList<Number>& rol)
{
  
 for(QList<Number>::const_iterator it = rol.constBegin(); it != rol.constEnd(); it++)
   m_averageBySum = m_averageBySum + (*it);
 
 m_averageBySum = m_averageBySum / rol.size();
 
 return;
}

/* Median is calculate by (Linf + [(n/2) - Fiac BeforeClass] * h) / fiModalClass
 */
void Separatrices::setMedian(const QList< StatClass >& statisticClasses, const uint modalClassIndex, 
			     const uint rolSize, const Number& h)
{
  m_median = 0;
/*   WARNING 1 FAZER ESSES CALCULOS EM UMA LINHA.. ESTA FUNCIONANDO MAS, DA PARA MELHORAR
   NAO VOU FAZER ISSO AGORA POIS TENHO MUITAS OUTRAS COISAS P/ FAZER...
   
   O AVISO 2 JA FOI CONSERTADO!
  WARNING 2 TEM UM SERIO PROBLEMA AQUI, OBSERVE QUE SE O modalClassPosition = 0, teremos um -1, e logo
   um erro em runTIme, neste caso, a linha statisticClasses[modalClassIndex-1].absoluteFrequencyAcumulated() deve ser 0
*/
  if (!modalClassIndex)
    m_median = (rolSize/2);
  else 
    m_median =  ((rolSize/2) - statisticClasses[modalClassIndex-1].absoluteFrequencyAcumulated());
  
  m_median = (m_median*h) / statisticClasses[modalClassIndex].absoluteFrequency();
  m_median = statisticClasses[modalClassIndex].begin() + m_median;
  return;
}

void Separatrices::setMode(const QList< StatClass >& statisticClasses, const uint modalClassIndex, const Number& h)
{
 Number d1, d2;
 
 if (!modalClassIndex)
   d1 = (statisticClasses[modalClassIndex].absoluteFrequency()); 
 else
   d1 = statisticClasses[modalClassIndex].absoluteFrequency() - statisticClasses[modalClassIndex-1].absoluteFrequency();
 
 if (modalClassIndex+1 >= statisticClasses.size())
   d2 = statisticClasses[modalClassIndex].absoluteFrequency();
 else
   d2 = statisticClasses[modalClassIndex].absoluteFrequency() - statisticClasses[modalClassIndex+1].absoluteFrequency();
 
 //qDebug() << "In mode:" << d1.toString() << "/" << d1.toString() << "+" << d2.toString() << " * " << h.toString();
 m_mode = statisticClasses[modalClassIndex].begin() + ( (d1/(d1+d2))*h );
 
 return;
}

void Separatrices::setVariance(const QList< Number >& rol)
{
  m_variance = 0;
  for(QList<Number>::const_iterator it = rol.begin(); it < rol.end(); it++){
    m_variance = (m_variance + pow((*it - m_averageBySum).toDouble(),2));
  }
  
  qDebug() << "Variance sum is " << m_variance.toString();
  m_variance = pow ((m_variance / (rol.size()-1)).toDouble(),2);
  qDebug() << "Variance sum " << m_variance.toString();
  return;
}

Number Separatrices::averageBySum() const { return m_averageBySum; }

Number Separatrices::averageByHalfPoint() const { return m_averageByHalfPoint; }

Number Separatrices::mode() const { return m_mode; }

Number Separatrices::median() const { return m_median; }

Number Separatrices::variance() const { return m_variance; }

Number Separatrices::quartil(const int q)
{

}

Number Separatrices::decil(const int d)
{

}

Number Separatrices::percentis(const int p)
{

}

Separatrices::~Separatrices()
{

}

void Separatrices::clear()
{
  m_averageByHalfPoint = 0;
  m_averageBySum = 0;
  m_decil = 0;
  m_median = 0;
  m_mode = 0;
  m_quartil = 0;
  m_percentil = 0;
  return;
}

void Separatrices::redefine(const QList< Number >& rol, const QList< StatClass >& statisticClasses, 
			    const uint modalClassIndex, const Number& h)
{
  clear();
  setAverageBySum(rol);
  setAverageByHalfPoint(statisticClasses,rol.size());
  setMedian(statisticClasses,modalClassIndex,rol.size(),h);
  setMode(statisticClasses,modalClassIndex,h);
  setVariance(rol);
}
