#include <QtMath>
#include <QDebug>
#include <numeric>

#include "Include/ShteinerTreeAlgh.hpp"

#define QINT32_MAX (std::numeric_limits<qint32>::max())
#define QINT32_MIN (std::numeric_limits<qint32>::min())


inline
qint32
ShteinerTree::AlgProcessor::CalcTriangleArea(
   const QPoint& a,
   const QPoint& b,
   const QPoint& c) 
{
	return (b.x() - a.x()) * (c.y() - a.y()) - (b.y() - a.y()) * (c.x() - a.x());
}

 
inline
bool
ShteinerTree::AlgProcessor::IsPointsIntersected(
   qint32 a,
   qint32 b,
   qint32 c,
   qint32 d) 
{
	if (a > b)  std::swap (a, b);
	if (c > d)  std::swap (c, d);
	return qMax(a,c) <= qMin(b,d);
}
 

bool 
ShteinerTree::AlgProcessor::IsIntersected (
   const QLine& Fst,
   const QLine& Scnd) {

   QPoint a = Fst.p1();
   QPoint b = Fst.p2();
   QPoint c = Scnd.p1();
   QPoint d = Scnd.p2();
	return IsPointsIntersected (a.x(), b.x(), c.x(), d.x())
		&& IsPointsIntersected (a.y(), b.y(), c.y(), d.y())
		&& CalcTriangleArea(a,b,c) * CalcTriangleArea(a,b,d) <= 0
		&& CalcTriangleArea(c,d,a) * CalcTriangleArea(c,d,b) <= 0;
}


qint32
ShteinerTree::AlgProcessor::CalcMinManhattanDist( 
   const NodeList&VertexList,
   NodePtr Vertex,
   const NodeList &ExceptVerticies)
{
    qint32 minDistance = QINT32_MAX;
   
   for(const auto& it : VertexList)
   {      
      bool isFind = false;
      for( const auto& exceptVerIter : ExceptVerticies)
      {
         if(*exceptVerIter == *it) 
         { isFind = true; break;}
      }
      if(isFind) { continue;}

      qint32 currDistance = CalcManhattanDistance(Vertex, it);
      qDebug()<< currDistance;
      if(currDistance <= minDistance && 0 != currDistance) 
      {
          minDistance = currDistance;
      }
   }
   return minDistance;
}

NodeList::const_iterator 
ShteinerTree::AlgProcessor::FindByVertex(
   const NodeList &VertexList,
   NodePtr Vertex)
{
   for(NodeList::const_iterator it = VertexList.begin(); it != VertexList.end(); it++)
   {
      if(**it == *Vertex) { return it;}
   }
   return VertexList.end();
}

GraphModelPtr 
ShteinerTree::AlgProcessor::Process()
{
   if(nullptr == Model) { return nullptr;}

   NodeList resultNodeList;

   NodeList nodeList = Model->GetNodes();
   NodeList::const_iterator currentIter = nodeList.begin();
   NodeList exceptNodes;
   bool isOk = true;
   while(!nodeList.empty()|| nodeList.size() != 1)
   {
      if(nodeList.size() == 1) 
      { break;}
      if(nodeList.size() == 2)
      {
         nodeList.erase(currentIter);
         NodePtr first = *nodeList.begin();
         NodePtr res = *FindMinManhattanDistance(Model->GetNodes(),first,nodeList);

         //first->AddLink(res);
         LFormes resFormes = CreateLform(first,res);
         NodePtr second = Node::CreateNode("",resFormes.first.first.p2());
         
         first->AddLink(second);
         second->AddLink(res);

         resultNodeList.push_back(res);
         resultNodeList.push_back(second);
         resultNodeList.push_back(first);
         break;

      }
      
      // current node
      NodePtr currNode = *currentIter;
      exceptNodes.push_back(currNode);

      // secondNode
      auto secondNodeIter = FindMinManhattanDistance(nodeList, currNode, exceptNodes);
      NodePtr secondNode = *secondNodeIter;
      exceptNodes.push_back(secondNode);

      //thirdNode
      auto thirdNodeIter = FindMinManhattanDistance(nodeList,secondNode,exceptNodes);
      NodePtr thirdNode = *thirdNodeIter;

      qDebug() << currNode->GetIndicies();
      qDebug() << secondNode->GetIndicies();
      qDebug() << thirdNode->GetIndicies();

      LFormes firstForms = CreateLform(currNode,secondNode);
      LFormes secondForms = CreateLform(secondNode, thirdNode);
      
      NodePtr resVertex = GetResultVertex(firstForms, secondForms);
      if(nullptr == resVertex) { isOk = false; break;}
      exceptNodes.push_back(resVertex);
      qDebug() << resVertex->GetIndicies();

      currNode->AddLink(resVertex);
      qDebug() << currNode->GetIndicies();
      resVertex->AddLink(secondNode);
      //resVertex->AddLink(thirdNode);

      resultNodeList.push_back(currNode);
      resultNodeList.push_back(resVertex);
      resultNodeList.push_back(secondNode);

      nodeList.erase(FindByVertex(nodeList,currNode));
      currentIter = FindByVertex(nodeList,secondNode); 
      
      qDebug() << (*currentIter)->GetIndicies();
   }

   GraphModelPtr resultModel(new GraphModel);
   resultModel->SetNodes(resultNodeList);
   return resultModel;
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


NodeList::const_iterator
ShteinerTree::AlgProcessor::FindMinManhattanDistance(
   const NodeList &VertexList,
   NodePtr Vertex,
   const NodeList &ExceptVerticies)
{
   qint32 minDistance = QINT32_MAX;
   NodeList::const_iterator retVal = VertexList.begin();
   
   for(NodeList::const_iterator it = VertexList.begin(); it != VertexList.end();it++)
   {      
      bool isFind = false;
      for( NodeList::const_iterator exceptVerIter = ExceptVerticies.begin(); exceptVerIter != ExceptVerticies.end(); exceptVerIter++)
      {
         if(**exceptVerIter == **it) 
         { isFind = true; break;}
      }
      if(isFind) { continue;}

      qint32 currDistance = CalcManhattanDistance(Vertex, *it);
      qDebug()<< currDistance;
      if(-1 == currDistance) { return VertexList.end();}
      if(currDistance <= minDistance && 0 != currDistance) 
      {
          minDistance = currDistance;
          retVal = it;
      }
   }
   return retVal;
}


LFormes
ShteinerTree::AlgProcessor::CreateLform(
   NodePtr Fst,
   NodePtr Scnd)
{
   LFormes retVal;
   if(nullptr == Fst || nullptr == Scnd){ return retVal;}

   const QPoint fstPoint = Fst->GetIndicies();
   const QPoint scndPoint = Scnd->GetIndicies();

   retVal.first.first = QLine(Fst->GetIndicies(),QPoint(fstPoint.x(),scndPoint.y()));
   retVal.first.second = QLine(QPoint(fstPoint.x(),scndPoint.y()),Scnd->GetIndicies());

   retVal.second.first = QLine(Fst->GetIndicies(),QPoint(scndPoint.x(),fstPoint.y()));
   retVal.second.second = QLine(QPoint(scndPoint.x(),fstPoint.y()),Scnd->GetIndicies());   
   return retVal;
}


 bool
 ShteinerTree::AlgProcessor::IsLFormIntersected(
   const LForm &Fst,
   const LForm &Scnd)
{
   //Fst.first with scnd;

   if(IsIntersected(Fst.first,Scnd.first)) { return true;}
   if(IsIntersected(Fst.first,Scnd.second)) { return true;}

   if(IsIntersected(Fst.second,Scnd.first)) { return true;}
   if(IsIntersected(Fst.second,Scnd.second)) { return true;}

   return false;

}


NodePtr
ShteinerTree::AlgProcessor::GetResultVertex(
  const LFormes& Fst,
  const LFormes& Scnd)
{
   if(IsLFormIntersected(Fst.first,Scnd.first)) { return Node::CreateNode("",Fst.first.first.p2());}
   if(IsLFormIntersected(Fst.first,Scnd.second)) { return Node::CreateNode("",Fst.first.first.p2());}

   if(IsLFormIntersected(Fst.second,Scnd.first)) { return Node::CreateNode("",Fst.second.first.p2());}
   if(IsLFormIntersected(Fst.second,Scnd.second)) { return Node::CreateNode("",Fst.second.first.p2());}

   return nullptr;
}


