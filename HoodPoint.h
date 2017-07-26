#include <string>
using namespace std;

class HoodPoint {
   public:   
      HoodPoint();
      ~HoodPoint(){};

      HoodPoint (int x, int y);
      HoodPoint (int x, int y, std::string direction) ;

      int getX();
      int getY();
      std::string getDirection();
      int getIntDirection();
      static HoodPoint getDirPoint(int direction);

   private:
      void init(int x, int y);
      int posX;
      int posY;
      std::string direction;
};
