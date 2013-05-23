#include "FixDialog.h"
#include <qdebug.h>
#include <QSpinBox>
#include <qpushbutton.h>
#include <qstyle.h>
#include <QHBoxLayout>
#include <QVBoxLayout>

FixDialog::FixDialog(const short &fix, QWidget* parent, Qt::WindowFlags f): QDialog(parent,f)
  , m_hLayout(new QHBoxLayout())
  , m_vLayout(new QVBoxLayout(this))
  , m_spinBox(new QSpinBox(this))
  , m_ok(new QPushButton(style()->standardIcon(QStyle::SP_DialogApplyButton),"Apply"))
  , m_cancel(new QPushButton(style()->standardIcon(QStyle::SP_DialogCancelButton),"Cancel"))
  , m_lastFix(fix)
{
  m_spinBox->setValue(fix);
  m_spinBox->setRange(0,19); // WARNING VERIFICAR DEPOIS O LIMITE SUPERIOR CORRETO!
  this->setFixedSize(250,80);
  this->setWindowTitle("Set fix");
  
  m_vLayout->addWidget(m_spinBox,0,Qt::AlignCenter);
  m_hLayout->addWidget(m_ok,0,Qt::AlignBottom|Qt::AlignRight);
  m_hLayout->addWidget(m_cancel,50,Qt::AlignBottom|Qt::AlignRight);
  m_vLayout->addLayout(m_hLayout);
  this->setLayout(m_vLayout);
  
  QObject::connect(m_spinBox,SIGNAL(valueChanged(int)),this,SLOT(newData(int)));
  QObject::connect(m_ok,SIGNAL(clicked(bool)),this,SLOT(accept()));
  QObject::connect(m_cancel,SIGNAL(clicked(bool)),this,SLOT(reject(bool)));
}

void FixDialog::newData(int f) { emit dataValue(m_spinBox->value()); }
void FixDialog::reject(bool b){ emit dataValue(m_lastFix); emit rejected(); }

FixDialog::~FixDialog()
{
  qDebug() << "destroy dialog";
  delete m_spinBox;
  delete m_ok;
  delete m_cancel;
  delete m_hLayout;
}

short int FixDialog::getLastFix() const { return m_lastFix;}

