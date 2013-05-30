#include "StatClassModel.h"
#include "../Guis/FixDialog.h"
#include <Qt/qdebug.h>
#include <QtGui/qbrush.h>

#define ROWS_DEFAULT 7
#define COLUMNS_DEFAULT 9

StatClassModel::StatClassModel(const QList< StatClass >& data, QObject* parent): QAbstractTableModel(parent)
  , m_data(data)
  , m_columns(COLUMNS_DEFAULT)
  , m_rows(data.size())
  , m_fix(5)
  , m_modalClass(2)
  , m_fixDialog(0)
{}

StatClassModel::StatClassModel(QObject* parent): QAbstractTableModel(parent)
  , m_data(QList<StatClass>())
  , m_columns(COLUMNS_DEFAULT)
  , m_rows(ROWS_DEFAULT)
  , m_fix(2)
  , m_fixDialog(0)
{}

int StatClassModel::rowCount(const QModelIndex& index) const { return m_rows;}

int StatClassModel::columnCount(const QModelIndex& index) const { return m_columns;}

int StatClassModel::fix() const { return m_fix;}

bool StatClassModel::setFix(const int fix)
{ 
  if (fix <= 19){
      m_fix=fix;
      emit dataChanged(createIndex(0,0), createIndex(m_rows,m_columns));
      emit fixChanged(m_fix);
      return true;
  }
  return false;
}

bool StatClassModel::insertRows(int row, int count, const QModelIndex& parent)
{
    beginInsertRows(parent, row, (row+count)-1);
    m_rows+=count;
    endInsertRows();
    return true;
}

bool StatClassModel::removeRows(int row, int count, const QModelIndex& parent)
{
  beginRemoveRows(parent, row, (row+(count-1)));
  m_rows-=count;
  endRemoveRows();
  return true;
}

QVariant StatClassModel::data(const QModelIndex& index, int role) const
{
  if ((!index.isValid()))
    return QVariant();
  
  if (!m_data.size()) // this is a error, m_data never is empty 
    return QVariant();
  
  int row = index.row();
  int column = index.column();
  
  switch(role){
    
    case Qt::UserRole:
    case Qt::DisplayRole: 
      switch(column){
	
	case 0:
	  return QString::number(row+1);
	  break;
	
	case 1: // Bounds X |--- Y
	  return QString("%1 %2 %3").arg(m_data[row].begin().toString(m_fix)).arg("|----")
	  .arg(m_data[row].end().toString(m_fix));
	  break;
	case 2:
	  return QString::number(m_data[row].absoluteFrequency());
	  break;
	
	case 3:
	  return QString::number(m_data[row].absoluteFrequencyAcumulated());
	  break;
	
	case 4:
	  return m_data[row].relativeFrequency().toString(m_fix);
	  break;
	
	case 5:
	  return m_data[row].relativeFrequencyAcumulated().toString(m_fix);
	  break;
	
	case 6:
	  return m_data[row].percents().toString(m_fix);
	  break;
	
	case 7:
	  return m_data[row].percentsAcumulated().toString(m_fix);
	  break;
	
	case 8:
	  return m_data[row].halfPoint().toString(m_fix);
	  break;
      
	default:
	  break;
      }
    
    case Qt::BackgroundRole:
      if (row == m_modalClass){ // when find modal class colour of red
	QBrush background(Qt::red);
	return background;
      } else if (m_data[row].absoluteFrequency() == 0){ // when find a empty class colour of green
	  QBrush background(Qt::green);
	  return background;
      }
      break;
      
    case Qt::WhatsThisRole:
      break;
      
    default:
      break;  
  }
  return QVariant();
}

void StatClassModel::addData(const QList< StatClass >& data)
{
  m_data.clear();
  m_data = data;
  int rows = m_data.size();
  
  if (rows > m_rows){
    insertRows(m_rows, (rows%m_rows), QModelIndex());
    qDebug() << "Adicionado" << rows%m_rows << "linhas";
    
  } else if (rows < m_rows){
    qDebug() << "Removendo" << m_rows-rows << "linhas";
    removeRows((m_rows-rows)+1,(m_rows-rows), QModelIndex());
  }
  
  findModalClass();
  emit dataChanged(createIndex(0,0),createIndex(m_rows-1,m_columns-1));
}

QVariant StatClassModel::headerData(int section, Qt::Orientation orientations, int role) const
{
  if((role != Qt::DisplayRole) || (orientations!= Qt::Horizontal))
    return QVariant();
    
  switch(section){
    case 0:
      return QString("Classes");
      break;
    
    case 1:
      return QString("Bounds");
      break;
    
    case 2:
      return QString("Fi");
      break;
    
    case 3:
      return QString("Fac");
      break;
    
    case 4:
      return QString("fi");
      break;
    
    case 5:
      return QString("fac");
      break;
    
    case 6:
      return QString("%");
      break;
    
    case 7:
      return QString("%ac");
      break;
    
    case 8:
      return QString("Xi");
      break;
    
    default:
      break;
  }
  return QVariant();
}

QList< StatClass >::const_iterator StatClassModel::constBegin() const
{ return m_data.constBegin();}

QList< StatClass >::const_iterator StatClassModel::constEnd() const
{ return m_data.constEnd();}


int StatClassModel::size() const
{ return m_data.size();}

void StatClassModel::findModalClass()
{
  uint index=0;
  
  for(int i=1; i< m_data.size(); i++)
    if (m_data[index].absoluteFrequency() < m_data[i].absoluteFrequency())
      index=i;
    
  m_modalClass = index;
}

QModelIndex StatClassModel::getIndex(const unsigned index) const
{ 
 int row = index/m_columns;
 int column = (index%m_columns);
 
 if (column < 0)
   column^=column;
 
 return createIndex(row, column);
}

const StatClass& StatClassModel::modalClass() const { return m_data[m_modalClass]; }

void StatClassModel::createFixDialog()
{  
  if (!m_fixDialog){
    m_fixDialog = new FixDialog(m_fix,0,0);
    QObject::connect(m_fixDialog,SIGNAL(dataValue(int)),this,SLOT(setFix(int)));
    QObject::connect(m_fixDialog,SIGNAL(accepted()),this,SLOT(destroyFixDialog()));
    QObject::connect(m_fixDialog,SIGNAL(rejected()),this,SLOT(destroyFixDialog()));
    m_fixDialog->exec();
  }
  return;
}

StatClassModel::~StatClassModel()
{
}

void StatClassModel::destroyFixDialog()
{
  delete m_fixDialog;
  m_fixDialog = 0;
}

const QList< StatClass >& StatClassModel::getData() const {return m_data; }

const uint StatClassModel::modalClassPosition() const { return m_modalClass; }

/*
Qt::ItemFlags StatClassModel::flags(const QModelIndex& index) const
{
    return Qt::NoItemFlags;
}
*/