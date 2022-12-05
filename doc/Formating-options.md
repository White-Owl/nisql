Formatting options are defined by key `-f` and is string of `key=value` pairs separated by semicolon.

Please note: The keys are case insensitive, but values are (same as ODBC connection string).
For example, next two command will produce same result:<br>
`nisql ... out.xml -f "rows=Student"`<br>
`nisql ... out.xml -f "ROWS=Student"`

But if you define `-f "ROWS=sTuDeNt"` you will get xml with tags "sTuDeNt".

Different output formats, recognize different set of formatting options. The option which is for wrong output format (or with any unknown key) would be ignored.