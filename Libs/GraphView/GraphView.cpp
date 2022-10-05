#include "Include/GraphView.hpp"
#include <QDebug>
#include <QPointF>

namespace WorkspaceParameters
{
   constexpr quint32 width = 220;
   constexpr quint32 height = 220;
   constexpr quint32 vertexSz = 10;
}

GraphView::GraphView(
   QWidget* Parent)
   :QWidget(Parent)
{
   setFixedSize(WorkspaceParameters::width + 1, WorkspaceParameters::height + 1);
}


void
GraphView::DrawWorkspace(
   QPainter &Painter)
{
   QPen pen;
   pen.setColor(Qt::black);
   pen.setWidth(1);

   Painter.setPen(pen);

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


void
GraphView::DrawVerticies(
   QPainter& Painter)
{
   if(nullptr == Model) { return;}

   QPen pen;
   pen.setColor(Qt::red);
   pen.setWidth(WorkspaceParameters::vertexSz);
   
   Painter.setPen(pen);

   NodeList list = Model->GetNodes();
   for(const auto& iter : list)
   {
      const QPoint& indicies = iter->GetIndicies();
      qDebug() << indicies;
      qDebug() << CalcPointCoord(iter->GetIndicies());
      Painter.drawEllipse(ConvertVertInd2RoundRect(iter->GetIndicies()));
   }
}

void GraphView::DrawEdges(QPainter &Painter)
{
   if(nullptr == Model) { return;}

   QPen pen;
   pen.setColor(Qt::red);
   pen.setWidth(2);
   
   Painter.setPen(pen);

   const NodeList& list = Model->GetNodes();

   for(const auto& listIter:list)
   {
      const NodeList& links = listIter->GetLinks();
      for(const auto& linksIter:links)
      {
         Painter.drawLine(CalcPointCoord(listIter->GetIndicies()),CalcPointCoord(linksIter->GetIndicies()));
      }
   }
}


QPoint GraphView::CalcPointCoord(const QPoint &Indicies)
{
   constexpr quint32 beginOffs = 20;
   constexpr quint32 mulCoeff = 20;
   return QPoint(beginOffs + Indicies.x() * mulCoeff,beginOffs + Indicies.y() * mulCoeff);
}


QRect GraphView::ConvertVertInd2RoundRect(const QPoint &Indicies)
{
   const QPoint VertCenterPoint = CalcPointCoord(Indicies);
   return QRect(VertCenterPoint.x() - 2,VertCenterPoint.y() - 2,4,4);
}


void GraphView::paintEvent(QPaintEvent *Event)
{
   QPainter Painter(this);
   DrawWorkspace(Painter);
   DrawEdges(Painter);
   DrawVerticies(Painter);
}

