#ifndef __SHTEINER_TREE_ALGH_H__
#define __SHTEINER_TREE_ALGH_H__

#include "Include/GraphModel.hpp"

#include <utility>
#include <QLine>

using LForm = std::pair<QLine,QLine>;
using LFormes = std::pair<LForm, LForm>;


namespace ShteinerTree
{
   class AlgProcessor
   {
      private:
      GraphModelPtr Model;

      public:
      void SetModel(GraphModelPtr Model) { this->Model = Model;}
      GraphModelPtr Process();

      private:

      inline qint32 CalcManhattanDistance(NodePtr Fst, NodePtr Scnd);
      qint32 CalcMinManhattanDist( const NodeList &VertexList, NodePtr Vertex, const NodeList &ExceptVerticies);

      NodeList::const_iterator FindMinManhattanDistance(const NodeList &VertexList, NodePtr Vertex, const NodeList &ExceptVerticies);
      NodeList::const_iterator FindByVertex(const NodeList &VertexList,NodePtr Vertex);

      
      //LForm Parse
      NodePtr GetResultVertex( const LFormes& First,const LFormes& Second);
      LFormes CreateLform(NodePtr Fst, NodePtr Scnd);
      bool IsLFormIntersected(const LForm& Fst, const LForm& Scnd);

      //point parse
      inline bool IsIntersected (const QLine& Fst, const QLine& Scnd);
      inline bool IsPointsIntersected (qint32 a, qint32 b, qint32 c, qint32 d);
      inline qint32 CalcTriangleArea (const QPoint& a, const QPoint& b, const QPoint& c);

   };


}

#endif //!__SHTEINER_TREE_ALGH_H__
