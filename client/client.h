#pragma once
#ifndef CLIENT
#define CLIENT
#include<string>
#include"boost/asio.hpp"


using namespace boost::asio;

class client
{
public:

	client(const std::string& username, io_context& context) :username_(username), sock(context), started(true) {};

	void Connect(ip::tcp::endpoint& ep);

	void Disconnect();

	void Loop();

	std::string username() const;

private:

	void read_answer();

	size_t read_completion(char* buff, boost::system::error_code& ec, size_t bytes);

	void write_ping();

	void message_hadle();

	void on_login();

	void on_ping(const std::string& msg);

	void on_clients(const std::string& msg);

	void do_ask_clients();

	std::string username_;

	bool started;

	ip::tcp::socket sock;

	size_t already_read;

	char read_buff[1024];

};

#endif // !CLIENT