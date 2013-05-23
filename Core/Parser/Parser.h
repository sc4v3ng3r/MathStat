#ifndef PARSER_H
#define PARSER_H

#include <QObject>
#include <QStringList>

class Parser : public QObject {
  Q_OBJECT

private:
  QStringList m_data;

public:
 void interpreter(const QString& data);

};
#endif