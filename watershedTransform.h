#include <list>
#include <iostream>
#include "Point.h"
#include "Neighbourhood.h"
using namespace std;

class watershedTransform
{
    public:
        watershedTransform();
        static watershedTransform * createInstance(Neighbourhood *hood, int inWidth, int inPitch, int inRows);
        ~watershedTransform();
        void setInput(int **input);
        int ** computeWTransform();
       
    private:

        watershedTransform(Neighbourhood *hood, int inWidth, int inPitch, int inRows);
        void init(Neighbourhood *hood, int inWidth, int inPitch, int inRows);
        void computeBasin();
        int initOutput(int *cmap, int minValue);
//          void saveNeigbours(int *ptr, int h, int w);
        void buildArrowingMap(int *inPtr, int *outPtr, int minValue, int h, int w);
        bool buildLabelMap(int *inPtr, int *outPtr,  int h, int w);
    //    Neighbourhood *mHood;
        int **in;
        int **out;
        int **dist;
        int *cmap;
        int ccounter; // component counter
        Neighbourhood *mHood;

        list<int> mBasins ;
        list<Point> mQueue;
      //  int *mHistogram;
        int mInPitch;
        int mInRows;
        int mInWidth;
};

