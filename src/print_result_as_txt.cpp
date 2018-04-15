#include "nisql.h"

void print_result_as_txt(result &row) {
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
			file_name = output_file_name.substr(0, output_file_name.size()-4) + '_' + to_string(file_count) + ".txt";
		} else {
			file_name = file_names.front();
			file_names.pop();
		}
		if(verbose) cout << "Resultset #" << file_count << " into " << file_name << "\n";
		ofstream ofs(file_name);
	
		if(is_format_option_on("HDR")) {
			for(auto col_idx=0; col_idx<row.columns(); col_idx++) {
				if(col_idx>0) ofs << ' '; // separator between columns
				ofs << std::left << std::setw(row.column_size(col_idx))
				    << row.column_name(col_idx);
			}
			ofs << "\n";
		}
	
		unsigned long row_count=0;
		while( row.next() ) {
			for(auto col_idx=0; col_idx<row.columns(); col_idx++) {
				if(col_idx>0) ofs << ' '; // separator between columns
	
				auto col_width = row.column_name(col_idx).size();
				if(col_width < row.column_size(col_idx)) col_width = row.column_size(col_idx);
				auto ct = row.column_datatype(col_idx);
				if( (ct == SQL_NUMERIC) || (ct == SQL_DECIMAL) ||
				    (ct == SQL_INTEGER) || (ct == SQL_SMALLINT) ||
				    (ct == SQL_FLOAT) || (ct == SQL_REAL) || (ct == SQL_DOUBLE)) {
					if(row.column_decimal_digits(col_idx)>0) ofs.precision(row.column_decimal_digits(col_idx));
					ofs << std::right << setw(col_width) << row.get<nanodbc::string>(col_idx);
				} else {
					ofs << std::left << setw(col_width) << row.get<nanodbc::string>(col_idx);
				}
			}
			ofs << "\n";
			row_count++;
		}
		ofs.close();
		if(verbose) cout << row_count << " rows written\n";


		file_count++;
	} while (row.next_result());
	if(verbose) cout << "Done\n";
}

