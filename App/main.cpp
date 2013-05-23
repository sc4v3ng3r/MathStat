#include "MathStat.h"
#include <Qt/qapplication.h>
#include <QtGui/qpushbutton.h>

int main(int argc, char **argv){
  QApplication app(argc, argv);
  MathStat program;
  
  program.setMinimumSize(400,300);
  program.show();
  
  return app.exec();
}
