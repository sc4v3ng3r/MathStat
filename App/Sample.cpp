#include "Sample.h"
#include "../Core/StatClass.h"
#include "../Core/Separatrices.h"

#include <Qt/qdebug.h>
#include <cstdlib>
#include <qwt/qwt_series_data.h>

Sample::Sample(QObject* parent, const QString& name): QObject(parent)
  , m_coreData(this)
  , m_sampleSpace(this)
  , m_classModel(this)
  , m_state(false)
  , m_separatrices(0)
{
  this->setObjectName(name);
  QObject::connect(&m_histogram,SIGNAL(stateChanged(Histogram::GraphicType)),
		   SLOT(dataChangeHistogram(Histogram::GraphicType)));
}

void Sample::showHistogram()
{
  m_histogram.show();
  m_histogram.replot();
}

void Sample::setState(const bool state) 
{ m_state = state; emit stateChanged(m_state); return; }

bool Sample::state() const
{ return m_state; }

void Sample::calcAll()
{
 qDebug() << "called calcAll";
 int size = m_sampleSpace.size();
 
 if (!size)
   setState(false);
 
 else {
 // qDebug() << "ROL SIZE" << size << "Decimal Frequency" << m_sampleSpace.decimaFrequency();
  m_coreData.recalcAll((*m_sampleSpace.constDataBegin()).toDouble(),m_sampleSpace.last().toDouble() ,size);
  m_coreData.aproxWidth(m_sampleSpace.decimaFrequency());
  
 /* qDebug() << "Amplitude" << m_coreData.amplitude().toString() << "Classes" << m_coreData.classesNumber() 
  << "Width" << m_coreData.width().toString(); 
  */
  calcClasses(size); // this method calculates all statistic classes and your's proprietes and places in classModel
  dataChangeHistogram(m_histogram.state());
  setState(true);
 }
 m_statisticModel.clearModel();
 settingStatisticModel();
 return;
}

QList<StatClass> Sample::calcClasses(const int& size)
{
  int frequency, i; // hold the absolute frequency of each class
  StatClass data;
  QList<StatClass> allClasses; // 
  
  const QList<Number>& sampleSpace = m_sampleSpace.getData();
  i = frequency = 0;
  
  data.setBegin(sampleSpace[0]);
  
  while(i < sampleSpace.size()){  
    data.setEnd(data.begin() + m_coreData.width());
    
    while( (i < sampleSpace.size()) && (sampleSpace[i] < data.end()) ){
      frequency+=1;
      i++;
    }
    
    data.setAbsoluteFrequency(frequency);
    data.setRelativeFrequency(static_cast<double>(frequency) / static_cast<double>(sampleSpace.size()));
    data.setPercents();
    data.setHalfPoint();
    
    qDebug() << data.begin().toString() << data.end().toString() << data.absoluteFrequency();
    allClasses+=data;
    
    frequency^=frequency;
    data.setBegin(data.end());
  }
  
 //exeption for first class, because FaA, Fia and porcents acumulated they are the equals of Fa, Fi and percents
 allClasses[0].setAbsoluteFrequencyAcumulated(allClasses[0].absoluteFrequency());
 allClasses[0].setRelativeFrequencyAcumulated(allClasses[0].relativeFrequency());
 allClasses[0].setPercentsAcumulated(allClasses[0].percents());
 
 for(i=1; i < allClasses.size(); i++){
  allClasses[i].setAbsoluteFrequencyAcumulated(allClasses[i].absoluteFrequency()+allClasses[i-1].absoluteFrequencyAcumulated());
  allClasses[i].setRelativeFrequencyAcumulated(allClasses[i].relativeFrequency()+allClasses[i-1].relativeFrequencyAcumulated());
  allClasses[i].setPercentsAcumulated(allClasses[i].percents()+allClasses[i-1].percentsAcumulated());
 }
 
 m_classModel.addData(allClasses);
 
 //Only Debug
 for(i=0; i < allClasses.size(); i++){
   qDebug() << "class" << i+1 << allClasses[i].begin().toString() << "|--" << allClasses[i].end().toString()
   << allClasses[i].absoluteFrequency() << allClasses[i].absoluteFrequencyAcumulated() << allClasses[i].relativeFrequency().toString()
   << allClasses[i].relativeFrequencyAcumulated().toString() << allClasses[i].percents().toString() << allClasses[i].percentsAcumulated().toString()
   << allClasses[i].halfPoint().toString() << "\n";
  }
 
 
  if (!m_separatrices)
    m_separatrices = new Separatrices(m_sampleSpace.getData(), allClasses, m_classModel.modalClassPosition(),
				      m_coreData.width(),this);
 else m_separatrices->redefine(m_sampleSpace.getData(), allClasses, 
   m_classModel.modalClassPosition(), m_coreData.width());
 
 qDebug() << "average By Sum is " << m_separatrices->averageBySum().toString();
 qDebug() << "average By HalfPoint is " << m_separatrices->averageByHalfPoint().toString();
 qDebug() << "Median is " << m_separatrices->median().toString();
 qDebug() << "Mode is " << m_separatrices->mode().toString();
 return allClasses;
}

void Sample::restoreGraph(const Histogram::GraphicType& type)
{
  if (!m_classModel.size())
    return;
  
  m_histogram.setState(type);
  return;
}

void Sample::dataChangeHistogram(const Histogram::GraphicType& type)
{
  QVector<QwtIntervalSample> histogramSamples;
  QList<StatClass>::const_iterator it = m_classModel.constBegin();
  
  switch(type){
    case Histogram::Absolute:
      while(it != m_classModel.constEnd()){
	histogramSamples.append(QwtIntervalSample((*it).absoluteFrequency(),(*it).begin().toDouble(m_classModel.fix()),
						  (*it).end().toDouble(m_classModel.fix())));
	it++;
      }
      m_histogram.setAxisTitle(QwtPlot::yLeft,"Absolute frequency");
      break;
    
    case Histogram::Relative:
      while(it!= m_classModel.constEnd()){
	histogramSamples.append(QwtIntervalSample((*it).relativeFrequency().toDouble(m_classModel.fix()),
				(*it).begin().toDouble(m_classModel.fix()),(*it).end().toDouble(m_classModel.fix())));
	it++;
      }
      m_histogram.setAxisTitle(QwtPlot::yLeft,"Relative frequency");
      break;
    
    case Histogram::Percents:
      while(it !=m_classModel.constEnd()){
	histogramSamples.append(QwtIntervalSample((*it).percents().toDouble(m_classModel.fix()),
				(*it).begin().toDouble(m_classModel.fix()), (*it).end().toDouble(m_classModel.fix())));
	it++;
      }
      m_histogram.setAxisTitle(QwtPlot::yLeft,"Percents %");
      break;
    
    default:
      return;
      break;
  }
  m_histogram.setNewSamples(histogramSamples);
  m_histogram.replot();
  return;
}

Sample::~Sample()
{
  delete m_separatrices;
  m_separatrices = 0;
}

void Sample::settingStatisticModel()
{
  m_statisticModel.setData(m_coreData.classesNumber());
  m_statisticModel.setData(m_coreData.width());
  m_statisticModel.setData(m_coreData.amplitude());
  m_statisticModel.setData(m_sampleSpace.size());
  m_statisticModel.setData(m_separatrices->averageBySum());
  m_statisticModel.setData(m_separatrices->averageByHalfPoint());
  m_statisticModel.setData(m_separatrices->mode());
  m_statisticModel.setData(m_separatrices->median());
  //m_statisticModel.setData();

  return;
}

