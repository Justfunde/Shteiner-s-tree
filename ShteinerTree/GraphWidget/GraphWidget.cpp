#include "GraphWidget.hpp"

GraphWidget::GraphWidget(
   const QString &Label,
    QWidget* Parent)
    :QWidget(Parent)
    ,View(new GraphView(this))
{
   QLabel* label = new QLabel(Label);
   QVBoxLayout* mainLayout = new QVBoxLayout(this);

   QHBoxLayout* labelLayout = new QHBoxLayout(this);

   labelLayout->addSpacerItem(new QSpacerItem(20,20,QSizePolicy::Expanding,QSizePolicy::Minimum));
   labelLayout->addWidget(label);
   labelLayout->addSpacerItem(new QSpacerItem(20,20,QSizePolicy::Expanding,QSizePolicy::Minimum));

   mainLayout->addLayout(labelLayout);

   QHBoxLayout* matrLayout = new QHBoxLayout(this);
   matrLayout->addSpacerItem(new QSpacerItem(20,20,QSizePolicy::Expanding,QSizePolicy::Minimum));
   matrLayout->addWidget(View);
   matrLayout->addSpacerItem(new QSpacerItem(20,20,QSizePolicy::Expanding,QSizePolicy::Minimum));


   mainLayout->addLayout(matrLayout);
   setLayout(mainLayout);
   setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding );
   setFixedSize(400, 400);
}


void
GraphWidget::ReadFile(
   const QString& fName)
{
   if(fName.isEmpty()) { return;}

   std::shared_ptr<GraphModel> model(new GraphModel);
   model->InitModel(fName);
   View->SetModel(model);
}