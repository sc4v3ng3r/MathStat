#ifndef STATCLASS_H
#define STATCLASS_H

#include "Number.h"

class StatClass{
  
private:
  Number m_begin, m_end;
  int m_fa, m_faA;
  Number m_fi, m_fiA;
  Number m_percents, m_percentsA;
  Number m_halfPoint;
  
public:
  StatClass();
  StatClass(const StatClass& object);
  virtual ~StatClass(){};
  
  void setBegin(const Number& begin);
  void setEnd(const Number& end);
  void setAbsoluteFrequency(const unsigned fa);
  void setAbsoluteFrequencyAcumulated(const unsigned faa);
  void setRelativeFrequency(const Number& fi);
  void setRelativeFrequencyAcumulated(const Number& fia);
  void setPercents();
  void setPercentsAcumulated(const Number& value);
  void setHalfPoint();
  
  Number begin() const;
  Number end() const;
  int absoluteFrequency() const;
  int absoluteFrequencyAcumulated() const;
  Number relativeFrequency() const;
  Number relativeFrequencyAcumulated() const;
  Number percents() const;
  Number percentsAcumulated() const;
  Number halfPoint() const;

  StatClass& operator=(const StatClass& data);
  
};
#endif