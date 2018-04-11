#include <iostream>
#include <sstream>
#include "nisql.h"

void decript_format_options(const string &format_options) {
	map<string,string> ops;

	istringstream ss(format_options);
	string key_value_pair;
	while( getline(ss, key_value_pair, ';') ){
		int pos_equal = key_value_pair.find('=');
		if(pos_equal < 1) {
			throw runtime_error("option " + key_value_pair + " not understood");
		}
		options[ key_value_pair.substr(0, pos_equal) ] = key_value_pair.substr(pos_equal+1, key_value_pair.size()-pos_equal-1);
	}
}
