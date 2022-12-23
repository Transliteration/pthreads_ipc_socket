#include <string>

class Producer
{
	std::string &buffer;
	bool should_stop;

public:
	Producer(std::string &buffer);

	void run();
	bool checkInput(const std::string &inputStr);
	std::string transformInput(std::string &&inputStr);
};