#ifndef __SHTEINER_TREE_ALGH_H__
#define __SHTEINER_TREE_ALGH_H__

#include "Include/GraphModel.hpp"
#include <utility>
#include <QLine>

using LForm = std::pair<QLine,QLine>;


namespace ShteinerTree
{
      class AlgProcessor
   {
      private:
      std::shared_ptr<GraphModel> Model;

      public:
      void SetModel(std::shared_ptr<GraphModel> Model) { this->Model = Model;}
      std::shared_ptr<GraphModel> Process();

      private:

      inline qint32 CalcManhattanDistance(NodePtr Fst, NodePtr Scnd);
      inline NodeList::iterator FindMinManhattanDistance(NodeList &VertexList,NodePtr Vertex, const NodeList &ExceptVerticies);
      NodeList::iterator FindByVertex(NodeList &VertexList,NodePtr Vertex);


      NodePtr GetResultVertex( std::pair<LForm,LForm> First,
                               std::pair<LForm,LForm> Second);


      std::pair<LForm,LForm> CreateLform(NodePtr Fst, NodePtr Scnd);
      bool IsLFormIntersected(const LForm &Fst, const LForm &Scnd);
      int minminDist( NodeList &VertexList,
   NodePtr Vertex,
   const NodeList &ExceptVerticies);

   };


}

#endif //!__SHTEINER_TREE_ALGH_H__
