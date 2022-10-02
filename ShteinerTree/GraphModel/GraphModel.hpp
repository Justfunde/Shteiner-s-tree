#ifndef __GRAPH_MODEL_H__
#define __GRAPH_MODEL_H__

#include <QWidget>
#include <QPair>
#include <QList>
#include <QString>
#include <QPoint>
#include <QFile>
#include <QTextStream>
#include <QDebug>

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
   Node::Node(
   const QString &Name,
   QPoint Indicies)
   :Indicies(0, 0)
{
   this->Name = Name;
   if(Indicies.x() < 10 && Indicies.y() < 10) 
   {
      this->Indicies = Indicies;
   }
}

   void AddLink(std::shared_ptr<Node> Vertex)
{
   Links.push_back(Vertex);
}


void DeleteLink(std::shared_ptr<Node> Vertex)
{
   const auto foundObj = std::find(Links.begin(), Links.end(), Vertex);
   Links.erase(foundObj);
}


//setters
   void SetIndicies(const QPoint &Indicies)
   {
      if(Indicies.x() < 10 && Indicies.y() < 10) 
      {
         this->Indicies = Indicies;
      }
   }

   //getters
  //getters
   QPoint GetIndicies() const
   {
      return Indicies;
   }
   NodeList GetLinks() const { return Links;}

   //operators
   friend bool operator==(const Node& First,const Node& Second);
   //static std::shared_ptr<Node> CreateNode(const QString &Name, const QPoint &Indicies = QPoint()) { return std::shared_ptr<Node>(new Node(Name,Indicies));}
};


class GraphModel
{
   private:
   NodeList Nodes;

   public:
   GraphModel():Nodes(NodeList()) {}

   bool InitModel(const QString &GraphFileName)
   {
      bool retVal = true;
   do
   {
      if(GraphFileName.isEmpty()) {return false;}

      QFile file(GraphFileName);
      retVal = file.open(QIODevice::ReadOnly | QIODevice::Text);
      if(!retVal) { break;}

      QTextStream fstream(&file);
      NodeList tmpList;
      while(!fstream.atEnd())
      {
         QString nodeName;
         qint32 i, j;
         fstream >> nodeName >> i >> j;
         qDebug() << nodeName << i << j;
         std::shared_ptr<Node> node(new Node(nodeName,QPoint(j,i)));
         if(nullptr == node) { retVal = false; break;}
         tmpList.push_back(node);
      }
      if(!retVal) { break;}

      Nodes = tmpList;

      auto endIter = Nodes.end();
      endIter--;
      for(auto it = Nodes.begin(); it != endIter;)
      {
         (*it)->AddLink(*(++it));
      }


   } while (false);
   return retVal;
   }
   NodeList GetNodes() const {return Nodes;}
};

#endif //!__GRAPH_VIEW_H__