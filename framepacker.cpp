#include "framepacker.h"
#include <msgpack.hpp>
FramePacker::FramePacker()
{
    fname;
}

void FramePacker::setPackingTemplate()
{
    fname;
}

void FramePacker::setPackingStructureMeta(std::string source)
{
    fname;
    ps.source = source;
}

std::string FramePacker::packFrame(const cv::Mat &frame, int &error)
{
    fname;
    ps.height  = frame.rows;
    ps.width   = frame.cols;
    ps.channels = frame.channels();
    ps.dims = frame.dims;
    ps.type    = frame.type();
    ps.imgData = std::vector<uchar>(frame.data,frame.data + (frame.rows*frame.cols*frame.channels()));

    std::stringstream ss;
    msgpack::pack(&ss, ps);
    return ss.str();

}

packingStructure FramePacker::unpackFrame(std::string &packStr)
{
    fname;
    auto objectHandle = msgpack::unpack(packStr.data(), packStr.size());
    auto obj = objectHandle.get();
    packingStructure ps = obj.as<packingStructure>();
    return ps;
}

