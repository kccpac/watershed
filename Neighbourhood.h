class Neighbourhood 
{
	public:
		Neighbourhood();		
		~Neighbourhood() ;
        static Neighbourhood *  createInstance(Point *coors, int neigbhourSize, int pitch);
		//int getNeighbourPosition(int which);
        Point getNeighbourPosition(int which);
		int getSize();

	private:
        Neighbourhood(Point *coors, int neigbhourSize, int pitch);
		int mTotalSize;
		int mPitch;
		Point *mCoors;
};
