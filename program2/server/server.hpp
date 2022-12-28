#pragma once

class Server
{
public:
    Server(bool &should_stop);
    ~Server();

    void start_listening();

private:
    void init_socket();
    void bind_socket();
    void prepare_to_accept_connections();

    int server_socket;
    bool initialized_successefully;

    bool &should_stop;
};