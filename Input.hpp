/*
 * Input.hpp
 *
 *  Created on: Sep 27, 2018
 *      Author: camer
 */

#ifndef INPUT_HPP_
#define INPUT_HPP_
#include "Joint.hpp"
#include "Truss.hpp"
//#include "Point.cpp"

/*
 * NOTE : IN PROGRESS, NOT INTEGRATED TO MAIN YET
 * Application code should interface with this class and not the others
 * exceptions:
 * defining truss object
 */

class Input {
public :
	Input ();
	void addJoint(int x, int y, Truss* truss);
	void addMember(int j1_index, int j2_index, string name, Truss* truss);

	void defineLoad(int j_index, double jx, double jy, Truss* truss);
	/*
	 * currently need to calculate loads on supports manually
	 * later will add this functionality to defineSupports method
	 */
	void defineSupport(int j_index, double jx, double jy, Truss* truss); // will take index of joint
	//will overload defineSupports later for different number of supports

	void outputForces(Truss*truss);

private :
	//not sure if these are needed, can I just re-use pointers as I hand them off to their parents?
	Point* points_[100];
	Joint* joints_[100];
	Member* members_[100];
};


#endif /* INPUT_HPP_ */
