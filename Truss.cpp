/*
 * SolveTruss.cpp
 *
 *  Created on: May 29, 2018
 *      Author: camer
 */

#include "Truss.hpp"
#include "CircularQueue.hpp"

//never used - for form's sake
Truss::Truss()
{
	for (int i = 0; i < 32; i++)
		joints_[i] = nullptr;

	used = 0;
}

void Truss::addJoint(Joint *joint) {
	joints_[used] = joint;
	cout << "Joint added at " << joints_[used]->point_.x << " " <<  joints_[used]->point_.y << endl;
	used ++; //will have to use used-1 to refer to all the joints in the truss
}

bool Truss::allSolved() {
	for (int i=0; i<used-1;i++) {
		if (joints_[i]->solved!=true)
			return false;
	}
	return true;
}

bool Truss::canSolve(Joint *joint) {

	cout << "cansolve called  ";

	int unsolved  = 0;
	for (int i=0; i < joint->used-1; i++) {
		if (joint->members[i]->solved_ == false)
			unsolved ++;
		cout << "Unsolved : " << unsolved;
	}
	if (unsolved < 3)
		return true;
	return false;
}

Joint* Truss::getConnectedJoint(Member *member,Joint *currentJoint) {

	Point other = member->getOtherPoint(currentJoint->point_);
	cout << "other point = x:" << other.x << " y:" << other.y << endl;
	for (int i=0; i < used; i++) //searches through list of all joints
	{
		if (other.x == joints_[i]->point_.x && other.y == joints_[i]->point_.y)
		{
			cout << "found connected joint" << endl;
			return joints_[i];
		}
	}
	cout << "failed to find connected joint" << endl;
	return nullptr;
}

/*
 * Uses BFT to solve all the joints (nodes) in the truss graph
 * Could just loop through and solve the ones that it can until they are all solved but this would be the lame
 */
bool Truss::Solve()
{
	Joint * currentJoint = nullptr;
	Joint * currentJoint2 = nullptr;

	if (used == 0)
		return false;

	//load a supported joint into the process queue first
	for (int i=0; i<used-1;i++)
	{
		if (joints_[i]->supported == true){
			processQueue.enqueue(joints_[i]);
			cout << "supported enqueue success." << endl;
		}

	}


	//solve each joint like a boWWWWWWWsse
	while (allSolved() == false) {

		cout << endl << endl << "NEW JOINT" <<endl;

		cout << "here";

		currentJoint = processQueue.dequeue();

		if (currentJoint != nullptr)
		{
			if (canSolve(currentJoint) == true)
			{
				currentJoint->solveJoint();
				cout << "Truss has solved a Joint " << endl;

				//enqueue all connected unsolved Joints
				cout << endl << "Enqueuing..." << endl << endl;

				for (int i = 0; i < currentJoint->used; i++)
				{
					cout << "Enqueue loop ran " << i << endl;
					if (getConnectedJoint(currentJoint->members[i],currentJoint)->solved == false)
					{
						processQueue.enqueue(getConnectedJoint(currentJoint->members[i],currentJoint));
						cout << "connected Joint enqueued " << i  << endl;
					}

				}
			}
			else
			{
				unsolvedQueue.enqueue(currentJoint);
				cout << endl <<  "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!enqueued in unsolved queue!!!!!!!!!!!!" << endl;
			}

			cout << "test" << endl;
		}
		else
			cout << endl << "process queue empty." << endl;

		cout << "Process Enqueue done. " << endl << endl;

		currentJoint2 = unsolvedQueue.peek();
		if (currentJoint2 != nullptr)
		{
			cout << "checked Unsolved Queue." << endl;
			if (canSolve(currentJoint2) == true)
			{
				cout << "here." << endl;
				currentJoint2->solveJoint();
				Joint * holder = unsolvedQueue.dequeue();
				cout << "Truss has solved an unsolved Joint." << endl;

				//enqueue all connected unsolved joints
				cout << endl << "Enqueuing..." << endl << endl;

				for (int i = 0; i < currentJoint2->used-1; i++)
				{
					cout << "Enqueue loop ran " << i << endl;
					if (getConnectedJoint(currentJoint2->members[i],currentJoint2)->solved == false)
					{
						processQueue.enqueue(getConnectedJoint(currentJoint2->members[i],currentJoint2));
						cout << "connected Joint enqueued " << i  << endl;
					}
				}
			}
			cout << "got here." << endl;

		}
	}

	cout << "all solved!!!!!!" << endl;

	if (allSolved() == true)
		return true;
	else return false;

}

/*
 * loops through the joints in the truss solving where possible until all joints are solved
 * simpler back-up to primary solver
 */
bool Truss::SolveAlt()
{
	while (allSolved() == false)
	{
		for (int k = 0; k < used-1; k++)
		{
			cout << k << endl;
			Joint * currentJoint = joints_[k];
			if (currentJoint->solved == false && canSolve(currentJoint)) {
				currentJoint->solveJoint();
				cout << "Joint Solved " << endl;
			}
		}
	}
	if (allSolved() == true)
		return true;
	else return false;
	return allSolved();
}
