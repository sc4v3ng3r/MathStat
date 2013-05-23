#ifndef SAMPLESPACEVIEW_H
#define SAMPLESPACEVIEW_H

#include "../Models/SampleSpaceModel.h"
#include <QtGui/QTableView>
#include <Qt/qaction.h>

class SampleSpaceView : public QTableView {
  Q_OBJECT
  
public:
  
  SampleSpaceView(SampleSpaceModel &model, QWidget *parent=0 );
  
private:
  QAction m_delAction;
  SampleSpaceModel &m_model;
  
  
public Q_SLOTS:
  void delData();  
};

#endif