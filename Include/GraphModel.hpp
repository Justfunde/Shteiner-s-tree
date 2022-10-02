#ifndef __GRAPH_MODEL_H__
#define __GRAPH_MODEL_H__

#include <QString>
#include <QPoint>

#include <memory>
#include <list>

class Node;

using NodePtr = std::shared_ptr<Node>;

using NodeList = std::list<NodePtr>;


class Node
{
   private:
   QString Name;
   NodeList Links;
   QPoint Indicies;

   public:
   Node::Node( const QString &Name, const QPoint &Indicies = QPoint(0,0));

   void AddLink(NodePtr Vertex);
   void DeleteLink(NodePtr Vertex);

   void SetIndicies(const QPoint &Indicies);

   QPoint GetIndicies() const;
   NodeList GetLinks() const;

   //operators
   friend bool operator==(const Node& First,const Node& Second);
   static NodePtr CreateNode(const QString &Name, const QPoint &Indicies = QPoint()) { return NodePtr(new Node(Name,Indicies)); }
};


class GraphModel
{
   private:
   NodeList Nodes;

   public:
   GraphModel();

   bool InitModel(const QString &GraphFileName);
   void SetNodes(const NodeList Nodes) { this->Nodes = Nodes;}
   NodeList GetNodes() const;
};

#endif //!__GRAPH_VIEW_H__