#include "MathStat.h"
#include <QtGui/QVBoxLayout>
#include <QtGui/QHBoxLayout>
#include <QtGui/qdialog.h>
#include <QtGui/qsplitter.h>
#include <Qt/qdir.h>
#include <Qt/qdebug.h>

MathStat::MathStat(QWidget *parent) : QWidget(parent)
  , m_menuBar(this)
  , m_fileMenu("File",&m_menuBar)
  , m_editMenu( new QMenu("Edit", &m_menuBar))
  , m_graphcisMenu("Graphics View",&m_menuBar)
  , m_toolsMenu(new QMenu("Tools", &m_menuBar))
//   , m_dataInput(this)
//   , m_insertButton(new QPushButton(style()->standardIcon(QStyle::SP_DialogApplyButton),"apply",this))
  , m_actionSave("Save",this)
  , m_actionLoad("Load",this)
  , m_actionHide(new QAction("Hide",this))
  , m_actionShowHistogram(new QAction("Histogram", this))
  , m_actionBurn(new QAction("Calculate", this))
  , m_samples(this)
  , m_view(m_samples.m_sampleSpace,this)
  , m_classView(m_samples.m_classModel,this)
  , m_statisticsView(m_samples.m_statisticModel,this)
 // , m_debug(style()->standardIcon(QStyle::SP_MediaPlay),"Debug", this)
//   , m_lock("Load", this)
  , m_layout(new QVBoxLayout(this))
  , m_toolBar(new QToolBar("ToolBar",this))
{
  setupWindowMenu();
  setupActions(); 
  
  m_interpreterPanel.setParent(this);
  
  m_layout->addWidget(&m_menuBar);
  m_toolBar->addAction(style()->standardIcon(QStyle::SP_FileIcon),"New")->setParent(this);
  m_toolBar->addAction(&m_actionLoad);
  m_toolBar->addAction(style()->standardIcon(QStyle::SP_DialogSaveButton),"SaveAs")->setParent(this);
  m_toolBar->addSeparator();
  
  m_actionLoad.setIcon(style()->standardIcon(QStyle::SP_DialogOpenButton));
  
  // graphics icons
  m_actionShowHistogram->setIcon(QIcon(QString("../mathstatIcon/histogram.svg")));
  m_actionShowHistogram->setIconText(QString("Histogram"));
  m_actionShowHistogram->setEnabled(false);
  m_toolBar->addAction(m_actionShowHistogram);
  
  m_layout->addWidget(m_toolBar);
  m_layout->addWidget(&m_classView);
  m_layout->addWidget(&m_interpreterPanel);
  
 // m_hlayout->addWidget(&m_dataInput,0,Qt::AlignLeft);
//   m_hlayout->addWidget(m_insertButton,1,Qt::AlignLeft);
  //m_hlayout->addWidget(&m_debug,20,Qt::AlignLeft);
  //m_hlayout->addWidget(&m_lock,280,Qt::AlignLeft);
  
  //m_layout->addLayout(m_hlayout);
  m_view.setMinimumSize(450,150);
  m_view.setMaximumSize(450,250);
  
  m_statisticsView.setGeometry(650,350,300,300);
  m_statisticsView.setMaximumSize(300,400);
  m_layout->addWidget(&m_view,0,Qt::AlignLeft);
  //m_layout->addWidget(&m_debug,1,Qt::AlignVertical_Mask);
  
//   m_editMenu Colocar uma dialog para editar o fix....
  m_actionSave.setShortcut(QKeySequence(Qt::CTRL+Qt::Key_S));
  m_actionLoad.setShortcut(QKeySequence(Qt::CTRL+Qt::Key_L));
  
  QObject::connect(m_actionBurn,SIGNAL(triggered(bool)),&m_samples,SLOT(calcAll()));
  QObject::connect(m_actionBurn,SIGNAL(triggered(bool)),&m_samples.m_sampleSpace,SLOT(decimalParser()));
  
  QObject::connect(&m_actionSave,SIGNAL(triggered(bool)),&m_samples.m_sampleSpace,SLOT(save()));
  QObject::connect(&m_actionLoad,SIGNAL(triggered()),&m_samples.m_sampleSpace,SLOT(loadData()));
  QObject::connect(m_actionShowHistogram,SIGNAL(triggered()),&m_samples,SLOT(showHistogram()));
  QObject::connect(&m_samples,SIGNAL(stateChanged(bool)),m_actionShowHistogram,SLOT(setEnabled(bool)));
  
  QString tmp;
  tmp.append(QDir::homePath()).append("/MathStat");
  QDir dir(tmp);
  
  if (!dir.exists())
    dir.mkdir(tmp);
  
}

void MathStat::setupWindowMenu()
{
  m_fileMenu.addAction(&m_actionSave);
  m_fileMenu.addAction(&m_actionLoad);
  m_menuBar.addMenu(&m_fileMenu);
  m_menuBar.addMenu(m_editMenu);
  m_menuBar.addMenu(m_toolsMenu);
  
  QMenu *histogramMenu = new QMenu("Histogram", &m_graphcisMenu);
  
  m_fa = new QAction(QString("Absolute frequency"),histogramMenu);
  m_fa->setCheckable(true);
  m_fa->setChecked(true);
  m_fa->setEnabled(false);
  m_fa->setData(QVariant(Histogram::Absolute));
  histogramMenu->addAction(m_fa);
  
  m_fi = new QAction(QString("Relative frequency"), histogramMenu);
  m_fi->setCheckable(true);
  m_fi->setChecked(false);
  m_fi->setData(QVariant(Histogram::Relative));
  histogramMenu->addAction(m_fi);
  
  m_percents = new QAction(QString("Percents %"),histogramMenu);
  m_percents->setCheckable(true);
  m_percents->setChecked(false);
  m_percents->setData(QVariant(Histogram::Percents));
  histogramMenu->addAction(m_percents);
  
  histogramMenu->addSeparator();
  m_actionHide->setCheckable(true);
  m_actionHide->setChecked(false);
  
  histogramMenu->addAction(m_actionHide);
  m_graphcisMenu.addMenu(histogramMenu);
  m_menuBar.addMenu(&m_graphcisMenu);
  
  histogramMenu->setEnabled(false);
  QObject::connect(&m_samples,SIGNAL(stateChanged(bool)),histogramMenu,SLOT(setEnabled(bool)));
  QObject::connect(histogramMenu,SIGNAL(triggered(QAction*)),SLOT(handleGraphActions(QAction*)));
}

void MathStat::handleGraphActions(QAction* action)
{
  switch(action->data().toInt()){
    case Histogram::Absolute:
      m_fa->setEnabled(false);
      m_fa->setChecked(true);
      m_fi->setEnabled(true);
      m_fi->setChecked(false);
      m_percents->setEnabled(true);
      m_percents->setChecked(false);
      m_samples.restoreGraph(Histogram::Absolute);
      break;
      
    case Histogram::Relative:
      m_fi->setEnabled(false);
      m_fi->setChecked(true);
      m_fa->setEnabled(true);
      m_fa->setChecked(false);
      m_percents->setEnabled(true);
      m_percents->setChecked(false);
      m_samples.restoreGraph(Histogram::Relative);
      break;
      
    case Histogram::Percents:
      m_percents->setEnabled(false);
      m_percents->setChecked(true);
      m_fa->setEnabled(true);
      m_fa->setChecked(false);
      m_fi->setEnabled(true);
      m_fi->setChecked(false);
      m_samples.restoreGraph(Histogram::Percents);
      break;
  }
  return;
}

void MathStat::setupActions()
{
  QAction* fixAction = new QAction("Fix",m_editMenu);
  m_editMenu->addAction(fixAction);
  QObject::connect(fixAction,SIGNAL(triggered(bool)),&m_samples.m_classModel,SLOT(createFixDialog()));
  
  QAction* autoSort = new QAction("AutoSort", m_toolsMenu);
  autoSort->setCheckable(true);
  QObject::connect(autoSort,SIGNAL(toggled(bool)),&m_samples.m_sampleSpace,SLOT(AutoSort(bool)));
  m_toolsMenu->addAction(autoSort);
  m_toolBar->addAction(m_actionBurn);
  m_actionBurn->setIcon(style()->standardIcon(QStyle::SP_ArrowUp));
  
}

MathStat::~MathStat()
{
  //delete m_hlayout;
}
