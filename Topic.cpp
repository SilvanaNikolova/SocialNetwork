#include "Topic.h"

unsigned Topic::_id = 0;

Topic::Topic(size_t id)
{
	Topic::_id = id;
}

Topic::Topic(const MyString& title, const MyString& creatorName, const MyString& description, unsigned creatorId)
{
	_title = title;
	_creatorName = creatorName;
	_description = description;
	_creatorId = creatorId;
	_topicId = ++_id;
}

bool Topic::isTopic(const MyString& title)
{
	return _title == title;
}

const MyString& Topic::getName() const
{
	return _title;
}

const unsigned Topic::getId() const
{
	return _topicId;
}

void Topic::list() const
{
	size_t size = _posts.getSize();

	if (size == 0)
		std::cout << "No posts!" << std::endl;
	else
	{
		for (size_t i = 0; i < size; i++)
			std::cout << "Q: " << _posts[i].getDescription() << " {Id: " << _posts[i].getId() << "}" << std::endl;
	}
}

void Topic::showInfo() const
{
	std::cout << "Name: " << _title << std::endl
		<< "Description: " << _description << std::endl
		<< "Created by: " << _creatorName << " {Id: " << _creatorId << "}" << std::endl
		<< "Questions asked: " << _posts.getSize();
}

void Topic::post(const MyString& postName, const MyString& postDesc)
{
	_posts.pushBack(Post(postName, postDesc));
}

Post* Topic::p_open(const MyString& postName)
{
	size_t size = _posts.getSize();

	if (size == 0)
		return nullptr;
	//throw std::invalid_argument("There are no posts!");

	for (size_t i = 0; i < size; i++)
	{
		if (_posts[i].getName() == postName)
			return &_posts[i];
	}

	return nullptr;
}

Post* Topic::p_open(unsigned postId)
{
	size_t size = _posts.getSize();

	if (size == 0)
		return nullptr;

	for (size_t i = 0; i < size; i++)
	{
		if (_posts[i].getId() == postId)
			return &_posts[i];
	}

	return nullptr;
}

std::ostream& operator<<(std::ostream& os, const Topic& t)
{
	os << t._creatorName << '\n'
		<< t._description << '\n'
		<< t._title << '\n'
		<< t._topicId << '\n';

	size_t postsSize = t._posts.getSize();

	os << postsSize << '\n';

	for (size_t i = 0; i < postsSize; i++)
		os << t._posts[i];

	return os;
}

std::istream& operator>>(std::istream& is, Topic& t)
{
	is >> t._creatorName >> t._description >> t._title >> t._topicId;

	size_t postsSize;

	is >> postsSize;
		is.ignore();

	for (size_t i = 0; i < postsSize; i++)
	{
		Post p(postsSize);
		is >> p;
		t._posts.pushBack(std::move(p));
	}

	return is;
}
