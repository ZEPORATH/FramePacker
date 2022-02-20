#include <iostream>
#include "framepacker.h"
#include <opencv2/opencv.hpp>

bool testBasicFramePackUnpack()
{
  std::string source = "/home/sshekhar/yt/FramePacker/funny-dog.jpg";
   cv::Mat image = imread(source, cv::IMREAD_COLOR);
   FramePacker packer;
   int errCode = 0;
   cv::namedWindow("source Image", cv::WINDOW_AUTOSIZE);
   cv::namedWindow("deserialized Image", cv::WINDOW_AUTOSIZE);
   cv::imshow("source Image", image);
   packer.setPackingStructureMeta(source);
   spdlog::info("Sending data: {} {} {}X{} {} {}", source, image.type(), image.rows, image.cols, image.total()*image.channels(), image.dims);
   auto str = packer.packFrame(image, errCode);

    //   std::cout << str << std::endl;
   //Send over socket and recieve on the other end

   auto ps = packer.unpackFrame(str);
   spdlog::info("Recieved data:  {} {} {}X{} {}", ps.source, ps.type, ps.height, ps.width, ps.imgData.size());
   std::cout << ps.source << std::endl << source << std::endl;

   assert(ps.source == source);

   cv::imshow("deserialized Image", cv::Mat(ps.height, ps.width, ps.type, ps.imgData.data()));

   if(cv::waitKey(0) == 'c')
       return true;

   getchar();
   cv::destroyAllWindows();
   return true;
}

bool testBasicVideoStream() {
    fname;
    cv::VideoCapture cap("/home/sshekhar/yt/FramePacker/Sample1.mp4");
    if (!cap.isOpened())
    {
        spdlog::error("Unable to open capture device");
        return false;
    }
    cv::Mat frame;
    FramePacker packer;
    int errCode;
    cv::namedWindow("deserialized video feed", cv::WINDOW_AUTOSIZE);
    while(true)
    {
        cap.read(frame);
        std::string frameStr = packer.packFrame(frame, errCode);
        assert(!frameStr.empty());
        packingStructure ps = packer.unpackFrame(frameStr);
        cv::imshow("deserialized video feed", cv::Mat(ps.height, ps.width, ps.type, ps.imgData.data()));
        if (cv::waitKey(1) == 'q')
            return true;
    }
    cv::destroyAllWindows();
    return true;
}
int main(int argc, char *argv[])
{
//    testBasicFramePackUnpack();
    testBasicVideoStream();
    return 0;
}
