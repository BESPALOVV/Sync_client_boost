#include"boost/asio.hpp"
#include"boost/thread.hpp"
#include"boost/system.hpp"
#include <iostream>
#include "client.h"
using namespace boost::asio;


void client::Connect(ip::tcp::endpoint& ep)
{
	sock.connect(ep);
}

void client::Disconnect()
{
	sock.close();
}

void client::Loop()
{
	sock.write_some(buffer("login " + username_ + '\n'));

	read_answer();

	while (started)
	{
		try {
			write_ping();

			std::cout << "Client was ping" << std::endl;

			read_answer();

			boost::this_thread::sleep_for(boost::chrono::milliseconds(rand() % 7000));
		}
		catch (boost::system::error_code& ec)
		{
			throw ec;
		}

	}

}

std::string client::username() const { return username_; }

void client::read_answer()
{
	std::cout << "read started" << std::endl;
	already_read = 0;

	read(sock, buffer(read_buff, 1024), boost::bind(&client::read_completion, this, read_buff, boost::placeholders::_1, boost::placeholders::_2));

	message_hadle();
	std::cout << "read stoped" << std::endl;
}

size_t client::read_completion(char* buff, boost::system::error_code& ec, size_t bytes)
{
	if (ec) { return 0; }
	bool found = std::find(buff, buff + bytes, '\n') < buff + bytes;
	already_read = bytes;
	return found ? 0 : 1;
}

void client::write_ping()
{
	write(sock, buffer("ping\n", 5));
}

void client::message_hadle()
{
	std::string answer(read_buff, read_buff + already_read);

	std::cout << "ANSWER FROM SERVER" << answer << std::endl;

	if (answer.find("login") == 0) { on_login(); }

	else if (answer.find("ping") == 0) { on_ping(answer); }

	else if (answer.find("clients") < 3) { on_clients(answer); }

	else { std::cerr << "invalid answer from server:: " << answer << std::endl; }
}

void client::on_login() { do_ask_clients(); }

void client::on_ping(const std::string& msg)
{
	std::istringstream in(msg);

	std::string answer;

	in >> answer >> answer;

	if (answer == "client_list_changed")
	{
		do_ask_clients();
	}
}

void client::on_clients(const std::string& msg)
{
	std::string clients = msg.substr(8);

	std::cout << username_ << ", new client list:" << clients;

}

void client::do_ask_clients()
{
	write(sock, buffer("ask_clients\n", 12));

	read_answer();
}







