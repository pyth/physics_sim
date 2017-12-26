#include "view.h"

#include <QApplication>
#include <iostream>

int main(int argc, char **argv) {
	int num_objects = 100;
	if(argc > 1) {
		int arg = atol(argv[1]);
		if(arg > 1) {
			num_objects = arg;
		}
	}

	QApplication app(argc, argv);

	View gview("Simulation", 1024, 768, num_objects);
	gview.run();

	return 0;
}
