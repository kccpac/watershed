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
   mHood = NULL;
}

void watershedTransform::init(Neighbourhood *hood, int inWidth,  int inPitch, int inRows)
{
   mHood = hood;
   mInPitch = inPitch;
   mInRows= inRows;
   mInWidth = inWidth;
   cmap = NULL;
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

    memset(histogram, 0, MAX_VALUE * sizeof(int));
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

}

void watershedTransform::buildArrowingMap(int *inPtr, int *outPtr, int minValue, int h, int w)//, int ccounter)
{
   int nbSize = mHood->getSize();
   int nbCount = 0;

   cout  << "buildArrowingMap h = " << h << " w= " << w << " nbSize= " << nbSize << "\n";
   for (int i=0; i<nbSize; i++)
   {
      HoodPoint pt  = mHood->getNeighbourPosition(i);
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
   list<HoodPoint> tQueue;
   bool isFound = true;

   cout  << "buildLabelMap: h = " << h << " w= " << w << " nbSize= " << nbSize << "\n";

   int min_Value = 0xFFFE;
   int nbValue;
   int *nbOutPtr = NULL;
   int nbOutValue;
   int posX, posY;
   HoodPoint pt;
   for (int i=0; i<nbSize; i++)
   {
      pt  = mHood->getNeighbourPosition(i);
      posX = pt.getX()+w;
      posY = pt.getY()+h;

      cout  << "(posX, posY)  = (" << pt.getX()  << ", " << pt.getY()  << "), (" << posX  << ", " << posY  << ") \n";

      if (posX < 0 || posX >= mInWidth || posY < 0 || posY >= mInRows //||
      //     pt.getX() < 0 ||  pt.getX() >= mInWidth || pt.getY()  < 0 || pt.getY()  >= mInRows
      )
      continue;

      nbValue = in[posY][posX];//*(inPtr +  pt.getY() * (mInPitch + (2*sizeof(inPtr)/sizeof(int))) +  pt.getX());
      //        int *nbOutPtr = outPtr  +  posY * mInPitch +  posX;
      nbOutPtr = &out[posY ][posX];// outPtr + pt.getY() *(mInPitch + (2*sizeof(outPtr)/sizeof(int))) +  pt.getX() ;

      //     int testValue = *(inPtr +  pt.getY() * (mInPitch + (2*sizeof(inPtr)/sizeof(int))) +  pt.getX());
      //     int testOutValue =  *(outPtr + pt.getY() *(mInPitch + (2*sizeof(outPtr)/sizeof(int))) +  pt.getX());
      cout  << "outValue " << *nbOutPtr <<  " nbValue = " << nbValue << "\n";

      /*      if (testValue != nbValue || *nbOutPtr != testOutValue)
      {
      cout  << "Problem is found... testValue=" << testValue <<  " testOutValue = " << testOutValue << "\n";
      }*/
      // check if a new component is found !!
      // 3 cases: 
      // 1) neigbhour pixels never update before (INIT_WORK_VALUE)
      // 2) neigbhour pixels belongs to another component (due to the algorithmic nature, pixel value < current one)


      if (*nbOutPtr > (int) INIT_WORK_VALUE && 
            nbValue < *inPtr &&
            nbValue < min_Value &&
            *nbOutPtr < *outPtr ) 
      {
      *outPtr = *nbOutPtr;
      isFound = false;            
      }

      min_Value = (nbValue < min_Value) ? nbValue: min_Value;
   }

   std::cout << "tQueue size " << tQueue.size() << "\n";
   int x, y;
   for (HoodPoint pt: tQueue)
   {
      x = pt.getX();
      y = pt.getY();
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
         if (*(inPtr+j) == minValue)
         {        
            *outptr = (*outptr == INIT_WORK_VALUE) ? MASK: *outptr;  
            mQueue.push_back(HoodPoint(j, i));
            nbCount++;
         }
      }
   }

   std::cout << "\n";

   bool isFound = true;
   int x, y;//, *inPtr, *outPtr;
   for (HoodPoint pt: mQueue)
   {
      x =pt.getX() ;
      y = pt.getY();
      inPtr = in[y] + x;
      outPtr = out[y] + x;
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
}

int ** watershedTransform::computeWTransform()
{
   int csize =0;

   computeBasin();

   if (cmap != NULL)
   {
      delete cmap;
   }

   cmap = (int*) new int [mBasins.size()];
   memset(cmap, 0, sizeof(int)*mBasins.size());
   ccounter = 0;
   for ( int min:mBasins)
   {
      mQueue.clear();
      std::cout << "mQueue size (min = " << min << "pos = " << mBasins.size()  << ") = ";
      ccounter++;
      csize = initOutput(cmap, min);
      std::cout <<  mQueue.size() << "\n";
      /*
      for (HoodPoint pt: mQueue)
      {            
         int nValue = *(in[pt.getY()]+pt.getX());
         std::cout << " value at (" << pt.getX() << ", " << pt.getY() <<  ", " << pt.getDirection() << ")  = " << nValue << " \n";          
      }
      */
   }
   delete [] cmap;
   std::cout << "Done. \n";

   return NULL;
}

