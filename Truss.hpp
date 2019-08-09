/*
 * SolveTruss.hpp
 *
 *  Created on: May 29, 2018
 *      Author: camer
 */

#ifndef TRUSS_HPP_
#define TRUSS_HPP_
#include "Joint.hpp"
#include "CircularQueue.hpp"
#include <iostream>
#include <stdlib.h>

using namespace std;

class Truss
{
public:

	Truss();
	void addJoint(Joint *joint);
	bool Solve();
	bool SolveAlt();
	Joint* joints_ [32]; //needs to be public to be accessed to add ext forces due to loads and supports to individual joints

private:

	CircularQueue processQueue;
	CircularQueue unsolvedQueue;
	int used;
	bool allSolved();
	bool canSolve(Joint*);
	Joint* getConnectedJoint(Member *member,Joint *currentJoint);

};


#endif /* TRUSS_HPP_ */
