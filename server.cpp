#include "server.h"
#include <spdlog/spdlog.h>
#include <signal.h>
#include "framepacker.h"

bool appExit = false;
void ctrCHandler(int signal)
{
    printf("Got signal to exit\n");
    appExit = true;
}

Server::Server(int port, std::string topicName)
{
    m_context = zmq::context_t(1);
    m_socket = zmq::socket_t(m_context, zmq::socket_type::pub);
    m_socket.bind("tcp://*:"+std::to_string(port));
    if (!m_socket.connected())
    {
        spdlog::error("Unable to start server");
        std::runtime_error("Unable to start server");
    }
    m_topic = topicName;
}

void Server::publishFrame(const std::string &data)
{
    zmq::message_t topicName(m_topic.size());
    zmq::message_t payload(data.size());

    memcpy(topicName.data(), m_topic.data(), m_topic.size());
    memcpy(payload.data(), data.data(), data.size());

    auto rc = m_socket.send(topicName, zmq::send_flags::sndmore);
    rc = m_socket.send(payload, zmq::send_flags::none);
}

void Server::close()
{
    fname;
    try{
        if (m_socket.handle() != nullptr)
        {
            m_socket.close();
        }
        m_context.shutdown();
    }
    catch(zmq::error_t& e)
    {
        spdlog::error(e.what());
    }
}

Server::~Server()
{
    close();
}

void produceForBroadcast(Server* server)
{
    fname;
    // Capture the frame
    // Serialize/pack the frame
    // publish

    cv::VideoCapture cap("/home/sshekhar/yt/FramePacker/Sample1.mp4");
    if (!cap.isOpened())
    {
        spdlog::error("Unable to open capture device");
        appExit = true;
        return;
    }
    cv::Mat frame;
    FramePacker packer;
    int errCode;
    cv::namedWindow("video feed", cv::WINDOW_AUTOSIZE);
    while(!appExit && cap.get(cv::CAP_PROP_POS_FRAMES) != cap.get(cv::CAP_PROP_FRAME_COUNT)-1)
    {
        cap.read(frame);
        std::string frameStr = packer.packFrame(frame, errCode);
        assert(!frameStr.empty());
        server->publishFrame(frameStr);
//        cv::imshow("video feed", frame);
//        if (cv::waitKey(1) == 'q')
//        {
//            appExit = true;
//            return;
//        }
    }
    cv::destroyAllWindows();
    appExit = true;
    return;
}

int main(int argc, char *argv[])
{
    signal(SIGINT, ctrCHandler);
    Server broadcastServer(5000, "frame");
    std::thread t1(produceForBroadcast, &broadcastServer);
    while(!appExit)
    {
        sleep(1);
    }
    return 0;
}
