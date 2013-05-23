#include "Parser.h"
#include <Qt/qdebug.h>

Parser::Parser(QObject* parent): QObject(parent)
{
  
}

void Parser::interpreter(QString data)
{
  m_data = data.split(' ',QString::SkipEmptyParts,Qt::CaseInsensitive);
  
  Q_FOREACH(QString text, m_data){
    qDebug() << text;
  }
}

Parser::~Parser()
{

}
