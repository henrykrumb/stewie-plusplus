#include <iostream>

#include "../include/frame.h"


Frame::Frame(Box box, std::string address):
		Container(box, address)
{
	MAKE_ADDRESS(Frame);
}


int Frame::i_handle_key(int c) {
	return c;
}
