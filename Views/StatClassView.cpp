#include "StatClassView.h"
#include "../Models/StatClassModel.h"

StatClassView::StatClassView(StatClassModel& model, QWidget* parent): QTableView(parent)
  , m_model(model)
{
    this->setModel(&m_model);
}
