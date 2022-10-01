#include "GraphView.hpp"

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


void GraphView::paintEvent(QPaintEvent *Event)
{

   QPainter Painter(this);
   DrawWorkspace(Painter);
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

