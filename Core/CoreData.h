#ifndef COREDATA_H
#define COREDATA_H
#include "Number.h"
#include <Qt/qobject.h>

class CoreData : public QObject { // mudar para SampleDescription

  Q_OBJECT
private:
  Number m_amplitude;
  unsigned m_classesNumber;
  Number m_width;

public:
  CoreData(QObject *parent=0);
  CoreData(const double first, const double last, const int size, QObject* parent=0);
  virtual ~CoreData(){};
  void calcAmplitude(const double first, const double last);
  void calcClassesNumber(const unsigned n);
  void calcWidth(const unsigned& n);
  void recalcAll(const double first, const double last, const int size);
  void setWidth(const double width);
  Number amplitude() const;
  Number width() const;
  unsigned classesNumber() const;
  void aproxWidth(unsigned decimalFrequency);
  
private:
  void redefineWidth();
  
public Q_SLOTS:
  void debug()const;
};
#endif