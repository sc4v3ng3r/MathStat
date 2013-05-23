#ifndef MATHSTAT_H
#define MATHSTAT_H

#include "./Sample.h"
#include "../Views/SampleSpaceView.h"
#include "../Views/StatClassView.h"
#include "../Views/StatisticsView.h"
#include "../Guis/ParserGui.h"

#include <QtGui/qpushbutton.h>
#include <QtGui/qmenubar.h>
#include <QtGui/qmenu.h>
#include <QtGui/qlineedit.h>
#include <QtGui/qtoolbar.h>

class QVBoxLayout;
class QHBoxLayout;

class MathStat : public QWidget {

  Q_OBJECT
private: 
 
 ParserGui m_interpreterPanel;
 
 QMenuBar m_menuBar;
 QMenu m_fileMenu;
 QMenu m_graphcisMenu;
 
 QMenu* m_editMenu;
 QMenu* m_toolsMenu;
 
//  QLineEdit m_dataInput;
 
 QAction m_actionSave;
 QAction m_actionLoad;
 
 QAction* m_fa;
 QAction* m_fi;
 QAction* m_percents;
 QAction* m_actionHide;
 QAction* m_actionShowHistogram;
 QAction* m_actionBurn;
 
 Sample m_samples; // talvez sera uma lista de amostras!
 SampleSpaceView m_view; //
 StatClassView m_classView;
 StatisticsView m_statisticsView;
 
 
// QPushButton m_debug;

 QVBoxLayout *m_layout;

 QToolBar *m_toolBar;
 
public:
  MathStat(QWidget* parent=0);
 ~MathStat();
  
private:
  void setupWindowMenu();
  void setupActions();
  
private Q_SLOTS:
  void handleGraphActions(QAction* action);
  
};
#endif