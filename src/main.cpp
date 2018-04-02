#define __MAIN__
#include "nisql.h"


int main(int argc, char **argv) {
	if(! read_arguments(argc, argv) ) return 1;


	cout << "ready to work\n";


	return 0;
}
