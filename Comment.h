#pragma once
#include "MyString.h"
#include "Vector.hpp"
#include "Pair.hpp"
#include <fstream>

class Comment
{
	Vector<MyString> _replies;
	MyString _userName;
	MyString _text;
	int _rating = 0;
	unsigned _commentId;
	static unsigned _id;

public:
	Comment() = default;
	explicit Comment(size_t);
	Comment(const MyString&, const MyString&);

	const unsigned getId() const;
	const MyString& getText() const;

	void addReply(const MyString&);
	void rate(int);

	void showReplies() const;
	unsigned getRating() const;

	friend std::ostream& operator<<(std::ostream&, const Comment&);
	friend std::istream& operator>>(std::istream&, Comment&);
};