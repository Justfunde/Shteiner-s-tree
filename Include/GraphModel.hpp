#ifndef __GRAPH_MODEL_H__
#define __GRAPH_MODEL_H__

#include <QString>
#include <QPoint>

#include <memory>
#include <list>

class Node;

using NodeList = std::list<std::shared_ptr<Node>>;

class Node
{
   private:
   QString Name;
   NodeList Links;
   QPoint Indicies;

   public:
   Node::Node( const QString &Name, const QPoint &Indicies = QPoint(0,0));

   void AddLink(std::shared_ptr<Node> Vertex);
   void DeleteLink(std::shared_ptr<Node> Vertex);

   void SetIndicies(const QPoint &Indicies);

   QPoint GetIndicies() const;
   NodeList GetLinks() const;

   //operators
   friend bool operator==(const Node& First,const Node& Second);
   static std::shared_ptr<Node> CreateNode(const QString &Name, const QPoint &Indicies = QPoint()) { return std::shared_ptr<Node>(new Node(Name,Indicies)); }
};


class GraphModel
{
   private:
   NodeList Nodes;

   public:
   GraphModel();

   bool InitModel(const QString &GraphFileName);
   NodeList GetNodes() const;
};

#endif //!__GRAPH_VIEW_H__