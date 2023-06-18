#pragma once
#include "MyString.h"
#include "Vector.hpp"
#include "Pair.hpp"
#include <fstream>

class User
{
	Vector<Pair<unsigned, bool>> _commentRatings;
	MyString _firstName;
	MyString _lastName;
	MyString _password;
	unsigned _points = 0;
	unsigned _userId;
	static unsigned _id;

public:
	User() = default;
	explicit User(size_t);
	User(const MyString&, const MyString&, const MyString&);

	const MyString& getName() const;
	const unsigned getId() const;
	const unsigned getPoints() const;

	void addPoint();

	bool isUser(const MyString&, const MyString&, const MyString&) const;
	bool isUser(const MyString&, const MyString&) const;

	bool addRating(unsigned);

	friend std::ostream& operator<<(std::ostream&, const User&);
	friend std::istream& operator>>(std::istream&, User&);
};

