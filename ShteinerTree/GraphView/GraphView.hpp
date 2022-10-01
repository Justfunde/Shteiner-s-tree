#ifndef __GRAPH_VIEW_H__
#define __GRAPH_VIEW_H__

#include "../GraphModel/GraphModel.hpp"

#include <QWidget>
#include <QPainter>
#include <QPaintEvent>
#include <memory>

class GraphView:public QWidget
{
   Q_OBJECT
   private:
   std::shared_ptr<GraphModel> Model;
   

   public:
   explicit GraphView(QWidget *Parent = nullptr);
   void SetModel(std::shared_ptr<GraphModel> Model) {this->Model = Model; }

   protected:
   virtual void paintEvent(QPaintEvent *Event) override final;

   private:
   void DrawWorkspace(QPainter &Painter);
   void DrawVerticies();
   void DrawEdges();

};

#endif //!__GRAPH_VIEW_H__