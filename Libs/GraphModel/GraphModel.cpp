#include <QFile>
#include <QTextStream>
#include <QDebug>

#include "Include/GraphModel.hpp"


GraphModel::GraphModel():Nodes(NodeList()) 
{}


bool
GraphModel::InitModel(
   const QString &GraphFileName)
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

         tmpList.push_back(Node::CreateNode(nodeName,QPoint(j,i)));
      }
      if(!retVal) { break;}

      Nodes.sort([](NodePtr p1, NodePtr p2)
         {
            const QPoint& p1Point = p1->GetIndicies();
            const QPoint& p2Point = p2->GetIndicies();
            return p1Point.x() < p2Point.x() && p1Point.y() < p2Point.y();
         });

      Nodes = std::move(tmpList);
   } while (false);
return retVal;
}


const NodeList&
GraphModel::GetNodes() const {return Nodes;}