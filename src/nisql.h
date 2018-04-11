#ifdef _WIN32
#include <windows.h>
#endif
#include <iostream>
#include <fstream>
#include <iomanip>
#include <locale>
#include <map>
#include <sql.h>
#include "nanodbc/nanodbc.h"

using namespace std;
using namespace nanodbc;

#ifdef __MAIN__
#define EXTERN
#else
#define EXTERN extern
#endif

EXTERN bool verbose;
EXTERN string connection_string;
EXTERN string requested_query;
EXTERN string output_file_name;
EXTERN map<string,string> options;


bool read_arguments(int argc, char **argv);
void decript_format_options(const string&);

void print_result_as_txt(nanodbc::result &);
void print_result_as_csv(nanodbc::result &);
void print_result_as_xml(nanodbc::result &);
void print_result_as_json(nanodbc::result &);

