#include "operators.hpp"

#include <cassert>

// ************************************************************************* //
OpAdd::OpAdd(const Node& lhs, const Node& rhs)
{
	m_children[0] = lhs.clone();
	m_children[1] = rhs.clone();
}

OpAdd::OpAdd(Node* lhs, Node* rhs)
{
    m_children[0] = lhs;
    m_children[1] = rhs;
}

Node* OpAdd::clone() const
{
	// Cloning requires a deep copy. Otherwise multiple pointer would address
	// the same memory.
	return new OpAdd(m_children[0]->clone(), m_children[1]->clone());
}

OpAdd::~OpAdd(){
    delete m_children[0];
    delete m_children[1];
}

int OpAdd::evaluate(const VariableMap* _varMap) const {
    int a = m_children[0]->evaluate(_varMap);
    int b = m_children[1]->evaluate(_varMap);
    return a + b;
}

std::string OpAdd::toString() const {
    return "( " + m_children[0]->toString() + " + " + m_children[1]->toString() + ")";
}

// ************************************************************************* //
OpMul::OpMul(const Node& lhs, const Node& rhs)
{
    m_children[0] = lhs.clone();
    m_children[1] = rhs.clone();
}

OpMul::OpMul(Node* lhs, Node* rhs)
{
    m_children[0] = lhs;
    m_children[1] = rhs;
}

Node* OpMul::clone() const
{
	// Cloning requires a deep copy. Otherwise multiple pointer would address
	// the same memory.
	return new OpMul(m_children[0]->clone(), m_children[1]->clone());
}

OpMul::~OpMul(){
    delete m_children[0];
    delete m_children[1];
}

int OpMul::evaluate(const VariableMap* _varMap) const {
    int a = m_children[0]->evaluate(_varMap);
    int b = m_children[1]->evaluate(_varMap);
    return a * b;
}

std::string OpMul::toString() const {
    return "( " + m_children[0]->toString() + " + " + m_children[1]->toString() + ")";
}

// TODO: the other methods


// ************************************************************************* //
OpNegate::OpNegate(const Node& lhs)
{
    m_child = lhs.clone();
}


OpNegate::OpNegate(Node* rhs)
{
    m_child = rhs;
}

Node* OpNegate::clone() const
{
	// Cloning requires a deep copy. Otherwise multiple pointer would address
	// the same memory.
	return new OpNegate(m_child->clone());
}

OpNegate::~OpNegate(){
    delete m_child;
}

int OpNegate::evaluate(const VariableMap* _varMap) const {
    return -m_child->evaluate(_varMap);
}

std::string OpNegate::toString() const {
    return "( -" + m_child->toString() + ")";
}
