#include <iostream>
#include "HoodPoint.h"
#include <string>

HoodPoint::HoodPoint()
{
   posX = posY = 0xFFFF;
   direction = std::string();
}

HoodPoint::HoodPoint (int x, int y): HoodPoint()
{  
   init(x, y);
}

HoodPoint::HoodPoint(int x, int y, std::string dir) : HoodPoint(x, y)
{
   direction = std::string(dir);
}

void HoodPoint::init(int x, int y)
{
   posX = x;
   posY = y;
}

int  HoodPoint::getX() { return posX;}
int  HoodPoint::getY() { return posY;}

std::string HoodPoint::getDirection()
{ 
   return direction;
}

int HoodPoint::getIntDirection()
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

 HoodPoint HoodPoint::getDirPoint(int direction)
 {
     HoodPoint pt;
     switch(direction)
     {
         case 1:
             pt = HoodPoint(0, 1, "Top");
             break;
         case 2: 
             pt = HoodPoint(0, -1, "Bottom");
             break;
          case 3: 
             pt = HoodPoint(-1, 0, "Left");
              break;
          case 4: 
             pt = HoodPoint(1, 0, "Right");
              break;
          case 5: 
             pt = HoodPoint(-1, -1, "Bottom_Left");
              break;
          case 6: 
             pt = HoodPoint(1, -1, "Bottom_Right");
              break;
          case 7: 
             pt = HoodPoint(1,1, "Top_Right");
              break;
          case 8: 
             pt = HoodPoint(-1, 1, "Top_Left");
              break;
         default:
             pt = HoodPoint();
             break;
     }
     return pt;
 }
