#include <cassert> // FOR assert
#include <cmath>
#include <string>
#include <sstream>
using std::stringstream;
using std::string;
using std::stod;
using std::sqrt;
using std::pow;


#include "Point.h"
#include "Exceptions.h"

using namespace Clustering;

namespace Clustering {

	typedef Point * PointPtr;


	const char Point::POINT_VALUE_DELIM = ',';


	// INIT ID HERE
	unsigned int Point::__idGen = 0;



	void Point::rewindIdGen()
	{
		--__idGen;
	}




	Point::Point(unsigned int arg_int, double * arg_double_ptr) : __dim(arg_int), __values(arg_double_ptr)
	{
		if (arg_int == 0)
			throw ZeroDimensionsEx();

	}


	Point::Point(unsigned int arg_int) : __dim(arg_int)
		{
			if (arg_int == 0)
				throw ZeroDimensionsEx();

			// SET ID TO IDGEN
			__id = __idGen++;

			__values = new double[__dim];

			for (int index = 0; index < __dim; index++)
			{
				__values[index] = 0.0;
			}

		}

//		Point::Point(int arg_int = 0, double *arg_ptr_double) {}

		// Big three: cpy ctor, overloaded operator=, dtor
		Point::Point(const Point &arg_Point)
		{
			if (&arg_Point == this)
			{
				// DO NOTHING
			}
			// ELSE DO CONSTRUCTOR
			else if (&arg_Point.__values != NULL)
			{
///*DEBUG*/	std::cout << "ID = " << arg_Point.__id << "    DIM = " << arg_Point.__dim << "\n";
				// SEGFAULT HERE
				__id = arg_Point.__id;
				__dim = arg_Point.__dim;
				__values = new double[arg_Point.getDims()];

				for (int index = 0; index < __dim; index++)
					setValue(index, arg_Point.getValue(index));
			}
			else
			{
				__id = arg_Point.__id;
				__dim = arg_Point.__dim;
			}
		}


		Point &Point::operator=(const Point &arg_Point)
		{
			if (&arg_Point == this)
			{
				return *this;
			}
			else if (this->getDims() != arg_Point.getDims())
			{
				throw DimensionalityMismatchEx(this->getDims(), arg_Point.getDims());
			}
			else
			{
				__id = arg_Point.getId();

				for (int index = 0; index < __dim; ++index)
				{
					this->__values[index] = arg_Point.getValue(index);
				}

				return *this;
			}
		}

		Point::~Point()
		{
			if (__values != NULL)
			{
				delete [] __values;
			}
			__values = NULL;
		}

		// Accessors & mutators
		int Point::getId() const
		{
			return __id;
		}

		unsigned int Point::getDims() const
		{
			return __dim;
		}

		void Point::setValue(unsigned int arg_int, double arg_double)
		{
			if (arg_int >= 0 && arg_int < __dim)
				__values[arg_int] = arg_double;
			else
				throw OutOfBoundsEx(__dim, arg_int);
		}


		double Point::getValue(unsigned int arg_int) const
		{
			if (arg_int >= 0 && arg_int < __dim)
				return __values[arg_int];
			else
				throw OutOfBoundsEx(__dim, arg_int);
		}




		// Overloaded operators

		// Members
		Point &Point::operator*=(double arg_double) // p *= 6; p.operator*=(6);
		{
			// TAKEN FROM LECTURE

			for (int i = 0; i < __dim; i++)
				__values[i] *= arg_double;

			return *this;
		}

	Point &Point::operator/=(double arg_double)
	{
		// TAKEN FROM LECTURE
		// Point &Point::operator/=(double d) { // TODO handle div-by-0 or let runtime handle it

		assert(arg_double != 0);

		for (int i = 0; i < __dim; i++)
			__values[i] /= arg_double;

		return *this;

	}


		const Point Point::operator*(double arg_double) const // prevent (p1 * 2) = p2;
		{
			Point newPoint(*this);
			newPoint *= arg_double;
			return newPoint;
		}

		const Point Point::operator/(double arg_double) const // p3 = p2 / 2;
		{
			Point newPoint(*this);
			newPoint /= arg_double;
			return newPoint;
		}

		double &Point::operator[](unsigned int index)
		{
			if (index >= 0 && index < __dim)
				return __values[index];
			else
				throw OutOfBoundsEx(__dim, index);
		}


		const double &Point::operator[](unsigned int index) const
		{
			if (index >= 0 && index < __dim)
				return __values[index];
			else
				throw OutOfBoundsEx(__dim, index);
		}


	// Friends
		Point &operator+=(Point &arg_Point_left, const Point &arg_Point_right)
		{
//			if (&arg_Point_left == &arg_Point_right)
//				return arg_Point_left *= 2;

			if (arg_Point_left.__dim == arg_Point_right.__dim)
				for (int index = 0; index < arg_Point_left.__dim; ++index)
					arg_Point_left.__values[index] += arg_Point_right.__values[index];
			else throw DimensionalityMismatchEx(arg_Point_left.getDims(), arg_Point_right.getDims());

			return arg_Point_left;
		}


	Point &operator-=(Point &arg_Point_left, const Point &arg_Point_right)
	{
//		if (&arg_Point_left == &arg_Point_right)
//			return arg_Point_left /= 2;

		if (arg_Point_left.__dim == arg_Point_right.__dim)
			for (int index = 0; index < arg_Point_left.__dim; ++index)
				arg_Point_left.__values[index] -= arg_Point_right.__values[index];
		else throw DimensionalityMismatchEx(arg_Point_left.getDims(), arg_Point_right.getDims());

		return arg_Point_left;
	}

		const Point operator+(const Point &arg_Point_left, const Point &arg_Point_right)
		{
			Point newPoint(arg_Point_left);
			return newPoint += arg_Point_right;
		}

		const Point operator-(const Point &arg_Point_left, const Point &arg_Point_right)
		{
			// DO MEMBERWISE LOOP
			Point newPoint(arg_Point_left);
			return newPoint -= arg_Point_right;
		}

		bool operator==(const Point &arg_Point_left, const Point &arg_Point_right)
		{
			bool result = false;

			if (arg_Point_left.getDims() != arg_Point_right.getDims())
				throw DimensionalityMismatchEx(arg_Point_left.getDims(), arg_Point_right.getDims());

			if (arg_Point_left.getId() == arg_Point_right.getId())
			{
				result = true;
				for (unsigned int index = 0; result && index < arg_Point_left.getDims(); ++index)
					if (arg_Point_left.getValue(index) != arg_Point_right.getValue(index))
						result = false;
			}



			return result;
		}

		bool operator!=(const Point &arg_Point_left, const Point &arg_Point_right)
		{
			return (!(arg_Point_left == arg_Point_right));
		}

		bool operator<(const Point &arg_Point_left, const Point &arg_Point_right)
		{
			// Note: One Point is smaller than another iff, for a given
			// dimension position, the value of the first point is less than
			// the value of the second point, and all the values on the left,
			// if any, are all equal. The values on the right don't matter.
			// For example, Point (5.0, 5.0, 4.5, 10.1, 13.4, 151.3) is
			// smaller than (5.0, 5.0, 4.5, 10.1, 13.5, 15.9).
			// Note: Implement operator<, then use it to implement operator>
			// and operator>=. Finally, use operator> to implement operator<=.


			// IF EXACT SAME OBJECTS CAN'T HAVE ONE LESS THAN OTHER
			if (&arg_Point_left == &arg_Point_right)
				return false;

			bool result = false;
			bool isEqual = false;

			if (arg_Point_left.getDims() == arg_Point_right.getDims())
			{

///*DEBUG*/	std::cout << "\nDIM = " << arg_Point_left.getDims() << "\n";

				isEqual = true;
				for (int index = 0; isEqual && index < arg_Point_left.getDims(); ++index)
				{
///*DEBUG*/	std::cout << "arg_Point_left.getValue("<<index<<") = " << arg_Point_left.getValue(index) << "  <  arg_Point_right.getValue(index) = " << arg_Point_right.getValue(index) << "\n";
					if (arg_Point_left.getValue(index) == arg_Point_right.getValue(index))
					{
						// CONTINUE LOOP
						continue;
					}
					else if (arg_Point_left.getValue(index) < arg_Point_right.getValue(index))
					{
						isEqual = false;
						result = true;
					}
					// RESULT IS ALREADY FALSE; RETURN
					else isEqual = false;
				}
			}
			else throw DimensionalityMismatchEx(arg_Point_left.getDims(), arg_Point_right.getDims());

			return result;
		}



		bool operator>(const Point &arg_Point_left, const Point &arg_Point_right)
		{
			return (arg_Point_right < arg_Point_left);
		}


		bool operator<=(const Point &arg_Point_left, const Point &arg_Point_right)
		{
			// CANNOT USE EXISTING == OPERATOR FOR REASON DON'T CARE ABOUT __ID
			// EXACT SAME OBJECTS ARE INHERENTLY EQUAL
			if (&arg_Point_left == &arg_Point_right)
				return true;

			bool result = false;
			bool isEqual = false;

			if (arg_Point_left.getDims() == arg_Point_right.getDims())
			{

///*DEBUG*/	std::cout << "\nDIM = " << arg_Point_left.getDims() << "\n";

				isEqual = true;
				for (int index = 0; isEqual && index < arg_Point_left.getDims(); ++index)
				{
///*DEBUG*/	std::cout << "arg_Point_left.getValue("<<index<<") = " << arg_Point_left.getValue(index) << "  <  arg_Point_right.getValue(index) = " << arg_Point_right.getValue(index) << "\n";
					if (arg_Point_left.getValue(index) == arg_Point_right.getValue(index))
					{
						// CONTINUE LOOP
						continue;
					}
					else if (arg_Point_left.getValue(index) < arg_Point_right.getValue(index))
					{
						isEqual = false;
						result = true;
					}
					// RESULT IS ALREADY FALSE; RETURN
					else isEqual = false;
				}
			}
			else throw DimensionalityMismatchEx(arg_Point_left.getDims(), arg_Point_right.getDims());

			return (result || isEqual);
		}




		bool operator>=(const Point &arg_Point_left, const Point &arg_Point_right)
		{
			return (arg_Point_right <= arg_Point_left);
		}


		std::ostream &operator<<(std::ostream &os, const Point &arg_Point_right)
		{
			int index;

			for (index = 0; index < arg_Point_right.getDims() - 1; ++index)
				os << arg_Point_right.getValue(index) << ", ";

			os << arg_Point_right.getValue(index);

			return os;
		}

		std::istream &operator>>(std::istream &ins, Point &arg_Point_right)
		{



			// MOSLY TAKEN FROM LECTURE
			string line;
			string buffer;
			double dvalue;
			int index = -1;

			while (getline(ins, line))
			{

				stringstream lineStream(line);

				while (getline(lineStream, buffer, Point::POINT_VALUE_DELIM))
				{

					if (++index == arg_Point_right.getDims())
					{
						Point::rewindIdGen();
						throw DimensionalityMismatchEx(index - 1, arg_Point_right.getDims());
					}

					dvalue = stod(buffer);
					arg_Point_right.setValue(index, dvalue);
				}

				if ((index + 1) != arg_Point_right.getDims())
				{
					Point::rewindIdGen();
					throw DimensionalityMismatchEx(index, arg_Point_right.getDims());
				}
			}

			return ins;
		}

}

///*
// * Add a new member function to Point called distanceTo.
// * This member function should accept as an argument a
// * const Point & (a reference to a constant Point), and
// * it should return a double that approximates the
// * distance between the two points. Note that distanceTo
// * is a constant member function.
// */
//
//// PRECOND. Argument to function is a reference to a const
//// Point object.
//// POSTCOND. Function returns double that approximates
//// distance between two points.
//double Point::distanceTo(const Point& otherPoint) const
//{
//	// FORMULA IS: sqrt( ((x2-x1)^2) + ((y2-y1)^2) + ((z2-z1)^2) );
//	// NOTE:  EXPRESSION FOR SQUARE ROOT IS INHERENTLY >= 0
//
//	return std::sqrt(
//			std::pow((x-otherPoint.getX()),2) +
//			std::pow((y-otherPoint.getY()),2) +
//			std::pow((z-otherPoint.getZ()),2)
//	);
//}
//
double Point::distanceTo(const Point& arg_Point) const
{
	// FORMULA IS: sqrt( ((x2-x1)^2) + ... + ((z2-z1)^2) );
	// NOTE:  EXPRESSION FOR SQUARE ROOT IS INHERENTLY >= 0

	double sum = 0.0;

	if (__dim == arg_Point.getDims())
		for (int index = 0; index < __dim; ++index)
			sum += pow(__values[index] - arg_Point.getValue(index), 2);
	else throw DimensionalityMismatchEx(__dim, arg_Point.getDims());

	return sqrt(sum);
}