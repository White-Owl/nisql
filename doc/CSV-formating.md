Dump the resultset into a text file with comma-separated fields.

Recognized formating options are:
* HDR - boolean option which defines should the first row of the file contain column names or not? By default - no.

* SETS - comma separated list of additional output files. The first resultset goes into the [output](../wiki/Output_file), the second resultset into the first file mentioned in the SETS, the third file into second file in the SETS, etc.<br>
If SETS has more names when actual resultsets returned - extra would be ignored.<br>
If SETS has fewer names when for each unexpected resultset the name would be constructed in the format output_#.csv. Where "output" is a name of the primary output file. For example:<br>
`nisq DSN=MyDB "select * from Students;select * from Professors; select * from Classes" students.csv -f"Sets=professors.csv"`<br>
Will produce two expected files _students.csv_ and _professors.csv_ (with the data from the first and second resultsets). And the third resultest will go into file _students_2.csv_.

* DELIM - a string which should separate fields in a row. By default ",". Use "\t" to split fields by TAB.

* QUOTE - boolean option, should we put text fields in double-quote always or not (default no). By CSV standards, the field is quoted if the text contains the delimiter inside, but otherwise the text is printed into the file as is. This option will force all text fields to be quoted always.

Example, assuming we have a table student with columns _sname varchar(30)_ and _age numeric(2)_:<br>
`nisql "DSN=MyDB" "select sname as Name, age as Age from student" out1.csv -f"hdr=on;delim=|"`<br>
Can produce an out1.csv with a contents:
<pre> Name|Age
 Maria White|21
 Charles Harris|22
 Susan Martin|20
 Joseph Thompson|19
 Christopher Garcia|20</pre>
