#include "HelperFunctions.h"

bool isDigit(const MyString& str)
{
	unsigned i = 0;
	while (str[i] != '\0')
	{
		if (str[i] < 48 || str[i] > 57)
			return false;

		i++;
	}

	return true;
}

unsigned convertToDigit(const MyString& str)
{
	size_t i = 0;
	unsigned digit = 0;

	while (str[i] != '\0')
	{
		digit *= 10;
		digit += (str[i] - 48);
		i++;
	}

	return digit;
}
