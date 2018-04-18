#include "nisql.h"

void print_result_as_json(result &row) {
	queue<string> file_names;
	file_names.push(output_file_name);
	if(options.find("SETS") != options.end()) {
		istringstream ss(options["SETS"]);
		string next_name;
		while( getline(ss, next_name, ',') ){
			file_names.push(next_name);
		}
	}


	int file_count = 0;
	do {
		string file_name;
		if(file_names.empty()) {
			file_name = output_file_name.substr(0, output_file_name.size()-4) + '_' + to_string(file_count) + ".json";
		} else {
			file_name = file_names.front();
			file_names.pop();
		}
		if(verbose) cout << "Resultset #" << file_count << " into " << file_name << "\n";
		ofstream ofs(file_name);

		ofs << "{ \"result\": ";
		unsigned long row_count=0;
		while( row.next() ) {
			if (row_count > 0) ofs << ",\n";
			ofs << "[ ";
			for(auto col_idx=0; col_idx<row.columns(); col_idx++) {
				if(col_idx>0) ofs << ", "; // separator between columns
				ofs << row.column_name(col_idx) << ':' << '"' << row.get<nanodbc::string>(col_idx) << '"';
			}
			ofs << "] ";
			row_count++;
		}
		ofs << "} ";
		ofs.close();
		if(verbose) cout << row_count << " rows written\n";


		file_count++;
	} while (row.next_result());
}

