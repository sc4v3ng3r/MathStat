#ifndef PARSER_H
#define PARSER_H

#include <Qt/qobject.h>
#include <Qt/qstringlist.h>

class Parser : public QObject {
  Q_OBJECT
  
private:
  QStringList m_data;
 
public:
 Parser(QObject* parent=0);
 virtual ~Parser();
 void interpreter(QString data);

public Q_SLOTS:

  
};
#endif