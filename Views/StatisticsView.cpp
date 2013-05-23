#include "StatisticsView.h"
#include "../Models/StatisticsModel.h"

StatisticsView::StatisticsView(StatisticsModel& model, QWidget* parent): QTableView(parent)
  , m_model(model)
{
  this->setModel(&m_model);
}

StatisticsView::~StatisticsView()
{

}
