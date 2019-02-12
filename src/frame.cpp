#include <iostream>

#include "../include/frame.h"


Frame::Frame(Box box, std::string address):
		Container(box, address)
{
	MAKE_ADDRESS(Frame);
}


Frame::Frame(const Frame& frame):
		Container(frame)
{
}


int Frame::i_handle_key(int c) {
	return c;
}
