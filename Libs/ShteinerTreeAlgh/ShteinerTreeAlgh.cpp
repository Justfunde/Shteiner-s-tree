#include <QtMath>
#include <QDebug>

#include "Include/ShteinerTreeAlgh.hpp"

inline int area (const QPoint& a,const QPoint& b, const QPoint& c) {
	return (b.x() - a.x()) * (c.y() - a.y()) - (b.y() - a.y()) * (c.x() - a.x());
}
 
inline bool intersect_1 (int a, int b, int c, int d) {
	if (a > b)  std::swap (a, b);
	if (c > d)  std::swap (c, d);
	return qMax(a,c) <= qMin(b,d);
}
 
bool intersect (const QLine& fst, const QLine& scnd) {

   QPoint a = fst.p1();
   QPoint b = fst.p2();
   QPoint c = scnd.p1();
   QPoint d = scnd.p2();
	return intersect_1 (a.x(), b.x(), c.x(), d.x())
		&& intersect_1 (a.y(), b.y(), c.y(), d.y())
		&& area(a,b,c) * area(a,b,d) <= 0
		&& area(c,d,a) * area(c,d,b) <= 0;
}

int ShteinerTree::AlgProcessor::minminDist( NodeList &VertexList,
   NodePtr Vertex,
   const NodeList &ExceptVerticies)
{
    qint32 minDistance = 100000;
   
   for(NodeList::iterator it = VertexList.begin(); it != VertexList.end();it++)
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
      if(currDistance <= minDistance && 0 != currDistance) 
      {
          minDistance = currDistance;
      }
   }
   //qDebug() << retVal;
   return minDistance;
}

NodeList::iterator 
ShteinerTree::AlgProcessor::FindByVertex(
   NodeList &VertexList,
   NodePtr Vertex)
{
   for(NodeList::iterator it = VertexList.begin();it != VertexList.end(); it++)
   {
      if(**it == *Vertex) { return it;}
   }
   return VertexList.end();
}

std::shared_ptr<GraphModel> 
ShteinerTree::AlgProcessor::Process()
{
   if(nullptr == Model) { return nullptr;}

   NodeList resultNodeList;


   NodeList nodeList = Model->GetNodes();
   NodeList::iterator currentIter = nodeList.begin();
   NodeList exceptNodes;
   bool isOk = true;
   uint32_t i = 0;
   while(!nodeList.empty()|| nodeList.size() != 1)
   {
      i++;
      if(nodeList.size() == 1) 
      { break;}
      if(nodeList.size() == 2)
      {
         NodePtr first = *nodeList.begin();
         NodePtr second = *std::next(nodeList.begin());
         auto form = CreateLform(first,second);
         NodePtr res = Node::CreateNode("",form.first.first.p2());
         
         first->AddLink(res);
         res->AddLink(second);

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

      qDebug() << secondNode->GetIndicies();
      qDebug() << thirdNode->GetIndicies();

      std::pair<LForm,LForm> firstForms = CreateLform(currNode,secondNode);
      std::pair<LForm,LForm> secondForms = CreateLform(secondNode, thirdNode);
      
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
      //nodeList.erase(FindByVertex(nodeList,secondNode));
      
      //if(minminDist(nodeList,resVertex,exceptNodes) < minminDist(nodeList,secondNode,exceptNodes))
      //{
      //  // nodeList.erase(FindByVertex(nodeList,secondNode));
      //  // currentIter =FindByVertex (resultNodeList,resVertex);
      //}
      //else {
         currentIter = FindByVertex(nodeList,secondNode); 
      
      qDebug() << (*currentIter)->GetIndicies();
      //if(i == 2) { break;}
   }

   std::shared_ptr<GraphModel> resultModel(new GraphModel);
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


inline
NodeList::iterator
ShteinerTree::AlgProcessor::FindMinManhattanDistance(
   NodeList &VertexList,
   NodePtr Vertex,
   const NodeList &ExceptVerticies)
{
   qint32 minDistance = 100000;
   NodeList::iterator retVal = VertexList.begin();
   
   for(NodeList::iterator it = VertexList.begin(); it != VertexList.end();it++)
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
   //qDebug() << retVal;
   return retVal;
}


std::pair<LForm,LForm>
ShteinerTree::AlgProcessor::CreateLform(
   NodePtr Fst,
   NodePtr Scnd)
{
   std::pair<LForm,LForm> retVal;
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

   if(intersect(Fst.first,Scnd.first)) { return true;}
   if(intersect(Fst.first,Scnd.second)) { return true;}

   if(intersect(Fst.second,Scnd.first)) { return true;}
   if(intersect(Fst.second,Scnd.second)) { return true;}

   return false;

}


NodePtr
ShteinerTree::AlgProcessor::GetResultVertex(
  std::pair<LForm,LForm> Fst,
  std::pair<LForm,LForm> Scnd)
{
   if(IsLFormIntersected(Fst.first,Scnd.first)) { return Node::CreateNode("",Fst.first.first.p2());}
   if(IsLFormIntersected(Fst.first,Scnd.second)) { return Node::CreateNode("",Fst.first.first.p2());}

   if(IsLFormIntersected(Fst.second,Scnd.first)) { return Node::CreateNode("",Fst.second.first.p2());}
   if(IsLFormIntersected(Fst.second,Scnd.second)) { return Node::CreateNode("",Fst.second.first.p2());}

   return nullptr;
}


