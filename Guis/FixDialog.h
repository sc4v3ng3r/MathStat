#ifndef FIX_DIALOG_H
#define FIX_DIALOG_H

#include <QtGui/qdialog.h>

class QSpinBox;
class QPushButton;
class QHBoxLayout;
class QVBoxLayout;

class FixDialog : public QDialog {
  Q_OBJECT
  private:
    QSpinBox* m_spinBox;
    QPushButton* m_ok;
    QPushButton* m_cancel;
    QVBoxLayout* m_vLayout;
    QHBoxLayout* m_hLayout;
    short m_lastFix;
    
public:
    FixDialog(const short &fix, QWidget* parent=0, Qt::WindowFlags f=0);
    virtual ~FixDialog();
    short getLastFix() const;
public Q_SLOTS:
  void newData(int f);
  void reject(bool b);
  
Q_SIGNALS:
 void dataValue(const int fix);
  
}; 
#endif