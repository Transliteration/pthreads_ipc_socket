#include <iostream>
#include <string>
#include <algorithm>
#include <sstream>

#include "producer.hpp"

Producer::Producer(Buffer &buffer)
	: buffer(buffer), should_stop(false)
{
}

void Producer::run()
{
	std::string user_input;

	while (!should_stop)
	{
		std::cout << "Input your string:\n";
		std::getline(std::cin, user_input);

		if (checkInput(user_input))
		{
			buffer.lock();

			buffer.setData(transformInput(std::move(user_input)));

			buffer.signal();
			buffer.unlock();
		}
	}

	// unreachable
	pthread_exit(nullptr);
}

bool Producer::checkInput(const std::string &inputStr)
{
	bool containsOnlyDigits = inputStr.find_first_not_of("0123456789") == std::string::npos;
	bool lengthCheck = inputStr.length() <= 64;

	if (!containsOnlyDigits)
	{
		std::cerr << "Producer: Your input does not consist entirely of numbers!\n";
	}

	if (!lengthCheck)
	{
		std::cerr << "Producer: Your input string contains more then 64 symbols!\n";
	}

	return containsOnlyDigits && lengthCheck;
}

std::string Producer::transformInput(std::string inputStr)
{
	std::stringstream transformedInput;

	std::sort(std::rbegin(inputStr), std::rend(inputStr));

	for (const auto &ch : inputStr)
	{
		if ((ch - '0') % 2 == 0)
		{
			transformedInput << "KB";
		}
		else
		{
			transformedInput << ch;
		}
	}

	return transformedInput.str();
}