#include <cstring>
#include <string>
#include <iostream>

#include "server/server.hpp"
#include <signal.h>

bool should_stop = false;

void SIGINT_handler(int)
{
    should_stop = true;
}

void add_SIGINT_handler()
{
    struct sigaction sa;
    sa.sa_handler = SIGINT_handler;
    sigfillset(&sa.sa_mask);
    sigaction(SIGINT, &sa, NULL);
}

int main()
{
    add_SIGINT_handler();

    Server server(should_stop);
    server.start_listening();

    return 0;
}