#include "node.hpp"

std::ostream &operator<<(std::ostream &lhs, const Node &rhs)
{
    lhs << rhs.toString();
    return lhs;
}

Node::~Node(){}
