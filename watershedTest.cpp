#include <iostream>
#include <malloc.h>


#include "string.h"
//#include "Point.h"
//#include "Neighbourhood.h"
#include "watershedTransform.h"
#include "Magick++.h"
//#include "MagickCore/image.h"
//#include "Magick++/ImageRef.h"
//#define imageWidth 10

#define imageWidth 7

using namespace std;
using namespace Magick;

class watershedTest
{
	public:
	 watershedTest();

};


void initImageMagick()
{
/*    InitializeMagick(NULL);

//InitializeMagick(*argv);

//    inImage.read("../../clip/lena.ppm");
//    inImage.magick("YUV");
//    inImage.defineValue("jpeg", "sampling-factor", "4:2:0");

    Image inImage("../../clip/pool.png");

    //inImage.read("../../clip/pool.png");

    inImage.grayscale(Rec709LumaPixelIntensityMethod);

    int width = inImage.columns();
    int height = inImage.rows();
    ImageInfo *info = inImage.imageInfo();
    std::cout << "width = " << width << " height = " << height << "\n";
    
 
 //   ExceptionInfo exceptionInfo;
  //  Image new_image = ReadYCBCRImage(info, &exceptionInfo); 
    Pixels my_pixel_cache(inImage);

    PixelInfo pixelInfo;
    GetPixelInfo(inImage.constImage(), &pixelInfo);

    std::cout << "colorspace = " << inImage.colorSpace() << "\n";

    std::cout << "image width = " << inImage.columns() << "\n";



//   PixelData pixelData(inImage,"RGB", CharPixel);

 //   char *data2 = (char *) pixelData.data();
 //   int size = pixelData.size();
 //   Quantum *data2 = pixelData.get(0, 0, width,height);
ExceptionInfo exceptionInfo;
 //   QuantumFormatType formatType = GetQuantumFormat(info);
   MagickCore::QuantumType qType = GetQuantumType(inImage.constImage(), &exceptionInfo);

    GetPixelInfo(inImage.constImage(), &pixelInfo);
   MagickCore::QuantumInfo *qInfo = AcquireQuantumInfo(info, inImage.constImage());
  //  GetQuantumInfo(info->constImageInfo(), &qInfo);
//    GetPixelInfoIntensity(inImage.constImage(), &pixelInfo);
    std::cout << "colorspace = " << inImage.colorSpace() << "\n";

    std::cout << "image width = " << inImage.columns() << "\n";

//    ExportImagePixels(image,0,0,640,1,"RGB",CharPixel,pixels,exception);
   Quantum *data = my_pixel_cache.get(0, 0, width,height);
    ColorGray green("blue"); 

 //   MagickCore::Image coreImage = ReadImage(info, 
//quantum_info=AcquireQuantumInfo(imageInfo(),image());
 //   MagickCore::QuantumInfo *qInfo = AcquireQuantumInfo(info,NULL);

  unsigned char *magick_restrict pixels;
  //int len = ExportQuantumPixels(inImage.constImage(), (const CacheView *) NULL,qInfo,qType, pixels, &exceptionInfo);
    Quantum *ptr = data;
    int row = 0, column = 0;
    for (row = 0; row < height ; ++row ) 
    {
   //     ptr = data + 3 * row * width;
        for (column = 0; column < width ; ++column ) 
        {

                // Y  =      (0.257 * R) + (0.504 * G) + (0.098 * B) + 16
                // Cr = V =  (0.439 * R) - (0.368 * G) - (0.071 * B) + 128
                // Cb = U = -(0.148 * R) - (0.291 * G) + (0.439 * B) + 128

                // YUV to RGB Conversion

                // B = 1.164(Y - 16)                   + 2.018(U - 128)
                // G = 1.164(Y - 16) - 0.813(V - 128) - 0.391(U - 128)
                // R = 1.164(Y - 16) + 1.596(V - 128)
             //   *ptr = QuantumRange*green.quantumRed(); ptr++;
               // *ptr = QuantumRange*green.quantumGreen(); ptr++;
               // *ptr = QuantumRange*green.quantumBlue(); ptr++;
            //  *pixels++=QuantumRange*green.quantumRed();
            //  *pixels++=QuantumRange*green.quantumGreen();
            //  *pixels++=QuantumRange*green.quantumBlue();
        }

//        return;
    } 
    my_pixel_cache.sync();
//    inImage.colorSpace(MagickCore::YCbCrColorspace);
    inImage.write( "test.png" );
*/

}

int main()
{
   HoodPoint  neigbors[] =
   {
      // Point(-1, -1, "Bottom_Left"),
      HoodPoint(0, -1, "Bottom"),
      HoodPoint(-1, 0, "Left"),
      // Point(1, -1, "Bottom_Right"),
      HoodPoint(1, 0, "Right"),
      // Point(1,1, "Top_Right"),
      HoodPoint(0, 1, "Top") // ,
      // Point(-1, 1, "Top_Left")
   };

   int image [][imageWidth] = 
   /* {
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
   }; */
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

   std::cout << "neigbhour: (" << neigbors[2].getX() << ", "  <<  neigbors[2].getY() << ", "  << neigbors[2].getDirection() << ") \n";
   std::cout << "neigbhour size : " << sizeof(neigbors)/sizeof(HoodPoint) <<"\n";
   Neighbourhood *hood = Neighbourhood::createInstance(neigbors, sizeof(neigbors)/sizeof(HoodPoint), imageWidth);
   std::cout << "hood is created. ";
   std::cout << "pos: " << hood->getNeighbourPosition(2).getX() << "\n";
   int imagePitch = ((imageWidth&0x10000)+1) << 4;
   int rows = sizeof(image)/(imageWidth*sizeof(int));
   std::cout << "# Image row: " << rows << " image size = " << sizeof(image) <<  " imagePitch="  << (imageWidth&0x1000) << "\n";

   HoodPoint pt = HoodPoint::getDirPoint(-1);

    int **im = (int **) malloc (rows * sizeof(int *));//new int * [rows];
    int i;
    for (i=0; i<rows; i++)
    {
        im[i] = (int*) malloc (imagePitch * sizeof(int ));//new int [imagePitch];
        std::cout << "im [ " << i << "] =: " << im[i] << "\n"; 
        memcpy(im[i], image[i], imagePitch*sizeof(int));
    }

    std::cout << "# Image row: " << rows << " im size = " << im[1] << ", " << im[0]  << "addr size=" << sizeof(im[1]) << " pitch=" << imagePitch*sizeof(int) <<  " \n";

    watershedTransform *transform = watershedTransform::createInstance(hood, imageWidth, imagePitch,  rows);
    std::cout << "watershedTransform createInstance done  \n";
    transform->setInput(im);
    transform->computeWTransform();

    for (i=rows-1; i>=0; i--)
    {
        free (im[i]);
    }
    free(im);
    delete hood;
    delete transform;

	return 0;
}
