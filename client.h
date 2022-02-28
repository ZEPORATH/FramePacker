#ifndef CLIENT_H
#define CLIENT_H

#include <string>
#include <zmq.hpp>
class Client
{
public:
    Client(int port, std::string topicName);
    void revieveFrame();
    void close();
    ~Client() {close();}
private:
    zmq::context_t m_context;
    zmq::socket_t m_socket;
    std::string m_topic;
};

#endif // CLIENT_H
