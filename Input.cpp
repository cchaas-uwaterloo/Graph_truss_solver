/*
 * Input.cpp
 *
 *  Created on: Sep 27, 2018
 *      Author: camer
 */

#include "Input.hpp"
#include "Joint.hpp"


Input::Input(){
	cout << "input defined";
}

void Input::addJoint(int x, int y, Truss* truss)
{
	Point * pointAdd = new Point(x,y);
	Joint * jointAdd = new Joint(pointAdd);
	truss->addJoint(jointAdd);
	pointAdd = nullptr;
	jointAdd = nullptr;
	delete pointAdd;
	delete jointAdd;
}

void Input::addMember(int j1_index, int j2_index, string name, Truss* truss)
{

	Member * memberAdd = new Member(truss->joints_[j1_index]->point_Pointer_, truss->joints_[j2_index]->point_Pointer_, name);
	truss->joints_[j1_index]->addMember(memberAdd);
	truss->joints_[j2_index]->addMember(memberAdd);
	memberAdd = nullptr;
	delete memberAdd;
}

void Input::defineSupport(int j_index, double jx, double jy, Truss* truss)
{
	truss->joints_[j_index]->addExt_f(jx,jy);
}

void Input::defineLoad(int j_index, double jx, double jy, Truss* truss)
{
	truss->joints_[j_index]->addExt_f(jx,jy);
}

void Input::outputForces(Truss* truss)
{
	//placeholder for now
}

