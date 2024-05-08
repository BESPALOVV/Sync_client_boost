#include"client.h"
#include<iostream>


int main()
{
	io_context context;

	ip::tcp::endpoint ep(ip::make_address_v4("127.0.0.1"), 1313);

	client cl("Alex", context);
	while (true)
	{
		try {
			std::cout << "Try to connect" << std::endl;

			cl.Connect(ep);

			cl.Loop();
		}
		catch (boost::system::error_code& ec)
		{
			if (ec.value() == 10056)
			{
				cl.Disconnect();
				std::cout << "Disconnect" << std::endl;
			}



		}
	}


	return 0;
}