#include "Post.h"

unsigned Post::_id = 0;

Post::Post(size_t id)
{
	Post::_id = id;
}

Post::Post(const MyString& title, const MyString& description)
{
	_title = title;
	_description = description;
	_postId = ++_id;
}

const MyString& Post::getName() const
{
	return _title;
}

const MyString& Post::getDescription() const
{
	return _description;
}

const unsigned Post::getId() const
{
	return _postId;
}

void Post::comment(const MyString& comment, const MyString& userName)
{
	_comments.pushBack(Comment(userName, comment));
}

void Post::showComments() const
{
	size_t size = _comments.getSize();

	if (size == 0)
	{
		std::cout << "No comments!" << std::endl;
		return;
	}

	else
	{
		for (size_t i = 0; i < size; i++)
		{
			std::cout << ">>" << _comments[i].getText() << " {Id: " << _comments[i].getId() << "}";
			int rating = _comments[i].getRating();

			if (rating != 0)
				std::cout << " {rating: " << rating << "}";

			std::cout << std::endl;
			_comments[i].showReplies();
		}
	}
}

void Post::reply(unsigned commentId, const MyString& reply)
{
	size_t size = _comments.getSize();

	if (size == 0)
	{
		std::cout << "No comments!" << std::endl;
		return;
	}

	bool replied = false;
	for (size_t i = 0; i < size; i++)
	{
		if (_comments[i].getId() == commentId)
		{
			_comments[i].addReply(reply);
			replied = true;
		}
	}

	if (!replied)
		std::cout << "There is no comment with this id!" << std::endl;
}

void Post::upvote(unsigned commentId, bool isRated)
{
	size_t size = _comments.getSize();

	if (size == 0)
	{
		std::cout << "No comments!" << std::endl;
		return;
	}

	bool exists = false;

	for (size_t i = 0; i < size; i++)
	{
		int rating = _comments[i].getRating();

		if (_comments[i].getId() == commentId && isRated == true)
		{
			rating < 0 ? _comments[i].rate(1) : _comments[i].rate(-1);
			//_comments[i].rate(-1);
			exists = true;
		}
		else if (_comments[i].getId() == commentId && isRated == false)
		{
			_comments[i].rate(1);
			exists = true;
		}
	}

	if (!exists)
		std::cout << "There is no comment with this id!" << std::endl;
}

void Post::downvote(unsigned commentId, bool isRated)
{
	size_t size = _comments.getSize();

	if (size == 0)
	{
		std::cout << "No comments!" << std::endl;
		return;
	}

	bool exists = false;

	for (size_t i = 0; i < size; i++)
	{
		int rating = _comments[i].getRating();
		if (_comments[i].getId() == commentId && isRated == true)
		{
			rating <= 0 ? _comments[i].rate(1) : _comments[i].rate(-1);
			//_comments[i].rate(1);
			exists = true;
		}
		else if (_comments[i].getId() == commentId && isRated == false)
		{
			_comments[i].rate(-1);
			exists = true;
		}
	}

	if (!exists)
		std::cout << "There is no comment with this id!" << std::endl;
}

std::ostream& operator<<(std::ostream& os, const Post& p)
{
	os << p._title << '\n'
		<< p._description << '\n'
		<< p._postId << '\n';

	size_t commentsSize = p._comments.getSize();

	os << commentsSize << '\n';

	for (size_t i = 0; i < commentsSize; i++)
		os << p._comments[i]; //removed '/n'

	return os;
}

std::istream& operator>>(std::istream& is, Post& p)
{
	//is.ignore();

	is >> p._title >> p._description >> p._postId;

	size_t commentsSize;

	is >> commentsSize;

	//if (commentsSize != 0)
		is.ignore();

	for (size_t i = 0; i < commentsSize; i++)
	{
		Comment c(commentsSize);
		is >> c;
		p._comments.pushBack(std::move(c));
		//is >> p._comments[i];
	}

	return is;
}