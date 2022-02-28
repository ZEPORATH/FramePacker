#ifndef SERVER_H
#define SERVER_H

#include <string>
#include <zmq.hpp>

class Server
{
public:
    Server(int port, std::string topicName);
    ~Server();
    void publishFrame(const std::string &data);
    void close();
private:
    zmq::context_t m_context;
    zmq::socket_t m_socket;
    std::string m_topic;
};

#endif // SERVER_H
