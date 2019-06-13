#include "utils.h"


Dimension stringsize(std::string str) {
	int w = 0;
	int h = 0;
	
	if (!str.empty()) {
		h = 1;
	}
	
	int x = 0;
	for (auto it = str.begin(); it != str.end(); ++it) {
		if (*it == '\n') {
			h += 1;
			x = 0;
		}
		else {
			x += 1;
			if (w < x) {
				w = x;
			}
		}
	}
	
	return Dimension(w, h);
}
