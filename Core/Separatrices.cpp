#include "Separatrices.h"
#include "../Models/SampleSpaceModel.h"
#include "StatClass.h"
#include <Qt/qdebug.h>
#include <math.h>


// WARNING LOGO  LOGO MUDAR OS PARAMETROS JA QUE ESTAMOS GUARDANDO A REFERENCIA EM m_rol E m_statClasses
Separatrices::Separatrices(const QList<Number>& rol, const QList< StatClass >& statisticClasses,
			   const uint modalClassIndex, const Number& h,QObject* parent): QObject(parent), m_averageBySum(0) 
  , m_averageByHalfPoint(0)
  , m_mode(0)
  , m_median(0)
  , m_quartil(0)
  , m_decil(0)
  , m_percentil(0)
  , m_variance(0)
  , m_width(&h)
  , m_rol(&rol)
  , m_statClasses(&statisticClasses)
{
  setAverageBySum(rol);
  setAverageByHalfPoint(statisticClasses, rol.size());
  setMedian(statisticClasses,modalClassIndex,rol.size(), h);
  setMode(statisticClasses, modalClassIndex,h);
  setVariance(rol);
  quartil(2);
  decil(2);
  percentis(50);
  
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
    if (q > 4)
    return m_quartil;
  
  Number div = ( (q * m_rol->size()) / 10 );
  int index=0;
  
  // Find the class that contains the element in position (div)
  for(QList<StatClass>::const_iterator it = m_statClasses->constBegin();
    it != m_statClasses->constEnd(); it++){
    qDebug() << div.toString() << ">=" << (*it).absoluteFrequency();
    if ( div >= (*it).absoluteFrequencyAcumulated() ){
      index+=1;
    } else break;
       
  }
   
  if (!index){
     m_quartil = ((div - 0) * (*m_width)) / m_statClasses->at(index).absoluteFrequency();
     m_quartil = m_quartil + m_statClasses->at(index).begin();
  } 
  
  else {
     m_quartil = ((div - m_statClasses->at(index-1).absoluteFrequencyAcumulated()) * (*m_width)) / m_statClasses->at(index).absoluteFrequency();
     m_quartil = m_quartil + m_statClasses->at(index).begin();
  }
  
  qDebug() << "Quartil" << q << m_quartil.toString();
  return m_quartil;
}

Number Separatrices::decil(const int d=2)
{
  if (d > 10)
    return m_decil;
  
  Number div = ( (d * m_rol->size()) / 10 );
  int index=0;
  
  // Find the class that contains the element in position (div)
  for(QList<StatClass>::const_iterator it = m_statClasses->constBegin();
    it != m_statClasses->constEnd(); it++){
    if ( div >= (*it).absoluteFrequencyAcumulated() ){
      index+=1;
    } else break;
       
  }
//   qDebug() << "decil index is: " << index << "div is " << div.toString();
   
  if (!index){
     m_decil = ((div - 0) * (*m_width)) / m_statClasses->at(index).absoluteFrequency();
     m_decil = m_decil + m_statClasses->at(index).begin();
  } 
  
  else {
     m_decil = ((div - m_statClasses->at(index-1).absoluteFrequencyAcumulated()) * (*m_width)) / m_statClasses->at(index).absoluteFrequency();
     m_decil = m_decil + m_statClasses->at(index).begin();
  }
  
  qDebug() << "Decil" << d << m_decil.toString();
  return m_decil;
}

Number Separatrices::percentis(const int p)
{
    if (p > 100)
    return m_percentil;
  
  Number div = ( (p * m_rol->size()) / 100 );
  int index=0;
  
  // Find the class that contains the element in position (div)
  for(QList<StatClass>::const_iterator it = m_statClasses->constBegin();
    it != m_statClasses->constEnd(); it++){
    if ( div >= (*it).absoluteFrequencyAcumulated() ){
      index+=1;
    } else break;
       
  }
   
  if (!index){
     m_percentil = ((div - 0) * (*m_width)) / m_statClasses->at(index).absoluteFrequency();
     m_percentil = m_percentil + m_statClasses->at(index).begin();
  } 
  
  else {
     m_percentil = ((div - m_statClasses->at(index-1).absoluteFrequencyAcumulated()) * (*m_width)) / m_statClasses->at(index).absoluteFrequency();
     m_percentil = m_percentil + m_statClasses->at(index).begin();
  }
  
  qDebug() << "Percentil" << p << m_percentil.toString();
  return m_percentil;

}

Separatrices::~Separatrices()
{
  m_rol = 0;
  m_statClasses = 0;
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
  m_rol = &rol;
  m_statClasses = &statisticClasses;
  quartil(2);
  decil(2);
  percentis(63);
}