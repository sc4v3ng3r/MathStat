#ifndef SAMPLESPACEMODEL_H
#define SAMPLESPACEMODEL_H

#include "../Core/Number.h"
#include <QtCore/QAbstractTableModel>
#include <QString>
class QFile;
//class QUrl;
class SampleSpaceModel : public QAbstractTableModel {
  Q_OBJECT
  
public:
  
  SampleSpaceModel(QObject *parent = 0);
  virtual ~SampleSpaceModel(){}
  //virtual void addData(QList<Number> values); // for the lineEdit input
  virtual void addData(const QModelIndex& index = QModelIndex(), const QVariant& value = QVariant());
  virtual QVariant data(const QModelIndex& index = QModelIndex(), int role = Qt::DisplayRole) const;
  virtual int rowCount(const QModelIndex& index = QModelIndex()) const;
  virtual int columnCount(const QModelIndex& index = QModelIndex()) const;
  virtual bool setData(const QModelIndex& index = QModelIndex(), const QVariant &value = QVariant(), int role = Qt::EditRole);
  int size() const;
  
  unsigned decimaFrequency() const; // WARNING put a better peformace is a good idea
  
  Qt::ItemFlags flags(const QModelIndex& index = QModelIndex()) const;
  void setRows(const int rows);
  bool isFull() const;
  // void setColumns(int columns);
  void delData(const QList<QModelIndex> &indexes = QList<QModelIndex>());
  QModelIndex getIndex(const unsigned index) const; // WARNING REPAIR THIS
  QList< Number >::const_iterator constDataBegin()const;
  QList< Number >::const_iterator constDataEnd()const;
  const Number& first() const; //talvez nao necessario
  const Number& last() const; // talvez nao necessario
  const QList< Number >& getData() const;

private:

  QList< Number > m_data;
  int m_rows;
  int m_columns;
  unsigned m_decimalFrequency;
  unsigned m_fix;
  
  int getItPosition(const QModelIndex &index = QModelIndex()) const;
  bool insertRows(int row, int count = 1, const QModelIndex& index = QModelIndex());
  bool saveData(QFile &url);

public Q_SLOTS:
  void decimalParser();
  void AutoSort(bool answer); // turn on or turn off the auto-Sort 
  void loadData(); // TEST FUNCTION
  bool save(); // TEST FUNCTION
  void sort();
};
#endif
