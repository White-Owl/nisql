#ifdef _WIN32
#include <windows.h>
#endif
#include <iostream>

using namespace std;

#ifdef __MAIN__
#define EXTERN
#else
#define EXTERN extern
#endif

EXTERN bool verbose;
EXTERN string connection_string;
EXTERN string requested_query;
EXTERN string output_file_name;
EXTERN string format_options;


bool read_arguments(int argc, char **argv);