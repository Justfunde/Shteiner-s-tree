#ifndef __MATRIX_WIDGET_H__
#define __MATRIX_WIDGET_H__

#include <QWidget>
#include <QVBoxLayout>
#include <QPushButton>
#include <QString>
#include <QLabel>

#include "Include/GraphView.hpp"

class GraphWidget:public QWidget
{
   Q_OBJECT
   private:
   GraphView* View;

   public:
   GraphWidget(const QString &Label, QWidget* Parent = nullptr);
  
   void ReadFile(const QString& fName);
   GraphView* GetView() const { return View; }
};


#endif //!__MATRIX_WIDGET_H__