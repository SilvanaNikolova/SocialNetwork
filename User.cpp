#include "User.h"

unsigned User::_id = 0;

User::User(size_t id)
{
	User::_id = id;
}

User::User(const MyString& firstName, const MyString& lastName, const MyString& password)
{
	_firstName = firstName;
	_lastName = lastName;
	_password = password;
	_points = 0;
	_userId = ++_id;
}

bool User::isUser(const MyString& firstName, const MyString& lastName, const MyString& password) const
{
	return _firstName == firstName && _lastName == lastName && _password == password;
}

bool User::isUser(const MyString& firstName, const MyString& password) const
{
	return _firstName == firstName && _password == password;
}

const MyString& User::getName() const
{
	return _firstName;
}

const unsigned User::getId() const
{
	return _userId;
}

const unsigned User::getPoints() const
{
	return _points;
}

void User::addPoint()
{
	_points++;

}

bool User::addRating(unsigned commentId)
{
	size_t size = _commentRatings.getSize();

	for (size_t i = 0; i < size; i++)
	{
		if (_commentRatings[i].getFirst() == commentId &&
			_commentRatings[i].getSecond() == true)
		{
			_commentRatings[i].setSecond(false);
			return true;
		}
		else if (_commentRatings[i].getFirst() == commentId &&
			_commentRatings[i].getSecond() == false)
		{
			_commentRatings[i].setSecond(true);
			return false;
		}
	}

	Pair<unsigned, bool> p(commentId, true);
	_commentRatings.pushBack(p);
	return false;
}

std::ostream& operator<<(std::ostream& os, const User& u)
{
	os << u._firstName << '\n'
		<< u._lastName << '\n'
		<< u._password << '\n'
		<< u._userId << '\n'
		<< u._points << '\n';

	size_t size = u._commentRatings.getSize();

	os << size << '\n';

	for (size_t i = 0; i < size; i++)
	{
		os << u._commentRatings[i].getFirst() << '\n';
		os << u._commentRatings[i].getSecond() << '\n';
	}

	return os;
}

std::istream& operator>>(std::istream& is, User& u)
{
	is >> u._firstName >> u._lastName >> u._password >> u._userId >> u._points;

	size_t size;

	is >> size;

	unsigned firstArg;
	bool secondArg;

	for (size_t i = 0; i < size; i++)
	{
		is >> firstArg;
		is >> secondArg;

		Pair<unsigned, bool> p(firstArg, secondArg);
		u._commentRatings.pushBack(p);
	}

	return is;
}