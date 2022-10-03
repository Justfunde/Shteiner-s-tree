#ifndef __MAIN_WINDOW_H__
#define __MAIN_WINDOW_H__

#include <QMainWindow>
#include <QLabel>
#include <QPushButton>

#include "MatrixWidget/MatrixWidget.hpp"

class MainWindow:public QMainWindow
{
   Q_OBJECT
   private:
   GraphWidget* FirstGraphWidget;
   GraphWidget* SecondGraphWidget;

   public:

   explicit MainWindow(QWidget* Parent = nullptr);

   private slots:
   void OnBrowse();
   void OnProcAlgh();
};


#endif //!__MAIN_WINDOW_H__