#ifndef __GRAPH_VIEW_H__
#define __GRAPH_VIEW_H__

#include "Include/GraphModel.hpp"

#include <QWidget>
#include <QPainter>
#include <QPaintEvent>
#include <QRect>

#include <memory>

class GraphView:public QWidget
{
   //todo:add Q_OBJECT
   private:
   std::shared_ptr<GraphModel> Model;
   

   public:
   explicit GraphView(QWidget *Parent = nullptr);
   void SetModel(std::shared_ptr<GraphModel> Model) {this->Model = Model; update(); }

   std::shared_ptr<GraphModel> GetModel() const { return Model;}

   protected:
   virtual void paintEvent(QPaintEvent *Event) override final;

   private:
   void DrawWorkspace(QPainter &Painter);
   void DrawVerticies(QPainter &Painter);
   void DrawEdges(QPainter &Painter);

   QPoint CalcPointCoord(const QPoint &Indicies);

   QRect ConvertVertInd2RoundRect(const QPoint &Indicies);
};

#endif //!__GRAPH_VIEW_H__