/*
 * Joint.hpp
 *
 *  Created on: Mar 19, 2018
 *      Author: camer
 */
#include "Point.hpp"
#include "Member.hpp"
#ifndef JOINT_HPP_
#define JOINT_HPP_


class Joint
{
public:
	Joint(Point* point);
	Member* members [8];
	Point point_;
	Point* point_Pointer_;
	int used;
	double ext_Y_f;
	double ext_X_f;
	bool solved;
	bool supported;
	void solveJoint();
	void addMember(Member* member);
	void addSupported();
	void addExt_f(double fx, double fy);
};


#endif /* JOINT_HPP_ */
