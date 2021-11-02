#include <iostream>
#include "framepacker.h"
#include <opencv2/opencv.hpp>

bool testBasicFramePackUnpack()
{
  std::string source = "/home/shekhar/Pictures/Webcam/shekhar.jpg";
   cv::Mat image = imread(source, cv::IMREAD_COLOR);
   FramePacker packer;
   int errCode = 0;
   cv::imshow("first read", image);
   packer.setPackingStructureMeta(source);
   spdlog::info("Sending data: {} {} {}X{} {} {}", source, image.type(), image.rows, image.cols, image.total()*image.channels(), image.dims);
   auto str = packer.packFrame(image, errCode);

   //Send over socket and recieve on the other end

   auto ps = packer.unpackFrame(str);
   spdlog::info("Recieved data:  {} {} {}X{} {}", ps.source, ps.type, ps.height, ps.width, ps.imgData.size());
   std::cout << ps.source << std::endl << source << std::endl;

   assert(ps.source == source);

   cv::imshow("second image", cv::Mat(ps.height, ps.width, ps.type, ps.imgData.data()));

   if(cv::waitKey(0) == 'c')
       return true;

   getchar();
   cv::destroyAllWindows();
   return true;
}

int main(int argc, char *argv[])
{
    testBasicFramePackUnpack();
    return 0;
}
