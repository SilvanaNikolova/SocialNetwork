#include "System.h"

System::System()
{
	readUsersFromFile();
	readTopicsFromFile();
}

bool System::signin(const MyString& firstName, const MyString& lastName, const MyString& password)
{
	size_t size = _users.getSize();

	for (size_t i = 0; i < size; i++)
	{
		if (_users[i].isUser(firstName, lastName, password))
		{
			std::cout << "There is already such user!";
			return false;
		}
	}

	User u(firstName, lastName, password);
	_users.pushBack(std::move(u));
	return true;
}

bool System::login(const MyString& firstName, const MyString& password)
{
	size_t count = _users.getSize();

	for (size_t i = 0; i < count; i++)
	{
		if (_users[i].isUser(firstName, password))
		{
			_currentUser = (&_users[i]);
			return true;
		}
	}

	if (!_currentUser)
		std::cout << "User not found!";
	return false;
}

void System::searchTopic(const MyString& topicName) const
{
	size_t size = _topics.getSize();

	if (size == 0)
	{
		std::cout << "There are no topics with title: " << topicName << "!";
		return;
	}

	for (size_t i = 0; i < size; i++)
	{
		if (_topics[i].getName().contains(topicName))
			std::cout << "-" << _topics[i].getName() <<
			" {Id:" << _topics[i].getId() << "}" << std::endl;
	}
}

bool System::createTopic(const MyString& title, const MyString& description)
{
	if (!_currentUser)
	{
		std::cout << "You should be logged in in order to create a topic!";
		return false;
	}

	size_t size = _topics.getSize();

	for (size_t i = 0; i < size; i++)
	{
		if (_topics[i].isTopic(title))
		{
			std::cout << "There is already topic with title: " << title << "!";
			return false;
		}
	}

	Topic t(title, _currentUser->getName(), description, _currentUser->getId());
	_topics.pushBack(std::move(t));
	return true;
}

void System::openTopic(const MyString& topicName)
{
	size_t size = _topics.getSize();

	for (size_t i = 0; i < size; i++)
	{
		if (_topics[i].getName() == topicName)
		{
			_currentTopic = (&_topics[i]);
		}
	}

	if (!_currentTopic)
	{
		std::cout << "There is no topic with title: " << topicName << "!";
		return;
	}

	std::cout << "Welcome to \"" << _currentTopic->getName() << "\"!" << std::endl;
}

void System::openTopic(unsigned topicId)
{
	size_t size = _topics.getSize();

	for (size_t i = 0; i < size; i++)
	{
		if (_topics[i].getId() == topicId)
		{
			_currentTopic = (&_topics[i]);
		}
	}

	if (!_currentTopic)
	{
		std::cout << "There is no topic with id: " << topicId << "!";
		return;
	}

	std::cout << "Welcome to \"" << _currentTopic->getName() << "\"!" << std::endl;
}

void System::listTopic() const
{
	if (!_currentTopic)
	{
		std::cout << "You should open a topic in order to see its posts!";
		return;
	}

	_currentTopic->list();
}

bool System::post(const MyString& postName, const MyString& postDesc) const
{
	if (!_currentTopic)
	{
		std::cout << "You should open a topic in order to create a post for it!";
		return false;
	}

	_currentTopic->post(postName, postDesc);
	return true;
}

void System::openPost(const MyString& postName)
{
	if (!_currentTopic)
	{
		std::cout << "You should open a topic in order to open its posts!";
		return;
	}

	_currentPost = _currentTopic->p_open(postName);

	if (!_currentPost)
	{
		std::cout << "There is no posts with title: " << postName << "!";
		return;
	}

	std::cout << "Q: " << _currentPost->getDescription() << std::endl;
}

void System::openPost(unsigned postId)
{
	if (!_currentTopic)
	{
		std::cout << "You should open a topic in order to open its posts!";
		return;
	}

	_currentPost = _currentTopic->p_open(postId);

	if (!_currentPost)
	{
		std::cout << "There is no posts with id: " << postId << "!";
		return;
	}

	std::cout << "Q: " << _currentPost->getDescription() << std::endl;
}

bool System::commentPost(const MyString& comment) const
{
	if (!_currentPost)
	{
		std::cout << "You should open a post in order to add a comment fot it!";
		return false;
	}

	//throw std::logic_error("No active post!");

	_currentPost->comment(comment, _currentUser->getName());
	_currentUser->addPoint();
	return true;
}

void System::listComments() const
{
	if (!_currentPost)
	{
		std::cout << "You should open a post in order to see its comments!";
		return;
	}
	//throw std::logic_error("No active post!");

	_currentPost->showComments();
}

bool System::replyToComment(const MyString& reply, unsigned commentId)
{
	if (!_currentPost)
	{
		std::cout << "You should open a post in order to reply to a comment!";
		return false;
	}
	//throw std::logic_error("Post not found!");

	_currentPost->reply(commentId, reply);
	return true;
}

void System::downvoteComment(unsigned commentId)
{
	if (!_currentPost)
	{
		std::cout << "You should open a post in order to react to a comment!";
		return;
	}
	//throw std::logic_error("Post not found!");

	bool isRated = _currentUser->addRating(commentId);

	_currentPost->downvote(commentId, isRated);
}

void System::upvoteComment(unsigned commentId)
{
	if (!_currentPost)
	{
		std::cout << "You should open a post in order to react to a comment!";
		return;
	}
	//throw std::logic_error("Post not found!");

	bool isRated = _currentUser->addRating(commentId);

	_currentPost->upvote(commentId, isRated);
}

void System::quitPost()
{
	if (!_currentPost)
	{
		std::cout << "There is no open post rigth now!" << std::endl;
		return;
	}

	std::cout << "You just left " << _currentPost->getName() << "!" << std::endl;

	//delete _currentPost; ???????
	_currentPost = nullptr;
}

void System::quitTopic()
{
	if (!_currentTopic)
	{
		std::cout << "There is no open topic rigth now!" << std::endl;
		return;
	}

	std::cout << "You just left topic " << _currentTopic->getName() << "!" << std::endl;


	_currentTopic = nullptr;
	_currentPost = nullptr;
}

bool System::logout()
{
	if (!_currentUser)
		return false;

	std::cout << "Goodbye, " << _currentUser->getName() << "!" << std::endl;

	_currentPost = nullptr;
	_currentTopic = nullptr;
	_currentUser = nullptr;
	return true;
}

void System::exit()
{
	_currentPost = nullptr;
	_currentTopic = nullptr;
	_currentUser = nullptr;

	saveUsersToFile();
	saveTopicsToFile();
}

void System::getUserInfo() const
{
	if (!_currentUser)
	{
		std::cout << "There is no active user rigth now!";
		return;
	}
	//throw std::logic_error("There is no active user rigth now!");

	std::cout << _currentUser->getName() << " having " << _currentUser->getPoints() << " points!";
}

void System::getTopicInfo(unsigned topicID) const
{
	if (!_currentUser)
	{
		std::cout << "You should be logged in in order to see the topic information!";
		return;
	}
	//throw std::logic_error("There is no active user rigth now!");

	size_t size = _topics.getSize();
	bool exists = false;

	for (size_t i = 0; i < size; i++)
	{
		if (_topics[i].getId() == topicID)
		{
			_topics[i].showInfo();
			exists = true;
		}
	}

	if (!exists)
	{
		std::cout << "There is no topic with id: " << topicID << "!";
		return;
	}
	//throw std::logic_error("There is no such topic");
}

void System::readUsersFromFile()
{
	std::ifstream is(USERS_FILE, std::ios::in);

	if (!is.is_open())
		throw std::runtime_error("File not open!");

	//is.ignore();

	//is.get();

	//if (is.eof())
	//{
	//	is.close();
	//	return;
	//}

	char beg[1024];
	is.getline(beg, 1024);

	if (strcmp(beg, "") == 0)
	{
		is.close();
		return;
	}

	is.seekg(std::ios::beg);

	//is.ignore('\n');

	//int usersCount = 0;
	//bool isUser;

	size_t size;

	is >> size;
	is.ignore();

	for (size_t i = 0; i < size; i++)
	{
		User u(size);
		is >> u;
		_users.pushBack(u);

		is.ignore();
	}

	is.close();

	//while (true)
	//{
	//	if (is.eof())
	//	{
	//		break;
	//	}

	//	User u;

	//	is >> u;

	//	//usersCount = _users.getSize();
	//	//isUser = false;

	//	//for (size_t i = 0; i < usersCount; i++)
	//	//{
	//	//	if (_users[i].isUser(u._firstName, u._lastName, u._password))
	//	//	{
	//	//		_users[i]._points = u._points;
	//	//		_users[i]._commentRatings = u._commentRatings;
	//	//		isUser = true;
	//	//		break;
	//	//	}
	//	//}

	//	//if (u.getName() != "")
	//	//if (!isUser)
	//	_users.pushBack(u);

	//	is.ignore();
	//}

	//is.clear();
	//is.close();
}

void System::readTopicsFromFile()
{
	std::ifstream is(TOPICS_FILE, std::ios::in);

	if (!is.is_open())
		throw std::runtime_error("File not open!");

	//is.ignore();

	//is.get();

	//if (is.eof())
	//{
	//	is.close();
	//	return;
	//}

	//is.seekg(-1);

	char beg[1024];
	is.getline(beg, 1024);

	if (strcmp(beg, "") == 0)
	{
		is.close();
		return;
	}

	is.seekg(std::ios::beg);

	size_t size;

	is >> size;
	is.ignore();

	for (size_t i = 0; i < size; i++)
	{
		Topic t(size);
		is >> t;
		_topics.pushBack(t);

		//is.ignore();
	}

	is.close();

	//while (true)
	//{
	//	if (is.eof())
	//	{
	//		break;
	//	}
	//	Topic t;

	//	is >> t;

	//	//if (t.getName() != "")
	//	_topics.pushBack(t);

	//	//is.get();
	//	is.ignore();
	//	//is.ignore('\n');
	//}


}

void System::saveUsersToFile() const
{
	size_t size = _users.getSize();

	std::ofstream os(USERS_FILE, std::ios::out | std::ios::trunc);

	if (!os.is_open())
		throw std::runtime_error("File not open!");

	os << size << '\n';

	for (size_t i = 0; i < size; i++)
		os << _users[i];
	//saveUserToFile(_users[i]);

	os.close();
}

void System::saveTopicsToFile() const
{
	size_t size = _topics.getSize();

	std::ofstream os(TOPICS_FILE, std::ios::out, std::ios::trunc);

	if (!os.is_open())
		throw std::runtime_error("File not open!");

	os << size << '\n';

	for (size_t i = 0; i < size; i++)
		os << _topics[i];
	//saveTopicToFile(_topics[i]);

	os.close();
}