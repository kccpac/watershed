#include "HoodPoint.h"

class Neighbourhood 
{
	public:
		Neighbourhood();		
		~Neighbourhood() ;
        static Neighbourhood *  createInstance(HoodPoint *coors, int neigbhourSize, int pitch);
		//int getNeighbourPosition(int which);
        HoodPoint getNeighbourPosition(int which);
		int getSize();

	private:
        Neighbourhood(HoodPoint *coors, int neigbhourSize, int pitch);
		int mTotalSize;
		int mPitch;
		HoodPoint *mCoors;
};
