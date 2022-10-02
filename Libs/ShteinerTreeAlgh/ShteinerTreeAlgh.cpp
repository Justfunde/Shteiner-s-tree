#include <QtMath>

#include "Include/ShteinerTreeAlgh.hpp"


NodeList::iterator 
ShteinerTree::AlgProcessor::FindByVertex(
   NodeList &VertexList,
   NodePtr Vertex)
{
   return std::find(VertexList.begin(),VertexList.end(),Vertex);
}

std::shared_ptr<GraphModel> 
ShteinerTree::AlgProcessor::Process()
{
   //if(nullptr == Model) { return nullptr;}
//
   //NodeList nodeList = Model->GetNodes();
   //NodeList::iterator currentIter = nodeList.begin();
   //while(!nodeList.empty()|| nodeList.size() != 1)
   //{
   //   NodePtr currNode = *currentIter;
   //   auto foundFirstMinDistObj = FindMinManhattanDistance(nodeList, *currentIter);
   //   LForm lForms = CreateLformVerticies(*currentIter,*foundFirstMinDistObj);
//
   //   nodeList.remove()
//
   //}
   return nullptr;
}

inline
qint32
ShteinerTree::AlgProcessor::CalcManhattanDistance(
   NodePtr Fst,
   NodePtr Scnd)
{
   if(nullptr == Fst || nullptr == Scnd) { return 0;}

   const QPoint fstPoint = Fst->GetIndicies();
   const QPoint scndPoint = Scnd->GetIndicies();

   return static_cast<quint32>(qAbs(fstPoint.x() - scndPoint.x()) + qAbs(fstPoint.y() - scndPoint.y()));
}


inline
NodeList::iterator
ShteinerTree::AlgProcessor::FindMinManhattanDistance(
   NodeList &VertexList,
   NodePtr Vertex,
   NodePtr ExceptVertex)
{
   qint32 minDistance = -1;
   NodeList::iterator retVal = VertexList.begin();
   for(NodeList::iterator it = VertexList.begin(); it != VertexList.end();it++)
   {
      if(*it == ExceptVertex) { continue;}

      qint32 currDistance = CalcManhattanDistance(Vertex, *it);
      if(-1 == currDistance) { return VertexList.end();}
      if(currDistance <= minDistance && 0 != currDistance) 
      {
          minDistance = currDistance;
          retVal = it;
      }
   }
   return retVal;
}


LForm
ShteinerTree::AlgProcessor::CreateLformVerticies(
   NodePtr Fst,
   NodePtr Scnd)
{
   LForm retVal;
   if(nullptr == Fst || nullptr == Scnd){ return retVal;}

   const QPoint fstPoint = Fst->GetIndicies();
   const QPoint scndPoint = Scnd->GetIndicies();

   retVal.first = Node::CreateNode("", QPoint(fstPoint.x(),scndPoint.y()));
   retVal.second = Node::CreateNode("",QPoint(scndPoint.x(),fstPoint.y()));
   return retVal;
}

NodePtr
ShteinerTree::AlgProcessor::GetResultVertex(
   const LForm &Fst,
   const LForm &Scnd)
{
   if(*Fst.first == *Scnd.first) { return Fst.first; }
   if(*Fst.first == *Scnd.second) { return Fst.first; }
   if(*Fst.second == *Scnd.first) { return Fst.second; }
   if(*Fst.second == *Scnd.second) { return Fst.second; }
   return nullptr;
}
