#include <iostream>
#include "Neighbourhood.h"

Neighbourhood::Neighbourhood(){}

Neighbourhood::Neighbourhood(HoodPoint *coors, int neigbhourSize, int pitch):Neighbourhood()
{
	mTotalSize =  (neigbhourSize > 0)  ? neigbhourSize: 0;

	mCoors = new  HoodPoint[mTotalSize];//(mTotalSize*sizeof(HoodPoint));
    std::cout << "init start " << mTotalSize << "\n";
//    memset(mCoors, 0, mTotalSize * sizeof(HoodPoint));
    int i;
	for ( i=0; i<mTotalSize; i++)
	{
    //    std::cout << "pos " << i << " " <<coors[i].getX() << ", " << coors[i].getY() << ", " << coors[i].getDirection() << "\n";
		mCoors[i] = HoodPoint(coors[i].getX(), coors[i].getY(), coors[i].getDirection());
    //    std::cout << "hood id=" << i << "\n";
	}
 // delete  mCoors;
	mPitch = pitch;
}

Neighbourhood::~Neighbourhood() 
{
	//if (mCoors) {
        delete  [] mCoors;
 std::cout << "Neighbourhood::~Neighbourhood \n";
	//	free(mCoors);
   // }
mCoors = NULL;
}

Neighbourhood* Neighbourhood::createInstance(HoodPoint *coors, int neigbhourSize, int pitch)
{
    return new Neighbourhood(coors, neigbhourSize,  pitch);
}

/*
int Neighbourhood::getNeighbourPosition(int which)
{
	if (which > mTotalSize || which < 0) 
		return -1;
	return	mCoors[which].getY()*mPitch+mCoors[which].getX();
}
*/

HoodPoint Neighbourhood::getNeighbourPosition(int which)
{
    HoodPoint pt;//Point() 
	if (which > mTotalSize || which < 0) 
		return pt;
	return	mCoors[which];
}

int Neighbourhood::getSize()
{
	return mTotalSize;
}

