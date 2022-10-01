#include "GraphView.hpp"
#include <QDebug>

namespace WorkspaceParameters
{
   constexpr quint32 width = 220;
   constexpr quint32 height = 220;
}

GraphView::GraphView(QWidget *Parent):QWidget(Parent)
{
   setFixedSize(WorkspaceParameters::width + 1, WorkspaceParameters::height + 1);
   
}

void GraphView::DrawWorkspace(QPainter &Painter)
{
   QPen pen;
   pen.setColor(Qt::black);
   pen.setWidth(1);

   Painter.setPen(pen);
   //Painter.drawRect(QRect(0,0,WorkspaceParameters::width,WorkspaceParameters::height));

   //verticalLine
   for(quint32 j = 0;j <= WorkspaceParameters::width; j += 20)
   {
      Painter.drawLine(j, 0, j, WorkspaceParameters::height);
   }

   //horizontalLine
   for(quint32 i = 0;i <= WorkspaceParameters::width; i += 20)
   {
      Painter.drawLine(0, i, WorkspaceParameters::width,i);
   }
   
}
void GraphView::DrawVerticies(QPainter &Painter)
{
   if(nullptr == Model) { return;}
   QPen pen;
   pen.setColor(Qt::black);
   pen.setWidth(5);
   
   Painter.setPen(pen);

   NodeList list = Model->GetNodes();
   
   
   for(auto iter = list.begin(); iter != list.end();iter++)
   {
      QPoint indicies = (*iter)->GetIndicies();
      qDebug() << indicies;
      Painter.drawPoint(20 + indicies.x() * 20, 20 +  indicies.y() * 20);
   }
}


void GraphView::paintEvent(QPaintEvent *Event)
{

   QPainter Painter(this);
   DrawWorkspace(Painter);
   DrawVerticies(Painter);
   //QPen pen;
   //pen.setColor(Qt::black);
   //pen.setWidth(1);
//
   //Painter.setPen(pen);
   ////Painter.drawRect(QRect(0,0,WorkspaceParameters::width,WorkspaceParameters::height));
//
   ////verticalLine
   //for(quint32 j = 0;j <= WorkspaceParameters::width; j += 20)
   //{
   //   Painter.drawLine(j, 0, j, WorkspaceParameters::height);
   //}
//
   ////horizontalLine
   //for(quint32 i = 0;i <= WorkspaceParameters::width; i += 20)
   //{
   //   Painter.drawLine(0, i, WorkspaceParameters::width,i);
   //}
   
}

