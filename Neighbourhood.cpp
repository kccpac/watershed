#include "Point.h"
#include "Neighbourhood.h"

Neighbourhood::Neighbourhood(){}

Neighbourhood::Neighbourhood(Point *coors, int neigbhourSize, int pitch)
{
	mTotalSize =  (neigbhourSize > 0)  ? neigbhourSize: 0;
	mCoors =(Point*) malloc (mTotalSize*sizeof(Point));
	for (int i=0; i<mTotalSize; i++)
	{
		mCoors[i] = Point(coors[i].getX(), coors[i].getY(), coors[i].getDirection());
	}
	mPitch = pitch;
}

Neighbourhood::~Neighbourhood() 
{
	if (mCoors) {
       // delete mCoors;
		free(mCoors);
    }
}

Neighbourhood* Neighbourhood::createInstance(Point *coors, int neigbhourSize, int pitch)
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

Point Neighbourhood::getNeighbourPosition(int which)
{
    Point pt;//Point() 
	if (which > mTotalSize || which < 0) 
		return pt;
	return	mCoors[which];
}

int Neighbourhood::getSize()
{
	return mTotalSize;
}

