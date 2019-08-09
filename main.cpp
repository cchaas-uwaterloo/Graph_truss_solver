/*
 * main.cpp
 *
 *  Created on: Mar 19, 2018
 *      Author: camer
 */

#include "Point.hpp"
#include "Joint.hpp"
#include "Member.hpp"
#include "Truss.hpp"
#include <cmath>
#include <stdlib.h>
#include <iostream>

using namespace std;

void hardAdd();

int main () {

	Point * point1 = new Point(0,0);
	Point * point2 = new Point(0.5,0);
	Point * point3 = new Point(0.5,1);
	Point * point4 = new Point(2,2.1);
	Point * point5 = new Point(5,2.1);
	Point * point6 = new Point(3.5,0);
	Point * point7 = new Point(6.5,0);
	Point * point8 = new Point(8,2.1);
	Point * point9 = new Point(9.5,0);
	Point * point10 = new Point(11,2.1);
	Point * point11 = new Point(12.5,0);
	Point * point12 = new Point(12.5,1);
	Point * point13 = new Point(13,0);

	///////////////////////////////////////////////////////////add names to Joints for debugging graph traversal algorithm//////////////////

	Joint * joint1 = new Joint(point1);
	Joint * joint2 = new Joint(point2);
	Joint * joint3 = new Joint(point3);
	Joint * joint4 = new Joint(point4);
	Joint * joint5 = new Joint(point5);
	Joint * joint6 = new Joint(point6);
	Joint * joint7 = new Joint(point7);
	Joint * joint8 = new Joint(point8);
	Joint * joint9 = new Joint(point9);
	Joint * joint10 = new Joint(point10);
	Joint * joint11 = new Joint(point11);
	Joint * joint12 = new Joint(point12);
	Joint * joint13 = new Joint(point13);




	Member* member1 = new Member(point1,point2,"m1"); //don't need to specify not solved in data constructor
	Member* member2 = new Member(point2,point3,"m2");
	Member* member3 = new Member(point3,point1,"m3");
	Member* member4 = new Member(point2,point4,"m4");
	Member* member5 = new Member(point3,point4,"m5");
	Member* member6 = new Member(point2,point6,"m6");
	Member* member7 = new Member(point4,point6,"m7");
	Member* member8 = new Member(point4,point5,"m8");
	Member* member9 = new Member(point5,point6,"m9");
	Member* member10 = new Member(point7,point6,"m10");
	Member* member11 = new Member(point5,point7,"m11");
	Member* member12 = new Member(point5,point8,"m12");
	Member* member13 = new Member(point7,point8,"m13");
	Member* member14 = new Member(point7,point9,"m14");
	Member* member15 = new Member(point8,point9,"m15");
	Member* member16 = new Member(point8,point10,"m16");
	Member* member17 = new Member(point9,point10,"m17");
	Member* member18 = new Member(point9,point11,"m18");
	Member* member19 = new Member(point10,point11,"m19");
	Member* member20 = new Member(point10,point12,"m20");
	Member* member21 = new Member(point12,point11,"m21");
	Member* member22 = new Member(point11,point13,"m22");
	Member* member23 = new Member(point12,point13,"m23");


	joint1->addMember(member1);
	joint1->addMember(member3);

	joint2->addMember(member1);
	joint2->addMember(member2);
	joint2->addMember(member4);
	joint2->addMember(member6);

	joint3->addMember(member2);
	joint3->addMember(member3);
	joint3->addMember(member5);

	joint4->addMember(member4);
	joint4->addMember(member5);
	joint4->addMember(member7);
	joint4->addMember(member8);

	joint5->addMember(member8);
	joint5->addMember(member9);
	joint5->addMember(member11);
	joint5->addMember(member12);

	joint6->addMember(member6);
	joint6->addMember(member7);
	joint6->addMember(member9);
	joint6->addMember(member10);

	joint7->addMember(member10);
	joint7->addMember(member11);
	joint7->addMember(member13);
	joint7->addMember(member14);

	joint8->addMember(member12);
	joint8->addMember(member13);
	joint8->addMember(member15);
	joint8->addMember(member16);

	joint9->addMember(member14);
	joint9->addMember(member15);
	joint9->addMember(member17);
	joint9->addMember(member18);

	joint10->addMember(member16);
	joint10->addMember(member17);
	joint10->addMember(member19);
	joint10->addMember(member20);

	joint11->addMember(member18);
	joint11->addMember(member19);
	joint11->addMember(member21);
	joint11->addMember(member22);

	joint12->addMember(member20);
	joint12->addMember(member21);
	joint12->addMember(member23);

	joint13->addMember(member22);
	joint13->addMember(member23);


	joint1->addExt_f(0,4.5);
	joint13->addExt_f(0,4.5);
	joint5->addExt_f(0,-3);
	joint7->addExt_f(0,-3);
	joint8->addExt_f(0,-3);

	joint1->addSupported();
	joint13->addSupported();

	Truss truss1;
	truss1.addJoint(joint1);
	truss1.addJoint(joint2);
	truss1.addJoint(joint3);
	truss1.addJoint(joint4);
	truss1.addJoint(joint5);
	truss1.addJoint(joint6);
	truss1.addJoint(joint7);
	truss1.addJoint(joint8);
	truss1.addJoint(joint9);
	truss1.addJoint(joint10);
	truss1.addJoint(joint11);
	truss1.addJoint(joint12);
	truss1.addJoint(joint13);


	/*joint1->solveJoint();
	joint3->solveJoint();
	joint2->solveJoint();
	joint4->solveJoint();
	joint6->solveJoint();
	joint5->solveJoint();
	joint7->solveJoint();
	joint8->solveJoint();
	joint9->solveJoint();
	joint10->solveJoint();
	joint11->solveJoint();
	joint12->solveJoint();
	joint13->solveJoint();*/


	//uses breadth first traversal to "intelligently" (LOL) solve the truss from one support to another
	bool solved = truss1.Solve();
	cout << "solved test" << solved << endl;

	cout << "member 1: "<< member1->force << " "<< (member1->TorC ? "Tension":"Compression") << endl;
	cout << "member 2: "<< member2->force << " "<< (member2->TorC ? "Tension":"Compression") << endl;
	cout << "member 3: "<< member3->force << " "<< (member3->TorC ? "Tension":"Compression") << endl;
	cout << "member 4: "<< member4->force << " "<< (member4->TorC ? "Tension":"Compression") << endl;
	cout << "member 5: "<< member5->force << " "<< (member5->TorC ? "Tension":"Compression") << endl;
	cout << "member 6: "<< member6->force << " "<< (member6->TorC ? "Tension":"Compression") << endl;
	cout << "member 7: "<< member7->force << " "<< (member7->TorC ? "Tension":"Compression") << endl;
	cout << "member 8: "<< member8->force << " "<< (member8->TorC ? "Tension":"Compression") << endl;
	cout << "member 9: "<< member9->force << " "<< (member9->TorC ? "Tension":"Compression") << endl;
	cout << "member 10: "<< member10->force << " "<< (member10->TorC ? "Tension":"Compression") << endl;
	cout << "member 11: "<< member11->force << " "<< (member11->TorC ? "Tension":"Compression") << endl;
	cout << "member 12: "<< member12->force << " "<< (member12->TorC ? "Tension":"Compression") << endl;
	cout << "member 13: "<< member13->force << " "<< (member13->TorC ? "Tension":"Compression") << endl;
	cout << "member 14: "<< member14->force << " "<< (member14->TorC ? "Tension":"Compression") << endl;
	cout << "member 15: "<< member15->force << " "<< (member15->TorC ? "Tension":"Compression") << endl;
	cout << "member 16: "<< member16->force << " "<< (member16->TorC ? "Tension":"Compression") << endl;
	cout << "member 17: "<< member17->force << " "<< (member17->TorC ? "Tension":"Compression") << endl;
	cout << "member 18: "<< member18->force << " "<< (member18->TorC ? "Tension":"Compression") << endl;
	cout << "member 19: "<< member19->force << " "<< (member19->TorC ? "Tension":"Compression") << endl;
	cout << "member 20: "<< member20->force << " "<< (member20->TorC ? "Tension":"Compression") << endl;
	cout << "member 21: "<< member21->force << " "<< (member21->TorC ? "Tension":"Compression") << endl;
	cout << "member 22: "<< member22->force << " "<< (member22->TorC ? "Tension":"Compression") << endl;
	cout << "member 23: "<< member23->force << " "<< (member23->TorC ? "Tension":"Compression") << endl;

	return 0;
}



