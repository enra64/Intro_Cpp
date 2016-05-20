#pragma once

// Include is necessary: inheritance cannot be solved with a forward declaration
#include "node.hpp"

/// \brief Binary addition operator
class OpAdd: public Node
{
public:
	/// \brief Must have two defined children -> references are a good choice.
	/// \details You need to COPY the nodes to have an own node*. To do that
	///		you will need to add a clone() function which returns a real copy
	///		of the calling object by a ´Node*´.
	///		Question: Is there an other solution and if not why?
	OpAdd(const Node& lhs, const Node& rhs);

	/// \brief Take ownership of two new children.
	/// \details Both parameters must be valid nodes which are not referenced
	///		elsewhere. The operator is responsible to delete them later.
	OpAdd(Node* lhs, Node* rhs);

	/// \brief Implements the clone operator. TODO: have a look at the
	///		implementation.
	virtual Node* clone() const override;

    ~OpAdd();

    std::string toString() const override;

    int evaluate(const VariableMap *_varMap) const override;

private:
	Node* m_children[2];

	// Still Non-Copyable
	OpAdd(const OpAdd&);
	OpAdd& operator = (const OpAdd&);
};


/// \brief Binary multiplication operator (Ternary MAD????)
class OpMul: public Node
{
public:
	/// \copydoc OpAdd(const Node&, const Node&)
	OpMul(const Node& lhs, const Node& rhs);

	/// \brief Take ownership of two new children.
	/// \details Both parameters must be valid nodes which are not referenced
	///		elsewhere. The operator is responsible to delete them later.
	OpMul(Node* lhs, Node* rhs);

	/// \brief Implements the clone operator. TODO: have a look at the
	///		implementation.
	virtual Node* clone() const override;

    ~OpMul();

    std::string toString() const override;

    int evaluate(const VariableMap *_varMap) const override;

private:
	Node* m_children[2];

	// Still Non-Copyable
	OpMul(const OpMul&);
	OpMul& operator = (const OpMul&);
};


/// \brief Unary - operator
class OpNegate: public Node
{
public:
	/// \copydoc OpAdd(const Node&, const Node&)
	OpNegate(const Node& lhs);

	/// \brief Take ownership of one new children.
	/// \details The Parameters must be a valid node which is not referenced
	///		elsewhere. The operator is responsible to delete it later.
	OpNegate(Node* rhs);

	/// \brief Implements the clone operator. TODO: have a look at the
	///		implementation.
	virtual Node* clone() const override;

    ~OpNegate();

    std::string toString() const override;

    int evaluate(const VariableMap *_varMap) const override;

private:
	Node* m_child;

	// Still Non-Copyable
	OpNegate(const OpNegate&);
	OpNegate& operator = (const OpNegate&);
};
