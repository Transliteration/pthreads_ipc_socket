#include "consumer.hpp"
#include <iostream>
#include <numeric>

#include <unistd.h>
#include <netdb.h>

Consumer::Consumer(Buffer &buffer)
    : buffer(buffer), unsent_messages()
{
}

int Consumer::calculateSum(const std::string &data)
{
    auto convertCharToNumber = [](const unsigned char ch)
    {
        if (std::isdigit(ch))
        {
            return ch - '0';
        }
        else
        {
            return 0;
        }
    };

    return std::transform_reduce(std::begin(data), std::end(data), 0, std::plus<>(), convertCharToNumber);
}

void Consumer::run()
{
    while (true)
    {
        buffer.lock();
        buffer.wait();

        auto buffer_string = buffer.consumeData();
        int sum = calculateSum(buffer_string);
        auto sumAsStr = std::to_string(sum);

        unsent_messages.push(sumAsStr);

        while (unsent_messages.size() > 0)
        {
            bool message_sent = connectToServerAndSendData(unsent_messages.front());
            if (message_sent)
            {
                unsent_messages.pop();
            }
            else
            {
                std::cout << "Unsent message placed in queue.\n";
                break;
            }
        }

        buffer.unlock();
    }

    // unreachable
    pthread_exit(nullptr);
}

bool Consumer::connectToServerAndSendData(const std::string &data)
{
    int socket;
    int connection;
    addrinfo *servinfo;

    addrinfo hints{};
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE;

    int gai = getaddrinfo(NULL, "25565", &hints, &servinfo);
    if (gai != 0)
    {
        printf("getaddrinfo: %s\n", gai_strerror(gai));
        return false;
    }

    socket = ::socket(servinfo->ai_family, servinfo->ai_socktype, servinfo->ai_protocol);
    if (socket == -1)
    {
        perror("socket");
        return false;
    }

    connection = connect(socket, servinfo->ai_addr, servinfo->ai_addrlen);
    if (connection == -1)
    {
        perror("Can't connect to server");
        close(socket);
        return false;
    }

    int send_bytes = send(socket, data.c_str(), sizeof(data), 0);
    if (send_bytes == -1)
    {
        perror("send");
        return false;
    }

    freeaddrinfo(servinfo);
    close(socket);

    return true;
}