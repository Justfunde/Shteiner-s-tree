#ifndef __MATRIX_WIDGET_H__
#define __MATRIX_WIDGET_H__

#include <QWidget>
#include <QVBoxLayout>
#include <QPushButton>
#include <QString>
#include <QLabel>

class GraphWidget:public QWidget
{
   Q_OBJECT
   QPushButton* button;
   public:
   GraphWidget(const QString &Label, QWidget* Parent = nullptr):QWidget(Parent),button(new QPushButton(this)) 
   {
      QLabel* label = new QLabel(Label);
      QVBoxLayout* mainLayout = new QVBoxLayout(this);

      QHBoxLayout* labelLayout = new QHBoxLayout(this);

      labelLayout->addSpacerItem(new QSpacerItem(20,20,QSizePolicy::Expanding,QSizePolicy::Minimum));
      labelLayout->addWidget(label);
      labelLayout->addSpacerItem(new QSpacerItem(20,20,QSizePolicy::Expanding,QSizePolicy::Minimum));
      button->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
      mainLayout->addLayout(labelLayout);
      mainLayout->addWidget(button);
      setLayout(mainLayout);
      setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding );
      setFixedSize(400, 400);
   }
};


#endif //!__MATRIX_WIDGET_H__