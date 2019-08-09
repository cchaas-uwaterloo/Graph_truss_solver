/*
 * Member.hpp
 *
 *  Created on: Mar 19, 2018
 *      Author: camer
 */

#include "Point.hpp"
#ifndef MEMBER_HPP_
#define MEMBER_HPP_
#include <string>

#define T (true)
#define C (false)


class Member
{
public:

	Member(Point* point1, Point* point2, std::string name);
	Member();

	Point point1_;
	Point point2_;
	std::string name_;
	double force;
	bool solved_;
	bool TorC;

	Point getOtherPoint(Point point);
};


#endif /* MEMBER_HPP_ */
