#ifndef STATCLASSVIEW_H
#define STATCLASSVIEW_H

#include <QtGui/QTableView>

class StatClassModel;

class StatClassView : public QTableView{
  Q_OBJECT

public:

  StatClassView(StatClassModel& model, QWidget* parent=0);

private:
  StatClassModel& m_model;
};
#endif