#ifndef STATCLASSMODEL_H
#define STATCLASSMODEL_H
#include <QtCore/QAbstractTableModel>
#include "../Core/StatClass.h"

class FixDialog;

class StatClassModel : public QAbstractTableModel{
  Q_OBJECT

private:
  QList<StatClass> m_data;
  int m_rows;
  int m_columns;
  int m_fix;
  uint m_modalClass; // position of modalClass
  FixDialog* m_fixDialog;
  
public:
  StatClassModel(const QList<StatClass>& data=QList<StatClass>(), QObject* parent=0);
  StatClassModel(QObject* parent=0);
  virtual ~StatClassModel();
  const StatClass& modalClass() const;
  const uint modalClassPosition() const;
  
  virtual int rowCount(const QModelIndex& index=QModelIndex()) const;
  virtual int columnCount(const QModelIndex& index=QModelIndex()) const;
  virtual QVariant data(const QModelIndex& index=QModelIndex(), int role=Qt::DisplayRole) const;
  virtual bool insertRows(int row, int count=1, const QModelIndex& parent=QModelIndex());
  virtual bool removeRows(int row, int count=1, const QModelIndex& parent=QModelIndex());
  QVariant headerData(int section, Qt::Orientation orientations, int role = Qt::DisplayRole)const;
 
  void addData(const QList<StatClass>& data=QList<StatClass>());
  int fix()const;
  int size()const;
  
  const QList<StatClass>& getData() const;
  QList<StatClass>::const_iterator constBegin() const;
  QList<StatClass>::const_iterator constEnd() const;  
  // Qt::ItemFlags flags(const QModelIndex& index=QModelIndex())const;
  
public Q_SLOTS:
  bool setFix(const int fix);
  void createFixDialog();

private Q_SLOTS:
  void destroyFixDialog();
  
private:
   void findModalClass();
    QModelIndex getIndex(const unsigned index) const;
    
Q_SIGNALS:
  void fixChanged(const short fix);
  
};
#endif