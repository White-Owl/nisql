_**NISQL**_ (short for Non Interactive SQL) is a tool designed to be used in a scheduled environment. It allows user to connect through ODBC to any database, execute any SQL script, and dump the resultset or multiple resultsets into the file(s).

This tutorial presumes that you already have a RDBMS and ODBC connection to it. So if you have DSN with a name _MyDB_, we can start using _**nisql**_.

The easiest way to use _**nisql**_ is to extract the contents of the table:<br>
`nisql DSN=MyDB TableA out.txt`<br>
That command will create an out.txt file with a contents of _TableA_ in fixed-width format.

You can ask, what should we do if the database server requires login and password? That is also not a problem. Just supply them as you would do in any ODBC application:<br>
`nisql "DSN=MyDB;UID=user;PWD=password" TableA out.txt`<br>
And you can also pass any other ODBC option that way. But for the remaining of the tutorial we would assume your DSN does not require credentials...

If instead of fixed-width format, you want a CSV, to load data into MS Excel, or any other CSV able tool, the difference from the first command would be just the name of the output file:<br>
`nisql DSN=MyDB TableA out.csv`<br>
The same can be done for XML and JSON formats. Just give a proper extension for the output file name.

But what if you want to extract an arbitrary SQL query, instead of the table? Nothing can be simpler:<br>
`nisql DSN=MyDB "select a.f1, b.f2 from TableA a, TableB b where a.pk=b.fk" out.csv`<br>
The only limit is how long the command line you OS and shell can handle. But if you want a really long SQL query with multiple joins, aliases for column names, temporary tables or even built-in DDL - just put all your code into .sql file and run:<br>
`nisql DSN=MyDB very-complicated-script.sql out.csv`

But the main feature of the _**nisql**_ is an ability to handle multiple resultsets at once. For example, you have a task: create a list of customers which a such-and-such, then do aggregation on that list this way, and that way. So essentially you want three reports at once, and you want them all in XML format:<br>
`nisql DSN=MyDB script-with-three-outputs.sql out.xml -f"ROOT=report;SETS=rawdata,firstAggregate,secondAggregate"`<br>
And that would create an XML file like:
<pre>
&lt;report>
    &lt;rawdata>
        &lt;row col1="some" col2="data" col3="1"/>
        &lt;row col1="some" col2="data" col3="2"/>
    &lt;/rawdata>
    &lt;firstAggregate>
        &lt;row group1="thing" total="123"/>
        &lt;row group2="other thing" total="345"/>
    &lt;/firstAggregate>
    &lt;secondAggregate>
        &lt;row group1="different group key 1" total="890"/>
        &lt;row group2="different group key 2" total="573"/>
    &lt;/secondAggregate>
&lt;/report></pre>

But what if you do not know how many resultsets the SQL script will produce? Maybe it is written by someone else? But you still want to dump all those resultsets into CSV files (with column names). Nothing can be easier:<br>
`nisql DSN=MyDB mystery-script.sql out.csv -f"HDR=yes"`<br>
This will create out.csv with the first resultset, out-1.csv with the second resultset, out-2.csv with a third one and it will create as many .csv files as necessary.<br>
And the formatting option _HDR_ will tell _**nisql**_ that you want the first row of each file to contain column names from the corresponding resultset.

Each output format (TXT, CSV, XML, and JSON) have many variants of how they can be written and for each such variant, the _**nisql**_ has an option. Just supply the one you need with a _**-f**_ key and you would have your files in no time, of course if the SQL script is written correctly. If not - the RDBMS you are using will complain with a standard ODBC error codes and messages.
