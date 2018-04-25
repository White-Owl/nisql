#include "nisql.h"

void print_result_as_json(result &row) {
	queue<string> section_names;
	queue<string> row_names;
	string root_name = options["ROOT"];
	if(root_name.empty()) root_name = "root";
	bool should_format = ! is_format_option_on("STREAM");
	bool expect_multiset = options.find("SETS") != options.end();
	bool each_column_at_line = is_format_option_on("FIELDPERLINE");

	if(expect_multiset) {
		istringstream ss(options["SETS"]);
		string next_name;
		while( getline(ss, next_name, ',') ){
			section_names.push(next_name);
		}
	}
	if(options.find("ROWS") != options.end()) {
		istringstream ss(options["ROWS"]);
		string next_name;
		while( getline(ss, next_name, ',') ){
			row_names.push(next_name);
		}
	}

	ofstream ofs(output_file_name);
	ofs << "{ \"" << root_name << "\": [";
	//if(should_format) ofs << "\n";

	int section_count = 0;
	do {
		string section_name;
		string row_name = "row";
		if(expect_multiset || section_count>0) {
			if(section_names.empty()) {
				section_name = "section_" + to_string(section_count);
			} else {
				section_name = section_names.front();
				section_names.pop();
			}
			if(verbose) cout << "Resultset #" << section_count << " into " << section_name << "\n";
			if (section_count > 0) {
				ofs << ", ";
			}
			if (should_format) ofs << "\n";

			if(should_format) ofs << "\t";

			ofs << " {\"" << section_name << "\": ["; //check if closed
			//if(should_format) ofs << "\n";
		}

		if(! row_names.empty()) {
			row_name = row_names.front();
			row_names.pop();
		}


		unsigned long row_count=0;
		while( row.next() ) {
			if (row_count > 0) ofs << ",";
			if(should_format) {
				ofs << "\n\t";
				if(expect_multiset || section_count>0) ofs << "\t";
			}
			/*if (row_name == "row") {
				row_name = "row_"+to_string(row_count);
			}*/
			ofs << "{ \"" << row_name << "\": {";
			if(should_format && each_column_at_line) {
				for(auto col_idx=0; col_idx<row.columns(); col_idx++) {
					if (col_idx > 0) ofs << ',';
					ofs << "\n\t\t";
					if(expect_multiset || section_count>0) ofs << "\t";
					ofs << '"' << row.column_name(col_idx) << "\":";
					ofs << '"' << row.get<nanodbc::string>(col_idx) << '"';
				}
				ofs << "\n\t";
				if(expect_multiset || section_count>0) ofs << "\t";
				ofs << "}"; //end row
			} else {
				for(auto col_idx=0; col_idx<row.columns(); col_idx++) {
					if (col_idx > 0) ofs << ',';
					ofs << '"' << row.column_name(col_idx) << ':' << '"' << row.get<nanodbc::string>(col_idx) << '"';
				}
				ofs << "} "; //end row
			}
			row_count++;
		}
		if(expect_multiset || section_count>0) {
			if(should_format) ofs << "\t";
			ofs << "] }"; //ends section name
			if(should_format) ofs << "\n";
		}

		if(verbose) cout << row_count << " rows written\n";


		section_count++;
	} while (row.next_result());
	ofs << " ]}";
	ofs.close();
}

