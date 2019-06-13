#include <iostream>

#include "example_1.h"


void usage(char* argv0) {
	std::cout << "usage: " << std::endl;
	std::cout << argv0 << " <EXAMPLE>" << std::endl;
	std::cout << std::endl;
	std::cout << "EXAMPLEs are:" << std::endl;
	std::cout << "1" << std::endl;
}


int main(int argc, char* argv[]) {
	int status;
	
	if (argc != 2) {
		usage(argv[0]);
		return EXIT_FAILURE;
	}
	
	std::string example(argv[1]);
	
	if (example == "1") {
		status = example_1(argc, argv);
	}
	else {
		std::cout << "example '" << example << "' not available" << std::endl;
		status = EXIT_FAILURE;
	}
	
	return status;
}

