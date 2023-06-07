#include "Comment.h"

unsigned Comment::_id = 0;

Comment::Comment(size_t id)
{
	Comment::_id = id;
}

Comment::Comment(const MyString& userName, const MyString& text)
{
	_userName = userName;
	_text = text;
	_rating = 0;
	_commentId = ++_id;
}

void Comment::addReply(const MyString& reply)
{
	_replies.pushBack(reply);
}

void Comment::showReplies() const
{
	for (size_t i = 0; i < _replies.getSize(); i++)
		std::cout << "  >>" << _replies[i] << std::endl;
}

unsigned Comment::getRating() const
{
	return _rating;
}

const unsigned Comment::getId() const
{
	return _commentId;
}

const MyString& Comment::getText() const
{
	return _text;
}

void Comment::rate(int rating)
{
	_rating += rating;
}

std::ostream& operator<<(std::ostream& os, const Comment& c)
{
	os << c._userName << '\n'
		<< c._text << '\n'
		<< c._commentId << '\n'
		<< c._rating << '\n';

	size_t repliesSize = c._replies.getSize();

	os << repliesSize << '\n';

	for (size_t i = 0; i < repliesSize; i++)
		os << c._replies[i] << '\n'; // removed '\n'

	return os;
}

std::istream& operator>>(std::istream& is, Comment& c)
{
	is >> c._userName >> c._text >> c._commentId >> c._rating;

	size_t repliesSize;

	is >> repliesSize;
	is.ignore();

	for (size_t i = 0; i < repliesSize; i++)
	{
		MyString reply;
		is >> reply;
		c._replies.pushBack(std::move(reply));
		//is >> c._replies[i];
	}

	return is;
}