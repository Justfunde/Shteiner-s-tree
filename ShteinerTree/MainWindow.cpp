#include <QHBoxLayout>
#include <QVBoxLayout>

#include "MainWindow.hpp"

MainWindow::MainWindow(QWidget* Parent)
   :QMainWindow(Parent)
   ,FirstGraphWidget(new GraphWidget("Исходная матрица"))
   ,SecondGraphWidget(new GraphWidget("Преобразованная матрица"))
{
   setCentralWidget(new QWidget);

   QHBoxLayout* buttonsLayout = new QHBoxLayout;
   QPushButton* buttonBrowse = new QPushButton(tr("Выбрать файл"),this);
   buttonsLayout->addSpacerItem(new QSpacerItem(20,20,QSizePolicy::Expanding,QSizePolicy::Minimum));
   buttonsLayout->addWidget(buttonBrowse);
   buttonsLayout->addSpacerItem(new QSpacerItem(20,20,QSizePolicy::Minimum,QSizePolicy::Minimum));
   
   QVBoxLayout* mainLayout = new QVBoxLayout(centralWidget());


   QHBoxLayout* mainMatrLayout = new QHBoxLayout(this);
   mainMatrLayout->addWidget(FirstGraphWidget);
   mainMatrLayout->addWidget(SecondGraphWidget);   

   mainLayout->addLayout(mainMatrLayout);
   mainLayout->addSpacerItem(new QSpacerItem(20,20,QSizePolicy::Expanding,QSizePolicy::Expanding));
   mainLayout->addLayout(buttonsLayout);
   mainLayout->addSpacerItem(new QSpacerItem(20,20,QSizePolicy::Expanding,QSizePolicy::Minimum));

   layout()->setSizeConstraint(QLayout::SetFixedSize);

}