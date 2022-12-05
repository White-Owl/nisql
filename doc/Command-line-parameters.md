The NISQL expects three necessary parameters and two optional ones.

&nbsp;&nbsp;&nbsp;  nisql connection query output [options]

The necessary parameters are:
* [connection](../wiki/Connection-string) - A connection string in ODBC format
* [query](../wiki/Query) - A name of the SQL script, a direct select statement, or just a name of a database object (table or view).
* [output](../wiki/Output-file) - A name of the file into which the data should be written. The extension of the output file defines the format of the dump.

Optional parameters are:
- -v - Enable verbose messages (by default off)
- -f"text" - How to style the output, the format of the text is following the ODBC's format of the connections string: "Key1=val1;Key2=val2".


Typical usage is:<br>
`nisql DSN=MyDB "select * from tableA where PK=123" out.csv -f"HDR=yes"`<br>
Which would dump the contents of tableA filtered by criteria PK=123, into file with CSV format, and the first row in that file would contain column names from the tableA.