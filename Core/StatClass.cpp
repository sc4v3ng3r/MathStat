#include "StatClass.h"

StatClass::StatClass():m_begin(0)
  , m_end(0)
  , m_fa(0)
  , m_faA(0)
  , m_fi(0)
  , m_fiA(0)
  , m_percents(0)
  , m_percentsA(0)
  , m_halfPoint(0)
{}

StatClass::StatClass(const StatClass& object): m_begin(object.begin())
  , m_end(object.end())
  , m_fa(object.absoluteFrequency())
  , m_faA(object.absoluteFrequencyAcumulated())
  , m_fi(object.relativeFrequency())
  , m_fiA(object.relativeFrequencyAcumulated())
  , m_percents(object.percents())
  , m_percentsA(object.percentsAcumulated())
  , m_halfPoint(object.halfPoint())
{}

Number StatClass::begin() const
{ return m_begin; }

Number StatClass::end() const
{ return m_end; }

int StatClass::absoluteFrequency() const
{ return m_fa;}

int StatClass::absoluteFrequencyAcumulated() const
{ return m_faA;}

Number StatClass::relativeFrequency() const
{ return m_fi;}

Number StatClass::relativeFrequencyAcumulated() const
{ return m_fiA;}

Number StatClass::percents() const
{return m_percents;}

Number StatClass::percentsAcumulated() const
{ return m_percentsA;}

Number StatClass::halfPoint() const
{ return m_halfPoint;}

void StatClass::setBegin(const Number& begin)
{ m_begin << begin; return;}

void StatClass::setEnd(const Number& end)
{ m_end << end; return;}

void StatClass::setAbsoluteFrequency(const unsigned int fa)
{ m_fa = fa; return; }

void StatClass::setAbsoluteFrequencyAcumulated(const unsigned int faa)
{ m_faA = faa; return; }

void StatClass::setRelativeFrequency(const Number& fi)
{ m_fi << fi; return; }

void StatClass::setRelativeFrequencyAcumulated(const Number& fia)
{ m_fiA << fia; return; }

void StatClass::setPercents()
{ m_percents << (m_fi*100); return;}

void StatClass::setPercentsAcumulated(const Number& value)
{ m_percentsA << value; return;}

void StatClass::setHalfPoint()
{ m_halfPoint << (m_begin+m_end)/2; return;}

StatClass& StatClass::operator=(const StatClass& data)
{
  this->m_begin << data.begin();
  this->m_end << data.end();
  this->m_fa = data.absoluteFrequency();
  this->m_faA = data.absoluteFrequencyAcumulated();
  this->m_fi << data.relativeFrequency();
  this->m_fiA << data.relativeFrequencyAcumulated();
  this->m_halfPoint << data.halfPoint();
  this->m_percents << data.percents();
  this->m_percentsA << data.percentsAcumulated();
  
  return *this;
}