#include "SampleSpaceModel.h"
#include "../Core/Number.h"

#include <qdebug.h>
#include <qdir.h>
#include <Qt/qfile.h>
#include <Qt/qdatetime.h>
#include <Qt/qfileinfo.h>
#include <Qt/qfiledialog.h>

SampleSpaceModel::SampleSpaceModel(QObject* parent): QAbstractTableModel(parent)
  , m_rows(7)
  , m_columns(7)
  , m_decimalFrequency(0)
  , m_fix(4)
{
  this->setObjectName("RolView");
  QObject::connect(this,SIGNAL(dataChanged(QModelIndex,QModelIndex)),this,SLOT(decimalParser()));
}

int SampleSpaceModel::size() const { return m_data.size(); }

int SampleSpaceModel::columnCount(const QModelIndex &index) const { return m_columns; }

int SampleSpaceModel::rowCount(const QModelIndex &index) const { return m_rows; } 

unsigned SampleSpaceModel::decimaFrequency() const { return m_decimalFrequency;}

/*
void SampleSpaceModel::addData(QList<float> values)
{/*
  if (!values.isEmpty()) {
    // tell the view that data are comming
    m_valueList.append(values);
    // tell the view that data has been add 
  }
  return;
}*/

bool SampleSpaceModel::isFull() const  // Esse metodo tem que ficar no View
{
  if ((m_columns*m_rows) == m_data.size())
    return true;
  
  return false;
}

void SampleSpaceModel::addData(const QModelIndex& index, const QVariant &value)
{
  
 int position = getItPosition(index);
 
 if (position > m_data.size()){   
   m_data.append(value.toString());  
 } 
 
 else m_data.insert(position, value.toString());

 return;
}

QVariant SampleSpaceModel::data(const QModelIndex& index, int role) const
{
  int position = getItPosition(index);
  
  if ( (!index.isValid() || (position >= m_data.size())) )  
    return QVariant();
  
  switch(role){
    case Qt::UserRole:
    case Qt::DisplayRole:
    case Qt::EditRole:
      return m_data.at(position).toString();
      break;
      
    default:
      break;
  }
  
  return QVariant();
}

bool SampleSpaceModel::setData(const QModelIndex& index, const QVariant& value, int role)
{
  
  if ((!index.isValid()) || (!value.toBool()))
    return false;
  
  int position = getItPosition(index);
  
  switch(role){ 
    
    case Qt::EditRole:
      if (position >= m_data.size()){
	addData(index, value);
	break;
      }
      
      m_data.replace(position,value.toString());
      break;
     
    default:
      return false;
      break;   
  }
 
 if (isFull())
  insertRows(index.row(),1,index);
  
  emit dataChanged(index, index);
 return true;
}

Qt::ItemFlags SampleSpaceModel::flags(const QModelIndex& index) const
{ return Qt::ItemIsEditable|Qt::ItemIsSelectable|Qt::ItemIsEnabled; }

void SampleSpaceModel::setRows(const int rows)
{
  if (rows)
    m_rows = rows;
  return;
}

/*
void SampleSpaceModel::setColumns(int columns)
{
  if (columns)
    m_columns=columns;
}
*/

bool SampleSpaceModel::insertRows(int row, int count, const QModelIndex& index)
{
  beginInsertRows(QModelIndex(),row, (row+count)-1);
  m_rows+=count;
  endInsertRows();
  return true;
}

int SampleSpaceModel::getItPosition(const QModelIndex &index) const
{ return ((index.row()*m_columns)+index.column()); }

/* WARNING if possible improve more peformace in delData function, maybe emit the dataChanged signal only
 * at the index that really were changed
 */

void SampleSpaceModel::delData(const QList<QModelIndex>& indexes)
{
  QList<QModelIndex> indexes2 = indexes;
  unsigned position;  
  
  while(indexes2.size()){
      QModelIndex index = indexes2.takeLast();
      
      if (index.data().isNull())
	continue;
      
      position = getItPosition(index);
      if (position < m_data.size())
	m_data.removeAt(position);
  }
  
  emit dataChanged(createIndex(0,0),getIndex(m_data.size()-1)/*indexes.last()*/);
  return;
}

QModelIndex SampleSpaceModel::getIndex(const unsigned index) const
{ 
 int row = index/m_columns; //
 int column = (index%m_columns);
 
 if (column < 0)
   column^=column;
 
 return createIndex(row, column);
}

void SampleSpaceModel::sort()
{ 
  qSort(m_data);
  return;
}

void SampleSpaceModel::decimalParser()
{
  unsigned *decimal = new unsigned[17]();
  unsigned decimalHome=0;
  
  for(QList<Number>::iterator it = m_data.begin();
      it!= m_data.end();
      it++){
    decimal[(*it).decimalFrequency()]++;
  }
  
  m_decimalFrequency = decimal[0];
   for(int j = 1; j < 17; j++){
     if (m_decimalFrequency < decimal[j]){
       m_decimalFrequency = decimal[j];
       decimalHome = j;
     }
   } // if decimals is equals, stay the first selected
    
  m_decimalFrequency = decimalHome;  
  
  qDebug() << "Decimal Frequency" << m_decimalFrequency;
  delete decimal;
  return;
}
bool SampleSpaceModel::saveData(QFile& file)
{
 QFileInfo info(file);
 QDir dir; 
 
 if (!info.exists())
    dir.mkpath(info.path());
  
 file.open(QIODevice::WriteOnly|QIODevice::Truncate);
 QDataStream out(&file);
 
 for(int i=0; i < m_data.size(); i++)
  out << m_data.at(i).toDouble();
 
 file.close();
 qDebug() << "File Saved";
 return true;
}

// TEST FUNCTION
bool SampleSpaceModel::save()
{
  
 QFile file(QFileDialog::getSaveFileName(0, tr("Save File"), QDir::homePath()));
 //qDebug() << "
 return saveData(file);
 
}

// TEST FUNCTION
void SampleSpaceModel::loadData()
{

 QFile file(QString(QFileDialog::getOpenFileName()));
 
 if (!file.open(QIODevice::ReadOnly)){ 
    qDebug() << "" << file.error();
    return;
 } 
 
 long lenght = file.size()/(sizeof(double));
 
 QDataStream in(&file);
 m_data.clear();
 
 for(int i=0; i < lenght; i++){
  double data;
  in >> data;
  m_data.append(Number(data)); 
 }
 
 int size = m_data.size();
 
 if (size > (m_rows*m_columns)){
  int product = size / m_columns;
  int rest = size % m_columns;
  rest+=product;
  insertRows(m_rows,rest-m_rows,QModelIndex());
 }
 
 emit dataChanged(createIndex(0,0), getIndex(size-1));
 file.close();
 qDebug() << "File Readed";
}

void SampleSpaceModel::AutoSort(bool answer)
{
  answer ? QObject::connect(this,SIGNAL(dataChanged(QModelIndex,QModelIndex)),this,SLOT(sort())) :
  QObject::disconnect(this,SIGNAL(dataChanged(QModelIndex,QModelIndex)),this,SLOT(sort()));
  return;
}

QList< Number >::const_iterator SampleSpaceModel::constDataBegin() const { return m_data.constBegin(); }

QList< Number >::const_iterator SampleSpaceModel::constDataEnd() const { return m_data.constEnd(); }

const Number& SampleSpaceModel::first() const { m_data.first();}

const Number& SampleSpaceModel::last() const { m_data.at(m_data.size()-1); }

const QList< Number >& SampleSpaceModel::getData() const { return m_data;}
