#define __MAIN__
#include "nisql.h"


int main(int argc, char **argv) {
	try {
		/// read command-line arguments and put them into
		/// several global variables
		if(! read_arguments(argc, argv) ) return 1;
		if(verbose) for(auto const& kv : options) {
			cout << kv.first << " = " << kv.second << "\n";
		}

		string sql_query; // buffer for the real query
		/// open connection to the database
		/// if failed - it will throw an exception
		connection conn(connection_string);

		/// decipher what is requested
		if( requested_query.size()>4 && requested_query.compare(requested_query.size()-4, 4, ".sql")==0 ) {
			/// Check if requested query is a .sql script - read it
			ifstream sql_script(requested_query, ios::binary | ios::ate);
			auto script_size = sql_script.tellg();
			sql_query.reserve(script_size);
			sql_script.seekg(0);
			sql_script.read(&(sql_query[0]), script_size);
		} else {
			/// The requested query was not .sql script.
			/// Search the requested string in catalogues
			catalog cat(conn);

			/// many databases can address object by up to three pieces which
			/// are translated in ODBC into catalog.schema.name
			string catalog_name, schema_name, object_name;
			/// so before scanning catalogs we need to split the requested
			/// query into those pieces
			auto rpos = requested_query.size();
			do {
				auto pos = requested_query.rfind('.', --rpos);
				if(object_name.empty()) {
					object_name = requested_query.substr(pos+1, rpos-pos);
				} else if(schema_name.empty()) {
					schema_name = requested_query.substr(pos+1, rpos-pos);
				} else {
					catalog_name = requested_query.substr(pos+1, rpos-pos);
				}
				rpos = pos;
			} while (rpos != string::npos);
			if(verbose) cout << "Searching for " <<catalog_name<<'.'<<schema_name<<'.'<<object_name<<"\n";

			auto tab = cat.find_tables(object_name, string(), schema_name, catalog_name);
			if(tab.next()) {
				/// sucessfuly found a table or view
				sql_query = "select * from " + requested_query;
				if(verbose) cout << "Found in TABLES: "
				                 << tab.table_catalog() << '.'
				                 << tab.table_schema() << '.'
				                 << tab.table_name() << ' '
				                 << tab.table_type() << "\n";
			}


			if(sql_query.empty()) {
				/// we did not find the object in tables or views
				/// check the list of procerures
				auto proc = cat.find_procedures(object_name, schema_name, catalog_name);
				if (proc.next()) {
					/// sucessfuly found a table or view
					sql_query = "execute " + requested_query;
					if(verbose) cout << "Found in PROCEDURES: "
				                         << proc.procedure_catalog() << '.'
					                 << proc.procedure_schema() << '.'
					                 << proc.procedure_name() << ' '
					                 << proc.procedure_type() << "\n";
				}
			}
		}

		if(sql_query.empty()) {
			/// we did not find the text from requested_query in database
			/// catalogues of objects.
			/// It is also not a script file. Therefore, assume it to be
			/// a direct query.
			sql_query = requested_query;
		}

		if(verbose) cout << "Actual query is:\n" << sql_query << "\n";

		result first_row = execute( conn, sql_query );

		string extention = output_file_name.substr(output_file_name.size()-4,4);
		if(extention == ".txt") {
			print_result_as_txt(first_row);
/*		} else if(extention == ".csv") {
			print_result_as_csv(first_row);
		} else if(extention == ".xml") {
			print_result_as_xml(first_row);
		} else if(extention == ".json") {
			print_result_as_json(first_row); */
		}

/*        result row = execute(
            conn,
            NANODBC_TEXT("SELECT CustomerID, ContactName, Phone"
                         "   FROM CUSTOMERS"
                         "   ORDER BY 2, 1, 3"));

        for (int i = 1; row.next(); ++i) {
            cout << i << " :"
                 << row.get<nanodbc::string>(0) << " "
                 << row.get<nanodbc::string>(1) << " "
                 << row.get<nanodbc::string>(2) << " " << endl;*/
        return EXIT_SUCCESS;
    }
    catch (runtime_error const& e) {
        cerr << e.what() << endl;
    }
    return EXIT_FAILURE;


//	return 0;
}
