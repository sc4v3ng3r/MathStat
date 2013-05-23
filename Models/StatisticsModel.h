#ifndef STATISTICS_MODEL_H
#define STATISTICS_MODEL_H

#include <QtCore/QAbstractTableModel>
#include "../Core/Number.h"

class StatisticsModel : public QAbstractTableModel {
  
private:
  Q_OBJECT
  QList<Number> m_data;
  int m_rows;
  int m_columns;
  
public:
  StatisticsModel(QObject* parent=0);
  virtual ~StatisticsModel();
  
  virtual int rowCount(const QModelIndex& index = QModelIndex()) const;
  virtual int columnCount(const QModelIndex& index = QModelIndex()) const;
  virtual QVariant data(const QModelIndex& index= QModelIndex(), int role = Qt::DisplayRole) const;
  virtual void addData(const QModelIndex& index=QModelIndex(), const QVariant& data = QVariant());
  void setData(const QList<Number>& values);
  void setData(const Number& value);
  void clearModel();
  
};

#endif