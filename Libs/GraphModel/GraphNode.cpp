#include "Include/GraphModel.hpp"

Node::Node(
   const QString &Name,
   const QPoint &Indicies)
   :Indicies(Indicies)
{
   this->Name = Name;
   if(Indicies.x() < 10 && Indicies.y() < 10) 
   {
      this->Indicies = Indicies;
   }
}


void
Node::AddLink(
   NodePtr Vertex)
{
   Links.push_back(Vertex);
}


void
Node::DeleteLink(
   NodePtr Vertex)
{
   const auto foundObj = std::find(Links.begin(), Links.end(), Vertex);
   Links.erase(foundObj);
}


void
Node::SetIndicies(
   const QPoint &Indicies)
{
   if(Indicies.x() < 10 && Indicies.y() < 10) 
   {
      this->Indicies = Indicies;
   }
}


QPoint
Node::GetIndicies() const { return Indicies; }


NodeList
Node::GetLinks() const { return Links; }


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