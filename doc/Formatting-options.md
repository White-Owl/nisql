The formatting options are specific for each format.
But they all follow the same rules as ODBC connection string:

&nbsp;&nbsp;&nbsp; Key1=value1;Key2=value2

* Where keys are case insensitive, and values are case sensitive.

* In some keys (like SETS for TXT and CSV format) we can define several values for one key. Then they are separated by commas. For example:<br>
`nislq DSN=MyDSN "select * from tableA; select * from tableB; select * from table C" a.txt -f"SETS=b.txt,c.txt"`<br>
That means dump the first resultset into file _a.txt_, the second one (from tableB) into _b.txt_ and the last one into the file _c.txt_.<br>
Please refer to the description of corresponding data formatter for explanation of what happens if number of resultsets does not correlate with number of expected sets.

* The boolean options (like include column headers or not in TXT and CSV formats) can be defined as case insensitive texts: ON/OFF, YES/NO, TRUE/FALSE, or 1/0. For example:<br>
`nislq DSN=MyDSN "select * from tableA" a.txt -f"HDR=true"`<br>
`nislq DSN=MyDSN "select * from tableA" a.txt -f"HDR=YES"`<br>
`nislq DSN=MyDSN "select * from tableA" a.txt -f"HDR=oN"`<br>
Would produce the very same result.