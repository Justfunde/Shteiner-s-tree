#ifndef __GRAPH_VIEW_H__
#define __GRAPH_VIEW_H__

#include "../GraphModel/GraphModel.hpp"

#include <QWidget>
#include <QPainter>
#include <QPaintEvent>
#include <memory>
#include <QPointF>

class GraphView:public QWidget
{
   Q_OBJECT
   private:
   std::shared_ptr<GraphModel> Model;
   

   public:
   explicit GraphView(QWidget *Parent = nullptr);
   void SetModel(std::shared_ptr<GraphModel> Model) {this->Model = Model; update(); }

   protected:
   virtual void paintEvent(QPaintEvent *Event) override final;

   private:
   void DrawWorkspace(QPainter &Painter);
   void DrawVerticies(QPainter &Painter);
   void DrawEdges(QPainter &Painter);

   QPoint CalcPointCoord(const QPoint &Indicies);

};

#endif //!__GRAPH_VIEW_H__