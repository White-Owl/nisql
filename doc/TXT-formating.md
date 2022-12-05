Dump the resultset into a text file with fixed-width columns.

Recognized formating options are:
* HDR - boolean option which defines should the first row of the file contain column names or not? By default - no.
* SETS - comma separated list of additional output files. The first resultset goes into the [output](../wiki/Output_file), the second resultset into the first file mentioned in the SETS, the third file into second file in the SETS, etc.<br>
If SETS has more names when actual resultsets returned - extra would be ignored.<br>
If SETS has fewer names when for each unexpected resultset the name would be constructed in the format output-#.txt. Where "output" is a name of the primary output file. For example:<br>
`nisq DSN=MyDB "select * from Students;select * from Professors; select * from Classes" students.txt -f"Sets=professors.txt"`<br>
Will produce two expected files _students.txt_ and _professors.txt_ (with the data from the first and second resultsets). And the third resultest will go into file _students-2.txt_.

The width of the columns in the file would be the same as column width returned by RDBMS. Please note, that many RDBMS (like MS SQL Server for example), define the computed fields as varchar(255) and the resulting column in the .txt would be 255 characters. You would have to use something like `convert(varchar(10), f1+f2)` if you want to limit the size of the computed field.

If width of the column is less than length of the column name, then length of the column name is used.

Example, assuming we have a table student with columns _sname varchar(30)_ and _age numeric(2)_:<br>
`nisql "DSN=MyDB" "select sname as Name, age as Age from student" out1.txt -v -f"hdr=on"`<br>
Can produce an out1.txt with a contents:
<pre> Name                           Age
 Maria White                     21
 Charles Harris                  22
 Susan Martin                    20
 Joseph Thompson                 19
 Christopher Garcia              20</pre>
