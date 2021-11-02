#ifndef FRAMEPACKER_H
#define FRAMEPACKER_H

#include <opencv2/opencv.hpp>
#include <stdint.h>
#include <string>
#include <msgpack.hpp>
#include <vector>
#include <iostream>
#include <spdlog/spdlog.h>

#define fname std::cout << __PRETTY_FUNCTION__ << std::endl;

struct packingStructure
{
    uint16_t height;
    uint16_t width;
    uint16_t type;
    uint16_t channels;
    uint16_t dims;
    std::vector<uchar> imgData;
    std::string source;
    MSGPACK_DEFINE(height, width, type, channels, dims, imgData, source);
};

class FramePacker
{
public:
    FramePacker();
    void setPackingTemplate();
    void setPackingStructureMeta(std::string source);
    std::string packFrame(const cv::Mat& frame, int& error);
    packingStructure unpackFrame(std::string& packStr);
private:
    packingStructure ps;
};

#endif // FRAMEPACKER_H
