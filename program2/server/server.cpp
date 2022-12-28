#include "server.hpp"

#include <iostream>

#include <netdb.h>
#include <unistd.h>

Server::Server(bool &should_stop)
    : initialized_successefully(true), should_stop(should_stop)
{
    init_socket();
    bind_socket();
    prepare_to_accept_connections();
}

Server::~Server()
{
    if (server_socket != -1)
    {
        close(server_socket);
    }
}

void Server::start_listening()
{
    if (!initialized_successefully)
    {
        std::cerr << "Failed to initialized server!\nExit!\n";
        exit(-1);
    }

    int count;
    std::string data;
    char buffer[64];

    while (!should_stop)
    {
        int client_fd = accept(server_socket, nullptr, nullptr);
        if (client_fd < 0)
        {
            perror("Error on accept! Continue to listening.");
            continue;
        }

        count = recv(client_fd, buffer, 64 - 1, 0);
        if (count <= 0)
        {
            perror("Error on receiving data from client!");
        }

        data = buffer;
        if (data.size() >= 2 && std::stoi(data) % 32 == 0)
        {
            std::cout << "Recieved data: [" << data << "]\n";
        }

        close(client_fd);
    }
}

void Server::init_socket()
{
    server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket == -1)
    {
        initialized_successefully = false;
    }

    const int enable = 1;
    if (setsockopt(server_socket, SOL_SOCKET, SO_REUSEADDR, &enable, sizeof(int)) < 0)
    {
        perror("setsockopt(SO_REUSEADDR) failed.");
    }
}

void Server::bind_socket()
{
    sockaddr_in server_address{};
    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = htons(INADDR_ANY);
    server_address.sin_port = htons(25565);

    if (bind(server_socket, reinterpret_cast<sockaddr *>(&server_address), sizeof(server_address)) < 0)
    {
        perror("Error on socket bind!");
        initialized_successefully = false;
    }
}

void Server::prepare_to_accept_connections()
{
    if (listen(server_socket, 1) == -1)
    {
        perror("Error on preparing for listen on socket!");
        initialized_successefully = false;
    }
}
