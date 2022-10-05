#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QFileDialog>

#include "MainWindow.hpp"
#include "Include/ShteinerTreeAlgh.hpp"


MainWindow::MainWindow(QWidget* Parent)
   :QMainWindow(Parent)
   ,FirstGraphWidget(new GraphWidget("Исходная матрица"))
   ,SecondGraphWidget(new GraphWidget("Преобразованная матрица"))
{
   setWindowIcon(QIcon(":Images/Mw.ico"));

   setCentralWidget(new QWidget);

   QHBoxLayout* buttonsLayout = new QHBoxLayout;
   QPushButton* buttonBrowse = new QPushButton(tr("Выбрать файл"),this);
   QPushButton* buttonAlghProcess = new QPushButton(tr("Обработать ДРП"), this);
   buttonsLayout->addSpacerItem(new QSpacerItem(20,20,QSizePolicy::Expanding,QSizePolicy::Minimum));
   buttonsLayout->addWidget(buttonAlghProcess);
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

   connect(buttonBrowse,&QPushButton::clicked,this,&MainWindow::OnBrowse);
   connect(buttonAlghProcess,&QPushButton::clicked,this,&MainWindow::OnProcAlgh);
}

void
MainWindow::OnBrowse()
{
   QString fileName = QFileDialog::getOpenFileName(this, tr("Выберите файл с графом"),"D:/",tr("GraphFiles (*.graph *.txt)"));
   if(fileName.isEmpty()) { return;}
   FirstGraphWidget->ReadFile(fileName);
}


void 
MainWindow::OnProcAlgh()
{
   ShteinerTree::AlgProcessor processor;
   processor.SetModel(FirstGraphWidget->GetView()->GetModel());
   SecondGraphWidget->GetView()->SetModel(processor.Process());
}