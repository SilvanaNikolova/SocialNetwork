#pragma once
#include "MyString.h"
#include "Comment.h"
#include "Vector.hpp"
#include <fstream>

class Post
{
	Vector<Comment> _comments;
	MyString _title;
	MyString _description;
	unsigned _postId;
	static unsigned _id;

public:
	Post() = default;
	explicit Post(size_t);
	Post(const MyString&, const MyString&);

	const MyString& getName() const;
	const MyString& getDescription() const;
	const unsigned getId() const;

	void comment(const MyString&, const MyString&);
	void reply(unsigned, const MyString&);

	void showComments() const;

	void upvote(unsigned, bool);
	void downvote(unsigned, bool);

	friend std::ostream& operator<<(std::ostream&, const Post&);
	friend std::istream& operator>>(std::istream&, Post&);
};