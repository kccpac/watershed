//#include <std>
#include <string>
using namespace std;

class Point {

public:
	
   
    Point();
   ~Point();

    Point (int x, int y);
	Point (int x, int y, std::string direction) ;
/*	{
        super();
		posX = x;
		posY = y;
        strcpy(this.direction.data, direction.data);
	}
*/
//	Point(Point thatPt);
/*	{
		posX = pt.posX;
		posY = pt.posY;
        strcpy(direction, pt.getDirection());

	}
*/
	int getX();// { return posX;}
	int getY();// { return posY;}
    std::string getDirection();
    int getIntDirection();
    static Point getDirPoint(int direction);

private:

    void init(int x, int y);
	int posX;
	int posY;
    std::string direction;


};
