#include "client.h"
#include "framepacker.h"
#include <signal.h>

bool appExit = false;
void ctrCHandler(int signal)
{
    printf("Got signal to exit\n");
    appExit = true;
}

Client::Client(int port, std::string topicName)
{
    m_context = zmq::context_t(1);
    m_socket = zmq::socket_t(m_context, zmq::socket_type::sub);
    m_socket.setsockopt(ZMQ_SUBSCRIBE, topicName.c_str(), topicName.size());
    m_socket.connect("tcp://localhost:"+std::to_string(port));
    if (!m_socket.connected())
    {
        spdlog::error("Unable to start server");
        std::runtime_error("Unable to start server");
    }
    m_topic = topicName;
}

void Client::revieveFrame()
{
    fname;
    zmq::message_t topicName;
    zmq::message_t payload;
    cv::namedWindow("Recieved Frame");
    FramePacker packer;
    spdlog::info("Client started waiting for the frame");
    while(!appExit)
    {
        auto rc = m_socket.recv(topicName, zmq::recv_flags::none);
        spdlog::info("topicname: {}", topicName.to_string());
        rc = m_socket.recv(payload, zmq::recv_flags::none);
        auto frameStr = payload.to_string();
        packingStructure ps = packer.unpackFrame(frameStr);
        cv::imshow("Recieved Frame", cv::Mat(ps.height, ps.width, ps.type, ps.imgData.data()));
        if (cv::waitKey(1) == 'q')
            appExit = true;
    }
    cv::destroyAllWindows();
}

void Client::close()
{
    fname;
    std::cout << "Close called" << std::endl;
    try{
        if (m_socket.handle() != nullptr)
        {
            m_socket.close();
        }
//        m_context.shutdown();
    }
    catch(zmq::error_t& e)
    {
        spdlog::error(e.what());
    }
}


int main(int argc, char *argv[])
{
    signal(SIGINT, ctrCHandler);
    Client client(5000, "frame");
    client.revieveFrame();
    return 0;
}

