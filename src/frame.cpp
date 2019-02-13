#include <iostream>

#include "frame.h"


Frame::Frame(std::string address):
		Container(address)
{
	MAKE_ADDRESS(Frame);
}


void Frame::pack() {
	
}


int Frame::handle_key(int c) {
	return c;
}
