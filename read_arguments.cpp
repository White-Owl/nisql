#include "nisql.h"

static void show_usage() {
	cout << "Usage: nisql conn query file [options]\n"
	     << "\tconn\tODBC connection string (i.e. DSN=mydb)\n"
	     << "\tquery\tCan be name of table, view, stored prcedure\n"
	     << "\t\tor direct SQL query (i.e. select f1,f5 from sometable where pk=1)\n"
	     << "\t\tor name of the file with queries. Have to have .sql extention\n"
	     << "\tfile\tname of the output file. Have to have one of the known\n"
	     << "\t\textentions: txt, csv, xml, json\n"
	     << "Options:\n"
	     << "\t-?, -h\t\tShow this help message\n"
	     << "\t-v\t\tEnable verbose mode\n"
	     << "\t-f format\tDefine formatting opttions, separated by ';'\n"
	     << "Options for TXT format:\n"
	     << "\tHDR=ON|OFF\tPrint column headers (ON)\n"
	     << "Options for CSV format:\n"
	     << "\tHDR=ON|OFF\tPrint column headers (ON)\n"
	     << "\tFLD=text\tSet field deilimiter, use hex codes for special characters (\\09)\n"
	     << "\tREC=text\tSet record deilimiter (\\0D\\0A on windows, \\0A on Linux)\n"
	     << "\tQUO=ON|OFF\tQuote text fields always (Off)\n"
	     << "\tFILE=text[;text]\tName of output files for multiple resultests\n"
	     << "Options for XML format:\n"
	     << "\tSTR=ON|OFF\tWrite XML into one stream or format it (ON)\n"
	     << "\tFLD=ON|OFF\tPrint fileds as tags (for ON) or values (for OFF) (default ON)\n"
	     << "\tROOT=text\tName for the XML's root (default 'data')\n"
	     << "\tSET=text[;text]\tName(s) of the recordset(s), for multiset queries\n"
	     << "\tRECORD=text[;text]\tName(s) for row element in recordset(s)(default 'record')\n"
	     << "Options for JSON format:\n"
	     << "\n"
	     << "\nExamples:\n"
	     << "  nisql -v DSN=MyDb1 Table1 out.txt -fHDR=off\n\n"
	     << "  nisql \"DSN=MyDb2;UID=jim;PWD=123\"\n"
	     << "        \"select f1,f5 from sales where customer='mary'\"\n"
	     << "        mary-sales.csv -f \"HDR=on;fld=,\"\n"
	     << endl;
}

bool read_arguments(int argc, char **argv) {
	for(int argn=1; argn<argc; argn++) {
		if(argv[argn][0] == '-' && argv[argn][1]) {
			char key = argv[argn][1];
			char *parameter_value = nullptr;

			/// First, check does the argument starts with a '-'
			/// and does it have something after it? If yes, assume
			/// this as an option
			switch(key) {
			case '?': case 'h':
				show_usage();
				return false;
			case 'v': verbose = true; break;
			case 'f':
				/// find parameter for the key f
				if (argv[argn][2]) {
					parameter_value = &(argv[argn][2]);
				} else if((argn+1)<argc) {
					if(argv[argn+1][0] != '-')
						parameter_value = argv[++argn];
				}
				if(parameter_value == nullptr) {
					cerr << "Key -f requires parameter\n\n";
					show_usage();
					return false;
				}
				format_options = parameter_value;
				break;
			default:
				cerr << "Unkown key -" << key << "\n";
				show_usage();
				return false;
			}

		} else {
			/// The argument is not in a form "-X", so treat this as a
			/// positional argument.
			/// And we expect three arguments: connection, query, file
			if(connection_string.empty()) {
				connection_string = argv[argn];
			} else if(requested_query.empty()) {
				requested_query = argv[argn];
			} else if(output_file_name.empty()) {
				output_file_name = argv[argn];
			} else {
				cerr << "Too many operands\n";
				show_usage();
				return false;
			}
		}
	}
	if(output_file_name.empty()) {
		cerr << "Not enough operands\n";
		show_usage();
		return false;
	}
	return true;
}
