#ifndef __SHTEINER_TREE_ALGH_H__
#define __SHTEINER_TREE_ALGH_H__

#include "Include/GraphModel.hpp"
#include <utility>

using LForm = std::pair<std::shared_ptr<Node>,std::shared_ptr<Node>>;


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

      inline qint32 CalcManhattanDistance(std::shared_ptr<Node> Fst, std::shared_ptr<Node> Scnd);
      inline NodeList::iterator FindMinManhattanDistance(NodeList &VertexList,std::shared_ptr<Node> Vertex, std::shared_ptr<Node> ExceptVertex);
      LForm CreateLformVerticies(std::shared_ptr<Node> Fst, std::shared_ptr<Node> Scnd);
      std::shared_ptr<Node> GetResultVertex(const LForm &Fst, const LForm &Scnd);
      NodeList::iterator FindByVertex(NodeList &VertexList,std::shared_ptr<Node> Vertex);
   };
}

#endif //!__SHTEINER_TREE_ALGH_H__
