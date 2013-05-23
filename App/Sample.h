#ifndef SAMPLE_H
#define SAMPLE_H

#include <Qt/qobject.h>

#include "../Core/CoreData.h"

#include "../Graphics/Histogram.h"
#include "../Models/SampleSpaceModel.h"
#include "../Models/StatClassModel.h"
#include "../Models/StatisticsModel.h"

class Separatrices;

class Sample : public QObject {
  Q_OBJECT

private:
  bool m_state;
  CoreData m_coreData; // change class Number for SampleDescription
  Histogram m_histogram; // maybe this be a pointer
  Separatrices *m_separatrices;
  // graficos
  // separatices
  
  void setState(const bool state);
  QList<StatClass> calcClasses(const int& size);
  void settingStatisticModel();
  
public:
  //WARNING the model's are publics because them are nedeed in class that holds the views...
  SampleSpaceModel m_sampleSpace;
  StatClassModel m_classModel;
  StatisticsModel m_statisticModel;
  
  Sample(QObject* parent=0, const QString &name = QString());
  virtual ~Sample();
  void restoreGraph(const Histogram::GraphicType& type);
  bool state() const;
public Q_SLOTS:
  void calcAll();
  void showHistogram();

private Q_SLOTS:
  void dataChangeHistogram(const Histogram::GraphicType& type);
  
Q_SIGNALS:
  void stateChanged(const bool state);
};
#endif
