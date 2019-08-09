/*
 * Member.cpp
 *
 *  Created on: Mar 19, 2018
 *      Author: camer
 */

#include "Member.hpp"
#include "Point.hpp"

Member::Member(Point* point1, Point* point2, std::string name) {
	point1_ = *point1;
	point2_ = *point2;
	solved_ = false;
	name_ = name;
	TorC = T;
	force = 0;
}

Member::Member() {
	Point p1(0,0);
	point1_ = p1;
	point2_ = p1;
	solved_ = false;
	name_ = " ";
	TorC = T;
	force = 0;
}

Point Member::getOtherPoint(Point point) {
	if (point1_.x == point.x && point1_.y == point.y)
		return point2_;
	return point1_;
}



