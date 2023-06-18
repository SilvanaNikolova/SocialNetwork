#include "Engine.h"
#include "HelperFunctions.h"

void signin(System& s)
{
	std::cout << "Enter first name: ";
	std::cin.ignore();
	char firstname[1024];
	std::cin.getline(firstname, 1024);

	std::cout << "Enter last name: ";
	char lastName[1024];
	std::cin.getline(lastName, 1024);

	std::cout << "Enter password: ";
	char pass[1024];
	std::cin.getline(pass, 1024);

	if (s.signin(firstname, lastName, pass))
		std::cout << "Success!";
}

void login(System& s)
{
	std::cout << "Name: ";
	char name[1024];
	std::cin.ignore();
	std::cin.getline(name, 1024);

	std::cout << "Password: ";
	char pass[1024];
	std::cin.getline(pass, 1024);

	if (s.login(name, pass))
		std::cout << "Welcome back, " << name << "!";
}

void createTopic(System& s)
{
	std::cout << "Enter topic title: ";
	char title[1024];
	std::cin.ignore();
	std::cin.getline(title, 1024);

	std::cout << "Enter topic description: ";
	char desc[1024];
	std::cin.getline(desc, 1024, '\n');

	if (s.createTopic(title, desc))
		std::cout << "Success!";
}

void searchTopic(const MyString& text, System& s)
{
	s.searchTopic(text);
}

void openTopicWithId(unsigned id, System& s)
{
	s.openTopic(id);
}

void openTopicWithTitle(const MyString& title, System& s)
{
	s.openTopic(title);
}

void list(System& s)
{
	s.listTopic();
}

void post(System& s)
{
	std::cout << "Enter post title: ";
	char name[1024];
	std::cin.ignore();
	std::cin.getline(name, 1024, '\n');

	std::cout << "Enter your question: ";
	char desc[1024];
	std::cin.getline(desc, 1024, '\n');

	if (s.post(name, desc))
		std::cout << "Posted!";
}

void openPostWithId(unsigned id, System& s)
{
	s.openPost(id);
}

void openPostWithTitle(const MyString& title, System& s)
{
	s.openPost(title);
}

void comment(System& s)
{
	std::cout << "Enter comment: ";
	char comment[1024];
	std::cin.ignore();
	std::cin.getline(comment, 1024);

	if (s.commentPost(comment))
		std::cout << "Posted!";
}

void comments(System& s)
{
	s.listComments();
}

void replyComment(unsigned id, System& s)
{
	std::cout << "Enter reply: ";
	char reply[1024];
	std::cin.ignore();
	std::cin.getline(reply, 1024);

	if (s.replyToComment(reply, id))
		std::cout << "Posted!";
}


void upvoteComment(unsigned id, System& s)
{
	s.upvoteComment(id);
}

void downvoteComment(unsigned id, System& s)
{
	s.downvoteComment(id);
}

void p_close(System& s)
{
	s.quitPost();
}

void quit(System& s)
{
	s.quitTopic();
}

void logout(System& s)
{
	if (!s.logout())
		std::cout << "There is no active user rigth now!";
}

void exit(System& s)
{
	std::cout << "Exiting...";
	s.exit();
}

void whoami(System& s)
{
	s.getUserInfo();
}

void about(unsigned id, System& s)
{
	s.getTopicInfo(id);
}

void printCommands()
{
	std::cout << "Commands:" << std::endl << "signin - creates a profile" << std::endl
		<< "login - enter the system with your name and password" << std::endl
		<< "logout - end access to the system" << std::endl
		<< "create - creates a topic" << std::endl
		<< "search <text> - shows all topics that include this text" << std::endl
		<< "open <title> - opens a topic with this title" << std::endl
		<< "open <id> - opens a topic with this id" << std::endl
		<< "post - creates a post for an open topic" << std::endl
		<< "p_open <title> - opens a post with this title" << std::endl
		<< "p_open <id> - opens a post with this id" << std::endl
		<< "list - display all the posts for the current topic" << std::endl
		<< "comment - adds a comment to an open post" << std::endl
		<< "comments - displays all the comments for an open post" << std::endl
		<< "reply <id> - replies to a comment to an open post" << std::endl
		<< "upvote <id> - like comment" << std::endl
		<< "downvote <id> - dislike comment" << std::endl
		<< "p_close - closes current post" << std::endl
		<< "quit - closes current topic" << std::endl
		<< "exit - closes the system" << std::endl
		<< "whoami - displays information about the user" << std::endl
		<< "about <id> - displays information about topic with this id" << std::endl;
}


void run()
{
	System s;

	std::cout << "Welcome to Sisinger!" << "In order to start the program please choose a valid command!" << std::endl;

	printCommands();

	MyString secondArg;
	unsigned idArg;

	while (true)
	{
		std::cout << "Enter command: ";
		char firstArg[1024];
		std::cin >> firstArg;

		if (strcmp(firstArg, "signin") == 0)
			signin(s);
		else if (strcmp(firstArg, "login") == 0)
			login(s);
		else if (strcmp(firstArg, "logout") == 0)
			logout(s);
		else if (strcmp(firstArg, "create") == 0)
			createTopic(s);
		else if (strcmp(firstArg, "search") == 0)
		{
			std::cin.ignore();
			std::cin >> secondArg;
			searchTopic(secondArg, s);
		}
		else if (strcmp(firstArg, "open") == 0)
		{
			std::cin.ignore();
			std::cin >> secondArg;

			if (isDigit(secondArg))
			{
				unsigned id = convertToDigit(secondArg);

				openTopicWithId(id, s);
			}
			else
				openTopicWithTitle(secondArg, s);

		}
		else if (strcmp(firstArg, "post") == 0)
			post(s);
		else if (strcmp(firstArg, "p_open") == 0)
		{
			std::cin.ignore();
			std::cin >> secondArg;

			if (isDigit(secondArg))
			{
				unsigned id = convertToDigit(secondArg);
				openPostWithId(id, s);
			}
			else
				openPostWithTitle(secondArg, s);
		}
		else if (strcmp(firstArg, "list") == 0)
			list(s);
		else if (strcmp(firstArg, "comment") == 0)
			comment(s);
		else if (strcmp(firstArg, "comments") == 0)
			comments(s);
		else if (strcmp(firstArg, "reply") == 0)
		{
			std::cin.ignore();
			std::cin >> secondArg;

			if (!isDigit(secondArg))
				std::cout << "Commentd id must be a digit! Please choose a valid command!";
			else {
				idArg = convertToDigit(secondArg);
				replyComment(idArg, s);
			}
		}
		else if (strcmp(firstArg, "upvote") == 0)
		{
			std::cin.ignore();
			std::cin >> secondArg;

			if (!isDigit(secondArg))
				std::cout << "Commentd id must be a digit! Please choose a valid command!";
			else {
				idArg = convertToDigit(secondArg);
				upvoteComment(idArg, s);
			}
		}
		else if (strcmp(firstArg, "downvote") == 0)
		{
			std::cin.ignore();
			std::cin >> secondArg;

			if (!isDigit(secondArg))
				std::cout << "Commentd id must be a digit! Please choose a valid command!";
			else {
				idArg = convertToDigit(secondArg);
				downvoteComment(idArg, s);
			}
		}
		else if (strcmp(firstArg, "p_close") == 0)
			p_close(s);
		else if (strcmp(firstArg, "quit") == 0)
			quit(s);
		else if (strcmp(firstArg, "exit") == 0)
		{
			exit(s);
			return;
		}
		else if (strcmp(firstArg, "whoami") == 0)
			whoami(s);
		else if (strcmp(firstArg, "about") == 0)
		{
			std::cin.ignore();
			std::cin >> secondArg;

			if (!isDigit(secondArg))
				std::cout << "Commentd id must be a digit! Please choose a valid command!";
			else {
				idArg = convertToDigit(secondArg);
				about(idArg, s);
			}
		}
		else {
			std::cout << "Invalid command! Choose between these valid commands!" << std::endl;
			printCommands();
		}
		std::cout << std::endl;
		std::cout << "-----------------------------";
		std::cout << std::endl;
	}
};