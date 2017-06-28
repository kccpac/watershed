#include <iostream>
#include <malloc.h>


#include "string.h"
//#include "Point.h"
//#include "Neighbourhood.h"
#include "watershedTransform.h"

#define imageWidth 10

//#define imageWidth 7

using namespace std;

class watershedTest
{
	public:
	 watershedTest();

};

int main()
{
    Point  neigbors[] = {
           // Point(-1, -1, "Bottom_Left"),
			Point(0, -1, "Bottom"),
			Point(-1, 0, "Left"),
        //    Point(1, -1, "Bottom_Right"),
			Point(1, 0, "Right"),
         //   Point(1,1, "Top_Right"),
			Point(0, 1, "Top") // ,
         //   Point(-1, 1, "Top_Left")
            };

	int image [][imageWidth] = 
   {
		{3, 5, 5, 2, 8, 8, 8, 11, 10, 10},
		{5, 5, 11, 11, 8, 11, 11, 8, 10, 10}, 
		{11, 5, 11, 11, 9, 9, 9, 9, 8, 10},
		{11, 11, 11, 7, 7, 7, 7, 9, 9, 8},
		{11, 11, 11, 11, 11, 9, 7, 10, 8, 10},
		{11, 10, 11, 9, 7, 7, 9, 9, 10, 8},
		{11, 10, 11, 9, 11, 9, 10, 10, 8, 10},
		{11, 11, 11, 8, 8, 8, 8, 8, 10, 10},
		{11, 11, 11, 11, 10, 10, 10, 10, 10, 10},
		{10, 10, 10, 10, 10, 10, 10, 10, 10, 10},
		{11, 11, 11, 11, 10, 10, 10, 10, 10, 10},
		{10, 10, 10, 10, 10, 10, 10, 10, 10, 10}
	};
/*
    {
        {20, 20, 20, 20, 20, 20, 20},
        {20, 20, 20, 5, 20, 20, 20},
        {20, 20, 8, 13, 6, 20, 20},
        {20, 9, 14, 16, 13, 7, 20},
        {20, 9, 13, 18, 17, 9, 20},
        {20, 9, 15, 17, 15, 9, 20},
        {20, 20, 9, 15, 9, 20, 20},
        {20, 20, 13, 9, 12, 20, 20},
        {20, 20, 14, 9, 13, 20, 20},
        {20, 20, 15, 9, 12, 20, 20},
        {20, 20, 13, 9, 12, 20, 20},
        {20, 20, 9, 15, 9, 20, 20},
        {20, 9, 15, 17, 15, 9, 20},
        {20, 9, 13, 19, 17, 9, 20},
        {20, 9, 14, 16, 13, 7, 20},
        {20, 20, 8, 13, 6, 20, 20},
        {20, 20, 20, 5, 20, 20, 20},
        {20, 20, 20, 20, 20, 20, 20}
    };
 */  
 //       Point x(0, -1, "Bottom");
	std::cout << "neigbhour: (" << neigbors[2].getX() << ", "  <<  neigbors[2].getY() << ", "  << neigbors[2].getDirection() << ") \n";
    std::cout << "neigbhour size : " << sizeof(neigbors)/sizeof(Point) <<"/n";
	Neighbourhood *hood = Neighbourhood::createInstance(neigbors, sizeof(neigbors)/sizeof(Point), imageWidth);
	std::cout << "pos: " << hood->getNeighbourPosition(2).getX() << " \n";
	//Neigbhourhood hood = new Neigbhourhood(neigbors, 10);
    int imagePitch = ((imageWidth&0x10000)+1) << 4;
    int rows = sizeof(image)/(imageWidth*sizeof(int));
    std::cout << "# Image row: " << rows << " image size = " << sizeof(image) <<  " imagePitch="  << (imageWidth&0x1000) << "\n";
    Point pt = Point::getDirPoint(-1);
    //std::cout << "pt (" << pt.getX() << ", " << pt.getY() << ") \n";
    //int **im = (int **) malloc (rows*sizeof(int *));
  //  exit(1);
    int **im = (int **) new int * [rows];
    for (int i=0; i<rows; i++)
    {
        //im[i] = (int *) malloc ( 8*sizeof(int));
        im[i] = new int [imagePitch];
        std::cout << "im [ " << i << "] =: " << im[i] << "\n"; 
        memcpy(im[i], image[i], imagePitch*sizeof(int));
    }

    std::cout << "# Image row: " << rows << " im size = " << im[1] << ", " << im[0]  << "addr size=" << sizeof(im[1]) << " pitch=" << imagePitch*sizeof(int) <<  " \n";

  //  int pitch = ((8 * imageWidth) / 32 + 1) * 32
    for (int i=0; i<rows; i++)
    {
        int *ptr =(i == 0) ? *im:  *im + i *(imagePitch + (2*sizeof(im[i])/(sizeof(int))));
//         std::cout << "im [ " << i << "] =: " << im[i] << " ptr=" << ptr  << " diff= " << (ptr-im[i]) << "\n"; 
        for (int j=0; j<imageWidth; j++)
        {           
            std::cout << *( ptr+j) << " ";
        }
        std::cout << "\n";
    }

  //  return 0;
    watershedTransform *transform = watershedTransform::createInstance(hood, imageWidth, imagePitch,  rows);
    std::cout << "watershedTransform createInstance done  \n";
    transform->setInput(im);
    transform->computeWTransform();
   // transform->getBasin();

    for (int i=0; i<rows; i++)
    {
        delete im[i];// = malloc (imageWidth*sizeof(int));
//        memcpy(im[i], image[i], imageWidth*sizeof(int));
    }

    delete im;
    delete transform;
    delete hood;
	return 0;
}
