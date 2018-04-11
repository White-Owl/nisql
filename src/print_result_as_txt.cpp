#include "nisql.h"

void print_result_as_txt(result &row) {
	ofstream ofs(output_file_name);

	if(options["HDR"]=="ON") {
		for(auto col_idx=0; col_idx<row.columns(); col_idx++) {
			if(col_idx>0) ofs << ' '; // separator between columns
			ofs << std::left << std::setw(row.column_size(col_idx))
			    << row.column_name(col_idx);
		}
		ofs << "\n";
	}

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
	}
	ofs.close();
}

