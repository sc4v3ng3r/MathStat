#ifndef NUMBER_H
#define NUMBER_H

#include <iostream>
#include <Qt/qstring.h>
#include <Qt/qdatastream.h>

#define MAX_DECIMAL_PRECISION 20
#define MAX_PRECISION 20  // WARNING find and put the max precision of double float point

class Number {
  
public:
  Number(const double number);
  Number(const QString& number);
  Number();
  Number(const Number& number);
  
  virtual ~Number();
  
  bool isDecimal() const;
  
  float toFloat() const;
  float toFloat(const short fix) const;
  double toDouble() const;
  double toDouble(const short fix) const;
  QString toString() const;
  QString toString(const short fix) const;
  
  double decimalPart() const;
  double decimalPart(const short fix) const;
  QString decimalPartToString() const;
  
  int integerPart() const;
  QString integerPartToString() const;
  
  short decimalFrequency() const;
  
  void setNumber(const double number);
  void setNumber(const Number& number);
  
  Number aprox(const short fix) const; // WARNING maybe this method has to be private
  
  Number& operator<<(const double number);// { this->setNumber(number); return *this; }
  inline Number& operator<<(const Number& number) { this->setNumber(number); return *this; }
  
  inline Number& operator=(const Number& number)
  { 
    this->m_integerPart.clear();
    this->m_decimalPart.clear();
    this->m_integerPart = number.m_integerPart;
    this->m_decimalPart = number.m_decimalPart;
    return *this;
  }
  
  inline bool operator<(const Number& number) const { return (this->toDouble() < number.toDouble()); }
  inline bool operator>(const Number& number) const { return !operator<(number); }
  
  inline Number operator+(const Number& rhs) const { return Number( ( (this->toDouble() ) + (rhs.toDouble()) ) ); }
  inline Number operator+(const double number) const {return Number( ( (this->toDouble()) + (number) ) ); }
  
  inline Number operator-(const Number& rhs) const { return Number( ( (this->toDouble() ) - (rhs.toDouble()) ) ); }
  inline Number operator-(const double number) const {return Number( ( (this->toDouble()) - (number) ) ) ;}
  
  inline Number operator*(const Number& rhs) const { return Number( ( (this->toDouble() ) * (rhs.toDouble()) ) ); }
  inline Number operator*(const double number) const { return Number(this->toDouble() *(number)); }
  
  inline Number operator/(const Number& rhs) const { return Number( (this->toDouble()) / (rhs.toDouble())); }
  inline Number operator/(const double number) const { return Number( (this->toDouble()) / (number)); }
  
  inline bool operator==(const Number& rhs) const { return (this->toDouble() == rhs.toDouble()) ? true : false; }
  inline bool operator!=(const Number& rhs) const { return !operator==(rhs); }

private:
  QString m_decimalPart;
  QString m_integerPart;
  
//   Number newAprox(const short fix) const;
};
#endif