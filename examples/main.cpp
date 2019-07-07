#include <iostream>

#include "example_forms.h"
#include "example_2.h"
//#include "example_3.h"
#include "example_jobs.h"


void usage(char* argv0) {
	std::cout << "usage: " << std::endl;
	std::cout << argv0 << " <EXAMPLE>" << std::endl;
	std::cout << std::endl;
	std::cout << "EXAMPLEs are:" << std::endl;
	std::cout << "forms" << std::endl;
	std::cout << "2" << std::endl;
	//std::cout << "3" << std::endl;
	std::cout << "jobs" << std::endl;
}


int main(int argc, char* argv[]) {
	int status;
	
	if (argc != 2) {
		usage(argv[0]);
		return EXIT_FAILURE;
	}
	
	std::string example(argv[1]);
	
	if (example == "forms") {
		status = example_forms(argc, argv);
	}
	else if (example == "2") {
		status = example_2(argc, argv);
	}
	/*else if (example == "3") {
		status = example_3(argc, argv);
	}*/
	else if (example == "jobs") {
		status  = example_jobs(argc, argv);
	}
	else {
		std::cout << "example '" << example << "' not available" << std::endl;
		status = EXIT_FAILURE;
	}
	
	return status;
}

