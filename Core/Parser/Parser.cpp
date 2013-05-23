#include "Parser.h"
#include <QDebug>

void Parser::interpreter(const QString& data)
{
  m_data = data.split(' ',QString::SkipEmptyParts,Qt::CaseInsensitive);

  Q_FOREACH(const QString& text, m_data){
    qDebug() << text;
  }
}
