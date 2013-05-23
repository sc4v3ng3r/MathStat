#include "Number.h"

#include <qstringlist.h>
#include <qdebug.h>

Number::Number() {}

Number::Number(const double number):
 m_integerPart(QString::number(number,'g',MAX_PRECISION))
{
  if (m_integerPart.split('.').size() > 1){
    m_decimalPart = m_integerPart.split('.').at(1);
    m_integerPart = m_integerPart.split('.').at(0);
  } 
  else m_integerPart = m_integerPart.split('.').at(0);
}

Number::Number(const QString& number): 
  m_integerPart(number.split('.').at(0))
{
  if (number.split('.').size() == 2)
    m_decimalPart = number.split('.').at(1);
}

Number::Number(const Number& number):
  m_integerPart(number.m_integerPart)
  , m_decimalPart(number.m_decimalPart)
{
}

Number::~Number(){}

bool Number::isDecimal() const
{
  if (m_decimalPart.size())
    return true;
  
  return false;
}

double Number::toDouble() const
{
  if (m_decimalPart.size()){
    return QString("%1.%2").arg(m_integerPart).arg(m_decimalPart).toDouble();
  } else return QString("%1.%2").arg(m_integerPart).arg("0").toDouble(); 
}

double Number::toDouble(const short int fix) const 
{
  if (m_decimalPart.size()){
    return aprox(fix).toDouble();
  } else return QString("%1.%2").arg(m_integerPart).arg("0").toDouble();
}

short int Number::decimalFrequency() const
{
  short size = m_decimalPart.size();
  if (size)
    return size;
  
  else return 0;
}

float Number::toFloat() const 
{
  if (m_decimalPart.size())
    return QString("%1.%2").arg(m_integerPart).arg(m_decimalPart).toFloat();
  else
    return m_integerPart.toFloat();
}

float Number::toFloat(const short int fix) const
{ 
  if (m_decimalPart.size()){
    return aprox(fix).toFloat();
  } else return QString("%1.%2").arg(m_integerPart).arg("0").toFloat();
}

QString Number::toString() const { 
  if (m_decimalPart.size())
    return QString("%1.%2").arg(m_integerPart).arg(m_decimalPart); 

  else return m_integerPart;
}

QString Number::toString(const short int fix) const { return aprox(fix).toString(); }

double Number::decimalPart() const
{
  if (m_decimalPart.size())
    return m_decimalPart.toDouble();
  return 0;
}

double Number::decimalPart(const short fix) const {
  
  if (m_decimalPart.size()){
   return this->aprox(fix).m_decimalPart.toDouble();
  }  
  return 0;
}
QString Number::decimalPartToString() const
{
  if (m_decimalPart.size()){
    return m_decimalPart;
  } else return QString();
}

int Number::integerPart() const { return m_integerPart.toInt(); }

QString Number::integerPartToString() const { return m_integerPart; }

void Number::setNumber(const double number)
{ 
  m_integerPart = QString::number(number);
  
  if (m_integerPart.split('.').size() > 1){
    m_decimalPart = m_integerPart.split('.').at(1);
    m_integerPart = m_integerPart.split('.').at(0);
  }
}

void Number::setNumber(const Number& number)
{
  this->m_integerPart = number.m_integerPart;
  this->m_decimalPart = number.m_decimalPart;
}

Number& Number::operator<<(const double number) { this->setNumber(number); return *this; }
/*
Number Number::newAprox(const short int fix) const
{
  Number newNumber;
  
  if (!m_decimalPart)
    return *this;
  
  // verificar as condicoes de fix!
  newNumber.m_decimalPart = this->m_decimalPart;
  newNumber.m_integerPart = this->m_integerPart;
}*/

// WARNING IMPROVE MORE PEFORMACE !!! only experimental but it's work
Number Number::aprox(const short int fix) const
{
 // dot position is m_intergerPart.size()+1;
 QString tmp;
 int i,d;

 if (!m_decimalPart.size())// if number is not decimal, return it
   return this->m_integerPart;
 
 if ((fix) >= m_decimalPart.size())
   return *this;
 
 if (!fix){
   int x;
//    qDebug() << "Fix 0 number is" << "Number is" << this->toString();
   if (this->m_decimalPart[fix].digitValue() >= 5){
//      qDebug() << "Vai aproximar ";
     x = this->m_integerPart.toInt() +1;
   }
   else { x = this->m_integerPart.toInt(); /*qDebug() << "Nao aproxima!";*/}
   
   Number n(x);
   return n;
 }
 
 tmp.clear(); // remover jaja!
 tmp = this->m_decimalPart.left(fix+2);
 
 if ( (tmp.size() == tmp.count('0')) || (this->m_decimalPart.left(fix).size() == this->m_decimalPart.left(fix).count('0')) )
    return this->m_integerPart;
   
 tmp.clear();
 tmp = this->m_integerPart;
 tmp.append(m_decimalPart.left(fix+1)); // return 123
 
 if (tmp.at(tmp.size()-1).digitValue() >=5){
//    qDebug() << "Vai ser aproximado";
   tmp.remove(tmp.size()-1,1);
   
   if (tmp.at(tmp.size()-1).digitValue() == 9){
     for(i=tmp.size()-1; i>=0; i--){
      if (tmp.at(i).digitValue() == 9)
       tmp.replace(i,1,QChar('0'));
      else break;
     } 
     if (i < 0){
	tmp.prepend(QChar('1'));
	tmp.insert(this->m_integerPart.size()+1,QChar('.'));
      } 
      else {
	d = tmp.at(i).digitValue(); d+=1;
	tmp.replace(i,1,QString::number(d));
	tmp.insert(this->m_integerPart.size(),QChar('.'));
      }
   } 
  else {
    d = tmp.at(tmp.size()-1).digitValue();
    d+=1;
    tmp.replace(tmp.size()-1,1,QString::number(d));
    tmp.insert(this->m_integerPart.size(),QChar('.'));
  }
 }
 else { // tratar somente quando nao precisa
    tmp.remove(tmp.size()-1,1);
    tmp.insert(this->m_integerPart.size(),QChar('.'));
 } 
 Number x(tmp);
 return x;
  
 /* OLD ALGORITHM don't handle for numbers type 99.999, need define QString aprox;
 if ((aprox.at(aprox.size()-1).digitValue()) >= 5){ // verify if last digit is greater or equals that 5, if yes...
   QChar d = aprox.at(aprox.size()-2); //
   d = QString::number((d.digitValue()+1)).at(0); // when is 9, trate 
   aprox.replace(aprox.size()-2,1,d);  
  }
  
  aprox.remove(aprox.size()-1,1);
  tmp.append(aprox);
 */ 
  //return aprox;
}

