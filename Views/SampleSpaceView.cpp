#include "SampleSpaceView.h"
#include <qdebug.h>

SampleSpaceView::SampleSpaceView(SampleSpaceModel &model, QWidget *parent): QTableView(parent)
  , m_delAction("actionDelete",this)
  , m_model(model)
  
{ 
  this->setModel(&m_model);
  m_delAction.setShortcut(Qt::Key_Delete);
  this->addAction(&m_delAction);
  
  for(short i=0; i < m_model.columnCount(); i++)
    this->setColumnWidth(i,60); 

  QObject::connect(&m_delAction,SIGNAL(triggered()),this,SLOT(delData()));
}

void SampleSpaceView::delData()
{
  QList<QModelIndex> indexes = this->selectedIndexes();
  qSort(indexes);
  m_model.delData(indexes);
  indexes.clear();
}

/*
void SampleSpaceView::lockView()
{
  qDebug() << "Selection Mode is actually " << this->selectionMode();
  
  (this->selectionMode() != QAbstractItemView::NoSelection) ? this->setSelectionMode(QAbstractItemView::NoSelection)
  :this->setSelectionMode(QAbstractItemView::ContiguousSelection);
  //this->setSelectionMode(QAbstractItemView::NoSelection);
  //this->selectionChanged();
  
}
*/