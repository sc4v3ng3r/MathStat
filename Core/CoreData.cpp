#include "CoreData.h"
#include <cmath>
#include <Qt/qdebug.h>
#include <cstdlib>

// mecher nessa classe e seus calculos, 
CoreData::CoreData(QObject *parent): QObject(parent)
  ,m_amplitude(0)
  ,m_classesNumber(0)
  ,m_width(0)
{}

CoreData::CoreData(const double first, const double last, const int size, QObject* parent): QObject(parent)
  , m_amplitude((last-first))
{
  calcAmplitude(first,last);
  calcClassesNumber(size);
  calcWidth(size);
  return;
}

void CoreData::calcAmplitude(const double first, const double last)
{
  m_amplitude << (last-first);
  return;
}

void CoreData::calcClassesNumber(const unsigned n)
{
  qDebug()<< "calculating class number" << (1+3.3*(log10(n)));
  m_classesNumber = (1+3.32*(log10(n)));
  m_classesNumber+=1;
  return;
}

void CoreData::calcWidth(const unsigned& n)
{ 
  m_width << ((m_amplitude.toDouble()) / (1+3.32*(log10(n))));
  return;
}
// this must to be slot
void CoreData::setWidth(const double width)
{ 
  if((width) && (width > 0)){
    m_width << width;
  }
  return;
}

Number CoreData::amplitude() const { return m_amplitude; }

unsigned int CoreData::classesNumber() const { return m_classesNumber; }

Number CoreData::width() const { return m_width; }

void CoreData::recalcAll(const double first, const double last, const int size)
{  
  calcAmplitude(first, last);
  calcClassesNumber(size);
  calcWidth(size);
  return;
}

// WARNING TEMPORARY METHOD
void CoreData::debug() const { qDebug() << "DATA" << m_amplitude.toString() << m_classesNumber << m_width.toString(); }

// WARNING APROXIMAR PARA UM VALOR DIVISIVEL POR 2 DE ACORDO COM A FREQUENCIA DECIMAL!

void CoreData::aproxWidth(unsigned int decimalFrequency)
{
/*  
  switch(decimalFrequency){
    case 0:
     Number newWidth(m_width.toString(0)); // WARNING temporary!
      break;
      
    default:
      Number newWidth(m_width.toString(decimalFrequency));
      //qDebug() << "Fazer tratamento, talvez seta parte inteira e parte decimal aproximada ^^";
      break;
  }*/
  
  qDebug() << "Width Aprox " << m_width.aprox(decimalFrequency).toString();
  Number newWidth(m_width.aprox(decimalFrequency));
  m_width = newWidth;
  qDebug() << "Width em uso" << m_width.toString();
}