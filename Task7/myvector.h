#pragma once

#include <sstream>
#include <stdexcept>
#include <iostream>
#include <math.h>

/// \brief Mixin for calculating the length (euclidian norm / distance) of a vector
// BONUS: Implement a mixin that calculates the length of a vector.
// Change the vector template to include this mixin.


/// \brief Template class for (math) vectors of variable length and type.
/// Works with all basic number types.
template<unsigned int Size, typename Element = float>
class Vector
{
public:

	// As always use const wherever meaningful!
	// This time you have to think about meaningful function signatures yourself.
	// However, the given documentation should make it clearly what these signatures should look like.
	// If your signature does not work with the given test-code but you're absolutely sure
	// that your signature fits the requirements, just alter the test-code accordingly! ;)


	/// Constructor that initializes all elements with zero.
    Vector(){
        for(unsigned int i = 0; i < Size; i++)
            elements[i] = 0;
    }
	/// Constructor that copies the vector
    Vector(const Vector<Size, Element>& o){
        for(unsigned int i = 0; i < Size; i++)
            elements[i] = o.elements[i];
    }
    
	/// Constructor that copies a vector of an arbitrary type with the same size.
	/// The type must be convertible by a static_cast to Element.
	template <typename oElement>
	Vector(const Vector<Size, oElement>& o){
        for(unsigned int i = 0; i < Size; i++)
            elements[i] = static_cast<Element>(o.elements[i]);
    }

	/// \brief Constructor that initializes the vector from a string.
	/// The string should contain values, separated by spaces. Uses stringstream for parsing.
	/// Will set all other elements to zero.
	Vector(const std::string& s){
        std::stringstream stream(s);
        Element t;
        for(unsigned int i = 0; i < Size; i++)
            elements[i] = stream >> t ? t : 0;
	}

	/// \brief Returns a string representation of the vector.
	// Todo: Implement a casting operator overload to std::string.
    operator std::string() const {
        std::string s;
        for(unsigned int i = 0; i < Size; i++)
            s.append(std::to_string(elements[i]) + " ");
        return s;
    }
    
	/// \brief Read access to an element.
	/// Checks for errors in debug mode - perform an error report of your choice
    const Element& operator[](const unsigned int i) const{
        #ifdef DEBUG
        if(i < 0 || i >= Size)
            throw std::invalid_argument("invalid access index.");
        #endif
        return elements[i];
    }
    
	/// \brief Write access to an element.
	/// Checks for errors in debug mode - perform an error report of your choice
    Element& operator[](const unsigned int i) {
        #ifdef DEBUG
        if(i < 0 || i >= Size)
            throw std::invalid_argument("invalid access index.");
        #endif
        return elements[i];
    }

	/// \brief Adds to vectors of the same size and type element-wise.
	Vector<Size, Element>& operator+(const Vector<Size, Element>& o){
	    Vector<Size, Element>* val = new Vector();
	    for(unsigned int i = 0; i < Size; i++)
	        val->elements[i] = elements[i] + o.elements[i];
        return *val;
	}


	/// \brief Simple template programming trick to make size accessible from outside.
	enum MetaInfo
	{
		SIZE = Size
	};

protected:
	/// Intern data representation.
	Element elements[Size];
};

template <typename Base>
class EuclideanVector : public Base {
public:
    double length () const {
        double sum = 0;
        for(unsigned int i = 0; i < this->SIZE; i++)
            sum += pow(this->elements[i], 2);
        return sqrt(sum);
    }
};
