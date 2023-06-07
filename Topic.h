#pragma once
#include "MyString.h"
#include "Vector.hpp"
#include "Post.h"
#include <fstream>

class Topic
{
	Vector<Post> _posts;
	MyString _title;
	MyString _creatorName;
	MyString _description;
	unsigned _creatorId;
	unsigned _topicId;
	static unsigned _id;

public:
	Topic() = default;
	explicit Topic(size_t);
	Topic(const MyString&, const MyString&, const MyString&, unsigned);

	const MyString& getName() const;
	const unsigned getId() const;

	void list() const;
	void showInfo() const;
	void post(const MyString&, const MyString&);
	Post* p_open(const MyString&);
	Post* p_open(unsigned);

	bool isTopic(const MyString&);

	friend std::ostream& operator<<(std::ostream&, const Topic&);
	friend std::istream& operator>>(std::istream&, Topic&);
};


