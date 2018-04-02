#define __MAIN__
#include "nisql.h"


int main(int argc, char **argv) {
	if(! read_arguments(argc, argv) ) return 1;

    try {
        connection conn(connection_string);
        result row = execute(
            conn,
            NANODBC_TEXT("SELECT CustomerID, ContactName, Phone"
                         "   FROM CUSTOMERS"
                         "   ORDER BY 2, 1, 3"));

        for (int i = 1; row.next(); ++i) {
            cout << i << " :"
                 << row.get<nanodbc::string>(0) << " "
                 << row.get<nanodbc::string>(1) << " "
                 << row.get<nanodbc::string>(2) << " " << endl;
        }
        return EXIT_SUCCESS;
    }
    catch (runtime_error const& e) {
        cerr << e.what() << endl;
    }
    return EXIT_FAILURE;


//	return 0;
}
