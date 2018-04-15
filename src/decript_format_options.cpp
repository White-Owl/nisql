#include "nisql.h"

void decript_format_options(const string &format_options) {
	map<string,string> ops;

	// iterate through the string and split it by semicolon
	istringstream ss(format_options);
	string key_value_pair;
	while( getline(ss, key_value_pair, ';') ){
		// split an option into key=value
		int pos_equal = key_value_pair.find('=');
		if(pos_equal < 1) {
			throw runtime_error("option " + key_value_pair + " not understood");
		}

		// Ensure that key is always upper case
		string key = key_value_pair.substr(0, pos_equal);
		transform( key.begin(), key.end(), key.begin(), [](unsigned char c){return toupper(c);});

		// value is case sensitive
		options[ key ] = key_value_pair.substr(pos_equal+1, key_value_pair.size()-pos_equal-1);
	}
}

/// helping function
bool is_format_option_on(const string &key) {
	string value = options[key];
	// make it upper case
	transform(value.begin(), value.end(), value.begin(), [](unsigned char c){return toupper(c);});

	return ((value == "ON") || (value == "TRUE") || (value == "YES") || (value == "1"));
}
