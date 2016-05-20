#include "valuenode.hpp"


Node* Value::clone() const
{
	// Create a new instance with the same type and data. As you can see we
	// need to know the type ´Value´ that is why we cannot implement it
	// elsewhere.
	return new Value(m_val);
}

int Value::evaluate(const VariableMap* _varMap) const {
    VariableMap::const_iterator valPos = _varMap->find(m_val);
    if(valPos != _varMap->end())
        return valPos->second;
    return std::stoi(m_val);
}

std::string Value::toString() const {
    return m_val;
}

Value::~Value(){

}
