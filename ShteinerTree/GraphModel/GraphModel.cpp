#include <QFile>
#include <QTextStream>

#include "GraphModel.hpp"





void Node::AddLink(std::shared_ptr<Node> Vertex)
{
   Links.push_back(Vertex);
}


void Node::DeleteLink(std::shared_ptr<Node> Vertex)
{
   const auto foundObj = std::find(Links.begin(), Links.end(), Vertex);
   Links.erase(foundObj);
}


//setters
void Node::SetIndicies(const QPoint &Indicies)
{
   if(Indicies.x() < 10 && Indicies.y() < 10) 
   {
      this->Indicies = Indicies;
   }
}







bool
operator==(
   const Node& First,
   const Node& Second)
{
   if(First.Name != Second.Name) { return false;}
   if(First.Indicies != Second.Indicies) { return false;}
   if(First.Links != Second.Links) { return false;}
   return true;
}


