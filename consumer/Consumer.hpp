#include <string>

class Consumer
{
    std::string &buffer;
	bool should_stop;

public:
	Consumer(std::string &buffer);

    void run();
}