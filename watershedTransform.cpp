# include "malloc.h"
#include "string.h"
#include "const.h"
#include "stdio.h"
//#include "Point.h"
//#include "Neighbourhood.h"
#include "watershedTransform.h"



watershedTransform::watershedTransform(){}

watershedTransform::watershedTransform(Neighbourhood *hood, int inWidth, int inPitch, int inRows)
{
    init(hood, inWidth, inPitch, inRows);
}

watershedTransform * watershedTransform::createInstance(Neighbourhood *hood, int inWidth, int inPitch, int inRows)
{
    watershedTransform *transform =  (inPitch > 0 && inRows > 0) ? new watershedTransform(hood, inWidth, inPitch, inRows): NULL;
    return transform;
}

 watershedTransform::~watershedTransform()
{
     for (int i=0; i<mInRows; i++)
    {
        free (out[i]); 
     } 
    free(out);
    mBasins.clear();
    mQueue.clear();
    
}

void watershedTransform::init(Neighbourhood *hood, int inWidth,  int inPitch, int inRows)
{
    mHood = hood;
    mInPitch = inPitch;
    mInRows= inRows;
    mInWidth = inWidth;
    cmap = NULL;
  //  mHistogram = (int *) malloc(MAX_VALUE * sizeof(int));
  //  memset(mHistogram, 0, MAX_VALUE * sizeof(int));
    mBasins.clear();
    out = (int **) malloc (mInRows *sizeof(int *));
    for (int i=0; i<mInRows; i++)
    {
        out[i] = (int *) malloc (mInPitch*sizeof(int));
        memset(out[i], INIT_WORK_VALUE, mInPitch*sizeof(int));
     }
    ccounter = 0;
}

void watershedTransform::setInput(int **input)
{
    in = input;
}

void watershedTransform::computeBasin()
{
    int *rowptr;
    int i=0;
    int  *histogram= (int*) malloc(MAX_VALUE * sizeof(int));

    for (i=0; i<mInRows; i++)
    {
        rowptr = in[i];
        for (int j=0; j<mInWidth; j++)
        {    
            std::cout << "in[" << j <<", " << i  << "] = " <<  rowptr+j << ": " << *(rowptr+j) << "\n";            
              histogram[*(rowptr+j)]++;
        }
    }

    for (i=0; i<MAX_VALUE; i++)
    {
        if (histogram[i] > 0) {
            mBasins.push_back(i);
        }
    }
    free(histogram);

   // return mBasins;
}

void watershedTransform::buildArrowingMap(int *inPtr, int *outPtr, int minValue, int h, int w)//, int ccounter)
{
    int nbSize = mHood->getSize();
    int nbCount = 0;
//    int *startPos = in[h];
//    int *endPos = in[h]+mInPitch;
    cout  << "buildArrowingMap h = " << h << " w= " << w << " nbSize= " << nbSize << "\n";
    for (int i=0; i<nbSize; i++)
    {
        Point pt  = mHood->getNeighbourPosition(i);
        int posX = pt.getX()+w;
        int posY = pt.getY()+h;

        cout  << "(posX, posY)  = (" << pt.getX()  << ", " << pt.getY()  << "), (" << posX  << ", " << posY  << ") \n";

        if (posX < 0 || posX >= mInWidth || posY < 0 || posY >= mInRows)
            continue;

        int nbValue = *(inPtr +  pt.getY() * (mInPitch + ((2*sizeof(inPtr))/sizeof(int))) +  pt.getX());
//        int *nbOutPtr = outPtr  +  posY * mInPitch +  posX;
        int *nbOutPtr = outPtr + pt.getY() *(mInPitch + ((2*sizeof(outPtr))/sizeof(int))) +  pt.getX() ;

        cout  << "outValue " << *nbOutPtr <<  " nbValue = " << nbValue << "\n";
        //printf("outPtr = %d \n ", outPtr  +  pt.getY() * mInPitch +  pt.getX() );
        //std::cout  << "outValue " << *(inPtr + pt.getY() *mInPitch) <<  " nbValue = " << nbValue << " pos =" <<  pt.getY() * mInPitch +   pt.getX() << "\n";

        if (*nbOutPtr == INIT_WORK_VALUE) 
        {
            if ((nbValue == minValue && *outPtr != MASK) ||
            //    (nbValue == minValue && *outPtr == MASK)  ||
               (nbValue > minValue))
            {            
                *nbOutPtr = pt.getIntDirection();
            } 
        }      
       // mQueue.push_back(Point(posX, posY, pt.getDirection()));
        nbCount++;
    }
   // std::cout  << "nbCount for pt (" << w << ",  "<< h  << ") = " << nbCount << "\n";
}

bool watershedTransform::buildLabelMap(int *inPtr, int *outPtr,  int h, int w)
{
    int nbSize = mHood->getSize();
    int nbCount = 0;
    list<Point> tQueue;
    bool isFound = true;
//    int *startPos = in[h];
//    int *endPos = in[h]+mInPitch;
    cout  << "buildLabelMap: h = " << h << " w= " << w << " nbSize= " << nbSize << "\n";

    int min_Value = 0xFFFE;

    for (int i=0; i<nbSize; i++)
    {
        Point pt  = mHood->getNeighbourPosition(i);
        int posX = pt.getX()+w;
        int posY = pt.getY()+h;

        cout  << "(posX, posY)  = (" << pt.getX()  << ", " << pt.getY()  << "), (" << posX  << ", " << posY  << ") \n";

        if (posX < 0 || posX >= mInWidth || posY < 0 || posY >= mInRows)
            continue;

        int nbValue = *(inPtr +  pt.getY() * (mInPitch + (2*sizeof(inPtr)/sizeof(int))) +  pt.getX());
//        int *nbOutPtr = outPtr  +  posY * mInPitch +  posX;
        int *nbOutPtr = outPtr + pt.getY() *(mInPitch + (2*sizeof(outPtr)/sizeof(int))) +  pt.getX() ;

        cout  << "outValue " << *nbOutPtr <<  " nbValue = " << nbValue << "\n";

        //if (*nbOutPtr == INIT_WORK_VALUE) 

        // check if a new component is found !!
        // 3 cases: 
        // 1) neigbhour pixels never update before (INIT_WORK_VALUE)
        // 2) neigbhour pixels belongs to another component (due to the algorithmic nature, pixel value < current one)
        
 
        if (*nbOutPtr > INIT_WORK_VALUE && 
            nbValue < *inPtr &&
            nbValue < min_Value &&
            *nbOutPtr < *outPtr ) 
        {
            *outPtr = *nbOutPtr;
            //min_Value = nbValue;
            isFound = false;            
        }

        min_Value = (nbValue < min_Value) ? nbValue: min_Value;
/*
        else if (*nbOutPtr == MASK) 
        {            
            *nbOutPtr = ccounter;
        //    tQueue.push_back(Point(posX, posY));
        } */
      /*  else if (nbValue > *inPtr)
        {
            *nbOutPtr = ccounter;
        }*/



    }

 

  // while (getchar() != '\n');
  //  fflush(stdin);    

    std::cout << "tQueue size " << tQueue.size() << "\n";
    for (Point pt: tQueue)
    {
        int x = pt.getX();
        int y = pt.getY();
        int *inPtr = in[y] + x;
        int *outPtr = out[y] + x;

        buildLabelMap(inPtr, outPtr, y, x);
    }


    std::cout << "Finish building component map \n";
   //mQueue.push_back(Point(posX, posY, pt.getDirection()));
    nbCount++;

    return isFound;

   // std::cout  << "nbCount for pt (" << w << ",  "<< h  << ") = " << nbCount << "\n";
}
int watershedTransform::initOutput(int *cmap, int minValue)
{
    int *inPtr, *outPtr;
    int nbCount = 0;
    //int ccounter = 0; // component counter

  //  std::cout  << "minValue = " << minValue << "\n";
    for (int i=0; i<mInRows; i++)
    {
        inPtr = in[i];
        outPtr = out[i];

        for (int j=0; j<mInWidth; j++)
        {             
            int *outptr = outPtr+j;
            if (*(inPtr+j) == minValue)// && *(outPtr+j) == INIT_WORK_VALUE)
            {        
               *outptr = (*outptr == INIT_WORK_VALUE) ? MASK: *outptr;  
      //          buildArrowingMap(inPtr+j, outptr, minValue, i, j);//, ccounter);
                mQueue.push_back(Point(j, i));
                nbCount++;
            }
        }
    }

    std::cout << "\n";

    bool isFound = true;
    for (Point pt: mQueue)
    {
        int x = pt.getX();
        int y = pt.getY();
        int *inPtr = in[y] + x;
        int *outPtr = out[y] + x;
        *outPtr = ccounter;
        if (buildLabelMap(inPtr, outPtr, y, x) == false)
        {
            isFound = false;
        }
    }
   if (isFound == false) ccounter--;
    std::cout  << "nbCount for min (" << minValue << ") = " << nbCount << "\n";
    std::cout << "# of label = " << ccounter << "\n";

    for (int i=0; i<mInRows; i++)
    {
        outPtr = out[i];
        for (int j=0; j<mInWidth; j++)
        {
            std::cout  << *(outPtr+j) << " ";
        }
        std::cout << "\n";
    }
    return 0;
    
//    mQueue.push_back(Point(mInPitch, mInRows));
}

int ** watershedTransform::computeWTransform()
{
//    int *cmap = NULL;
    int csize =0;
    computeBasin();

    if (cmap != NULL)
    {
        delete cmap;
    }
    cmap = new int [mBasins.size()];
    memset(cmap, 0, sizeof(int)*mBasins.size());
    ccounter = 0;
    for ( int min:mBasins)
    {
        mQueue.clear();
        std::cout << "mQueue size (min = " << min << "pos = " << mBasins.size()  << ") = ";
        ccounter++;
        csize = initOutput(cmap, min);
        std::cout <<  mQueue.size() << "\n";

        for (Point pt: mQueue)
        {            
           int nValue = *(in[pt.getY()]+pt.getX());
          // std::cout << " value at (" << pt.getX() << ", " << pt.getY() <<  ", " << pt.getDirection() << ")  = " << nValue << " \n";          
        }
      //  while (getchar() != '\n');
      //  fflush(stdin);

 //       break;

    }
    delete cmap;
   std::cout << "Done.";

    return NULL;
}

