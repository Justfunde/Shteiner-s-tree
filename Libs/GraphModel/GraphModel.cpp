#include <QFile>
#include <QTextStream>
#include <QDebug>

#include "Include/GraphModel.hpp"


GraphModel::GraphModel():Nodes(NodeList()) {}

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
      Nodes = tmpList;
   } while (false);
return retVal;
}


NodeList
GraphModel::GetNodes() const {return Nodes;}