#ifndef __SHTEINER_TREE_ALGH_H__
#define __SHTEINER_TREE_ALGH_H__

#include "Include/GraphModel.hpp"
#include <utility>

using LForm = std::pair<NodePtr,NodePtr>;


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
      inline NodeList::iterator FindMinManhattanDistance(NodeList &VertexList,NodePtr Vertex, NodePtr ExceptVertex);
      LForm CreateLformVerticies(NodePtr Fst, NodePtr Scnd);
      NodePtr GetResultVertex(const LForm &Fst, const LForm &Scnd);
      NodeList::iterator FindByVertex(NodeList &VertexList,NodePtr Vertex);
   };
}

#endif //!__SHTEINER_TREE_ALGH_H__
