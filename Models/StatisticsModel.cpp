#include "StatisticsModel.h"

StatisticsModel::StatisticsModel(QObject* parent): QAbstractTableModel(parent)
  , m_columns(2)
  , m_rows(11)
{}

int StatisticsModel::rowCount(const QModelIndex& index) const {return m_rows; }

int StatisticsModel::columnCount(const QModelIndex& index) const { return m_columns; }

QVariant StatisticsModel::data(const QModelIndex& index, int role) const
{
  if (!index.isValid())
    return QVariant();
  
  int row = index.row();
  
  if (row >= m_data.size())
    return QVariant();
  
  int column = index.column();
  
  switch(role){
   case Qt::DisplayRole:
   case Qt::UserRole:
     
     switch(row){
       case 0:
	 switch(column){
	   case 0:
	     return QString("Class Number");
	     break;
	   case 1:
	     return m_data[row].toString();
	     break;
	}
	break;
	
	case 1:
	  switch(column){
	    case 0:
	      return QString("Class Width");
	      break;
	    case 1:
	      return m_data[row].toString();
	      break;   
	  }
	  break;
	  
	case 2:
	  switch(column){
	    case 0:
	      return QString("Amplitude");
	      break;
	    case 1:
	      return m_data[row].toString();
	      break;
	  }
	  break;
	    
	case 3:
	  switch(column){
	    case 0:
	      return QString("Total");
	      break;
	    case 1:
	      return m_data[row].toString();
	      break;
	  }
	  break;
	case 4:
	  switch(column){
	    case 0:
	      return QString("Average by sum");
	      break;
	    case 1:
	      return m_data[row].toString();
	      break;
	  }
	  break;
	  
	case 5:
	  switch(column){
	    case 0:
	      return QString("Average by XiFi");
	      break;
	    case 1:
	      return m_data[row].toString();
	      break;
	  }
	  break;
	      
	case 6:
	  switch(column){
	    case 0:
	      return QString("Mode");
	      break;
	    case 1:
	      return m_data[row].toString();
	      break;
	  }
	  break;
	 
	 case 7:
	   switch(column){
	     case 0:
	       return QString("Median");
	       break;
	     case 1:
	       return m_data[row].toString();
	       break;
	  }
	  break;
	  
	 case 8:
	   switch(column){
	     case 0:
	       return QString("Quartil ");
	       break;
	     case 1:
	       return m_data[row].toString();
	       break;
	  }
	  break;
	  
	case 9:
	  switch(column){
	    case 0:
	      return QString("Decil ");
	      break;
	    case 1:
	      return m_data[row].toString();
	      break;
	  }
	  break;
	
	case 10:
	  switch(column){
	    case 0:
	      return QString("Percentil ");
	      break;
	    case 1:
	      return m_data[row].toString();
	      break;
	  }
	  break;
    }
    default: // Role default
      break;
  }
  
  return QVariant();
}

void StatisticsModel::addData(const QModelIndex& index, const QVariant& data)
{

}

//WARNING change the dataChanged
void StatisticsModel::setData(const QList< Number >& values)
{
  m_data = values;
  emit dataChanged(createIndex(0,0),createIndex(m_rows,m_columns)); // WARNING ONLY TEST
  return;
}

void StatisticsModel::setData(const Number& value)
{
  m_data.append(value);
  // this line below should be change, for improve more peformace
  // test only
  emit dataChanged(createIndex(0,0),createIndex(m_rows,m_columns)); // WARNING ONLY TEST
  return;
}

// WARNING CHANGE THE DATACHANGED
void StatisticsModel::clearModel()
{ 
  m_data.clear();
  emit dataChanged(createIndex(0,0),createIndex(m_rows,m_columns)); // WARNING ONLY TEST
  return;
}

StatisticsModel::~StatisticsModel()
{

}

