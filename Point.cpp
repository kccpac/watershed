#include <iostream>
#include "Point.h"
#include <string>

//class Point {
//	protected int ptx;
//	protected int pty;
//    protectedsString direction;
//	Point();

    Point::Point()
    {
        posX = posY = 0xFFFF;
    }
    Point::~Point()
    {
    }

    Point::Point (int x, int y)
    {
        init(x, y);
        direction = std::string();
    }

    Point::Point(int x, int y, std::string dir) 
    {
        init(x, y);
        direction = std::string(dir);
    }

    void Point::init(int x, int y)
    {
        posX = x;
        posY = y;
    }
/*
    Point::Point(Point thatPt)
    {
	    posX = thatPt.posX;
	    posY = thatPt.getY();
        direction = std::string(thatPt.getDirection());
      //  strcpy(this.direction.data, direction.data);
    }
*/
    int  Point::getX() { return posX;}
	int  Point::getY() { return posY;}

    std::string Point::getDirection()
    { 
        return direction;
    }

    int Point::getIntDirection()
    {
        int dir = 0;
       

        if (direction.compare("Top") == 0)
        {    
            dir = 1;
        }
        else if (direction.compare("Bottom") == 0)
        {
            dir = 2;
        }
        else if (direction.compare("Left") == 0)
        {
            dir = 3;
        }
        else if (direction.compare("Right") == 0)
        {
            dir = 4;
        }
        else if (direction.compare("Bottom_Left") == 0)
       {
            dir = 5;
        }
        else if (direction.compare("Bottom_Right") == 0)
        {
            dir = 6;
        }
        else if (direction.compare("Top_Right") == 0)
        {
            dir = 7;
        }
        else if (direction.compare("Top_Left") == 0)
        {
            dir = 8;
        }
         std::cout << "direction = " << direction << "dir = " << dir << "\n";
        return dir;
    }

 Point Point::getDirPoint(int direction)
    {
        Point pt;
       /*
  Point(-1, -1, "Bottom_Left"),
			Point(0, -1, "Bottom"),
			Point(-1, 0, "Left"),
            Point(1, -1, "Bottom_Right"),
			Point(1, 0, "Right"),
            Point(1,1, "Top_Right"),
			Point(0, 1, "Top"),
            Point(-1, 1, "Top_Left")};*/
        switch(direction)
        {
            case 1:
                pt = Point(0, 1, "Top");
                break;
            case 2: 
                pt = Point(0, -1, "Bottom");
                break;
             case 3: 
                pt = Point(-1, 0, "Left");
                 break;
             case 4: 
                pt = Point(1, 0, "Right");
                 break;
             case 5: 
                pt = Point(-1, -1, "Bottom_Left");
                 break;
             case 6: 
                pt = Point(1, -1, "Bottom_Right");
                 break;
             case 7: 
                pt = Point(1,1, "Top_Right");
                 break;
             case 8: 
                pt = Point(-1, 1, "Top_Left");
                 break;
        }
        return pt;
/*
        if (direction.compare("Top") == 0)
        {    
            dir = 1;
        }
        else if (direction.compare("Bottom") == 0)
        {
            dir = 2;
        }
        else if (direction.compare("Left") == 0)
        {
            dir = 3;
        }
        else if (direction.compare("Right") == 0)
        {
            dir = 4;
        }
        else if (direction.compare("Bottom_Left") == 0)
       {
            dir = 5;
        }
        else if (direction.compare("Bottom_Right") == 0)
        {
            dir = 6;
        }
        else if (direction.compare("Top_Right") == 0)
        {
            dir = 7;
        }
        else if (direction.compare("Top_Left") == 0)
        {
            dir = 8;
        }
         std::cout << "direction = " << direction << "dir = " << dir << "\n";*/
        return pt;
    }

/*	public int getX() { return x;}
	public int getY() { return y;}

    public std:string getDirection() { return direction;}*/
//};
