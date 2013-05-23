#ifndef PARSER_GUI_H
#define PARSER_GUI_H

#include <QtGui/QWidget>
#include "../Core/Parser/Parser.h"

class QLineEdit;
class QPushButton;
class QRegExp;
class QHBoxLayout;
class Number;

class ParserGui : public QWidget {
  Q_OBJECT
  
private:
  QLineEdit* m_dataInput;
  QPushButton* m_apply;
  QHBoxLayout* m_hLayout;
  Parser m_parser;
  
public:
  ParserGui(QWidget* parent = 0);
  virtual ~ParserGui();
  QRegExp* m_regularExpression;

private slots:
  void parsing();
  
Q_SIGNALS:
  void dataInterpreted(QList<Number>& numbers);
  
};
#endif