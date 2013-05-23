#include "ParserGui.h"
#include "../Core/Number.h"

#include <QtGui/qlineedit.h>
#include <QtGui/qpushbutton.h>
#include <QtGui/qstyle.h>
#include <QtGui/QHBoxLayout>
#include <QRegExpValidator>
#include <Qt/qdebug.h>

ParserGui::ParserGui(QWidget* parent) : QWidget(parent)
  , m_hLayout(new QHBoxLayout(this))
  , m_dataInput(new QLineEdit(this))
  , m_apply(new QPushButton(style()->standardIcon(QStyle::SP_DialogApplyButton),"Apply",this))
  , m_regularExpression(new QRegExp("[.;0-9 ]{1,255}") )
{
  m_dataInput->setFixedSize(100,25);
  
  m_dataInput->setMaxLength(400);
  m_dataInput->setValidator(new QRegExpValidator(*m_regularExpression,this));
  
  QObject::connect(m_apply, SIGNAL(clicked(bool)),SLOT(parsing()));
  
  m_hLayout->addWidget(m_dataInput,0,Qt::AlignLeft);
  m_hLayout->addWidget(m_apply,1,Qt::AlignLeft);
}

void ParserGui::parsing()
{
  QString data = m_dataInput->displayText();
  
  if (data.isEmpty())
    return;
  
  qDebug() << "text: " << data; 
  m_dataInput->clear();
  m_parser.interpreter(data);
//   emit dataInterpreted();
}

ParserGui::~ParserGui()
{
  delete m_dataInput;
  delete m_apply;
  delete m_regularExpression;
  delete m_hLayout;
}
