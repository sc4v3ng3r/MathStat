#ifndef STATISTICS_VIEW_H
#define STATISTICS_VIEW_H

#include <QtGui/qtableview.h>

class StatisticsModel;

class StatisticsView : public QTableView {
  Q_OBJECT
  
private:
  StatisticsModel& m_model;
  
public:
  
  StatisticsView(StatisticsModel& model, QWidget* parent=0);
  virtual ~StatisticsView();
}; 
#endif