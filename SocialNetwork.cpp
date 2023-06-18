#include "Engine.h"

int main()
{
	try
	{
		run();
	}
	catch (std::logic_error& err)
	{
		std::cout << err.what();
	}
	catch (std::invalid_argument& err)
	{
		std::cout << err.what();
	}
	catch (std::runtime_error& err)
	{
		std::cout << err.what();
	}
	catch (const std::exception& err)
	{
		std::cout << err.what();
	}
	catch (...)
	{
		std::cout << "Invalid argument!";
	}
	return 0;
}