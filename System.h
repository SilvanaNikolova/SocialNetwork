#pragma once
#include "MyString.h"
#include "Vector.hpp"
#include "User.h"
#include "Topic.h"
#include "Post.h"

const char USERS_FILE[] = "users.txt";
const char TOPICS_FILE[] = "topics.txt";

class System
{
	Vector<User> _users;
	Vector<Topic> _topics;
	User* _currentUser = nullptr;
	Topic* _currentTopic = nullptr;
	Post* _currentPost = nullptr;

	//Comment* _currentComment = nullptr;
	//bool _isLoggedIn = false;

public:
	System();

	bool signin(const MyString&, const MyString&, const MyString&);
	bool login(const MyString&, const MyString&);

	void searchTopic(const MyString&) const;
	bool createTopic(const MyString&, const MyString&);

	void openTopic(const MyString&);
	void openTopic(unsigned);
	void listTopic() const;

	bool post(const MyString&, const MyString&) const;
	void openPost(const MyString&);
	void openPost(unsigned);

	bool commentPost(const MyString&) const;
	void listComments() const;//
	bool replyToComment(const MyString&, unsigned);
	void downvoteComment(unsigned);
	void upvoteComment(unsigned);

	void quitPost();
	void quitTopic();
	bool logout();
	void exit();

	void getUserInfo() const;
	void getTopicInfo(unsigned) const;

	void readUsersFromFile();
	void readTopicsFromFile();

	void saveUsersToFile() const;
	void saveTopicsToFile() const;

	void saveUserToFile(const User&) const;
	void saveTopicToFile(const Topic&) const;
};