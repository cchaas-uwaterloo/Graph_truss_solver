/*
 * Joint.cpp
 *
 *  Created on: Mar 19, 2018
 *      Author: camer
 */

#include "Joint.hpp"
#include "Member.hpp"
#include <cmath>
#include <stdlib.h>
#include <iostream>

using namespace std;

double angleHorizontal(Point point1,Point point2) {
	double distx = fabs(point1.x-point2.x);
	double disty = fabs(point1.y-point2.y);
	double distTotal = sqrt(distx*distx+disty*disty);
	double angle = asin(disty/distTotal);
	return fabs(angle);
}

Joint::Joint(Point* point) {
	point_ = *point;
	point_Pointer_= point;
	for (int i = 0; i<8; i++){
		members[i] = new Member[8];
	}
	ext_Y_f = 0;
	ext_X_f = 0;
	used = 0;
	solved = false;
	supported = false;
}

void Joint::addMember(Member* member) {
	members[used] = member;
	used++;
}

void Joint::addExt_f(double fx,double fy) {
	ext_Y_f = fy;
	ext_X_f = fx;
}

void Joint::addSupported() {
	supported = true;
}

void Joint::solveJoint () {
	//the solved part of each component of the forces
	double cX = 0, cY = 0, f1_X_coeff = 0, f1_Y_coeff = 0, f2_X_coeff = 0, f2_Y_coeff = 0;
	int unknown_num = 0, unknown1 = 0, unknown2 = 0;
	//in x direction:
	for (int i=0; i<used; i++)
	{
		if(members[i]->solved_==true){
			if (members[i]->TorC == T){
				if (members[i]->getOtherPoint(point_).x > point_.x)
					cX+=(members[i]->force*cos(angleHorizontal(members[i]->getOtherPoint(point_),point_)));
				else
					cX-=(members[i]->force*cos(angleHorizontal(members[i]->getOtherPoint(point_),point_)));
				if (members[i]->getOtherPoint(point_).y > point_.y)
					cY+=(members[i]->force*sin(angleHorizontal(members[i]->getOtherPoint(point_),point_)));
				else
					cY-=(members[i]->force*sin(angleHorizontal(members[i]->getOtherPoint(point_),point_)));
			}
			else {
				if (members[i]->getOtherPoint(point_).x < point_.x)
					cX+=(members[i]->force*cos(angleHorizontal(members[i]->getOtherPoint(point_),point_)));
				else
					cX-=(members[i]->force*cos(angleHorizontal(members[i]->getOtherPoint(point_),point_)));
				if (members[i]->getOtherPoint(point_).y < point_.y)
					cY+=(members[i]->force*sin(angleHorizontal(members[i]->getOtherPoint(point_),point_)));
				else
					cY-=(members[i]->force*sin(angleHorizontal(members[i]->getOtherPoint(point_),point_)));
			}
		}
		else {
			if (unknown_num == 0){
				if (members[i]->getOtherPoint(point_).x > point_.x)
					f1_X_coeff = cos(angleHorizontal(members[i]->getOtherPoint(point_),point_));
				else
					f1_X_coeff = -1*cos(angleHorizontal(members[i]->getOtherPoint(point_),point_));
				if (members[i]->getOtherPoint(point_).y > point_.y)
					f1_Y_coeff = sin(angleHorizontal(members[i]->getOtherPoint(point_),point_));
				else
					f1_Y_coeff = -1*sin(angleHorizontal(members[i]->getOtherPoint(point_),point_));
				unknown1 = i;
				unknown_num++;
			}
			else{
				if (members[i]->getOtherPoint(point_).x > point_.x)
					f2_X_coeff = cos(angleHorizontal(members[i]->getOtherPoint(point_),point_));
				else
					f2_X_coeff = -1*cos(angleHorizontal(members[i]->getOtherPoint(point_),point_));
				if (members[i]->getOtherPoint(point_).y > point_.y)
					f2_Y_coeff = sin(angleHorizontal(members[i]->getOtherPoint(point_),point_));
				else
					f2_Y_coeff = -1*sin(angleHorizontal(members[i]->getOtherPoint(point_),point_));
				unknown2 = i;
			}
		}
	}

	double f1 = 0;
	double f2 = 0;


	if (unknown_num==0)
		return;

	//cout << "ext x f = " << ext_X_f << endl;
	//cout << "ext y f = " << ext_Y_f << endl;


	cY = -cY - ext_Y_f;
	cX = -cX - ext_X_f;

	//cout << " cX = " << cX << " cY = " << cY << endl;

	if (f2_Y_coeff==0 && f2_X_coeff==0) {
		if (f1_X_coeff>0.000001)
			f1=cX/f1_X_coeff;
		else
			f1 =cY/f1_Y_coeff;
	}

	else {
		double determinant = (f1_X_coeff*f2_Y_coeff - f1_Y_coeff*f2_X_coeff);
		f1 = (cX*f2_Y_coeff - f2_X_coeff*cY)/determinant;
		f2 = (f1_X_coeff*cY - cX*f1_Y_coeff)/determinant;
	}

	/*cout << "f1_X_coeff = " << f1_X_coeff << endl;
	cout << "f1_Y_coeff = " << f1_Y_coeff << endl;
	cout << "f2_X_coeff = " << f2_X_coeff << endl;
	cout << "f2_Y_coeff = " << f2_Y_coeff << endl;

	cout << "f1 = " << f1 << endl;
	cout << "f2 = " << f2 << endl;*/
	members[unknown1]->force = abs(f1);
	members[unknown1]->solved_ = true;
	cout << members[unknown1]->name_ << " has f: "<<members[unknown1]->force << endl;

	if (f1<0)
		members[unknown1]->TorC = C;
	else
		members[unknown1]->TorC = T;

	if (unknown2>unknown1) {
		members[unknown2]->force = abs(f2);
		cout << members[unknown2]->name_ << " has f: "<<members[unknown2]->force << endl;
		members[unknown2]->solved_ = true;
		if (f2<0)
			members[unknown2]->TorC = C;
		else
			members[unknown2]->TorC = T;
	}

	cout << "Joint solved"  << endl;

	solved = true;

	return;

}

