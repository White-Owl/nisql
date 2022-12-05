Dump the resultset into a JSON file.

Recognized formating options are:
* STREAM - boolean option which defines should we write the whole file as one string, or should we format the XML to be read by humans? By default - no.

* FIELDPERLINE - boolean. Should each column be printed on a separate line or no? By default no and each record would be written in one line. Works together with STREAM=NO.

* ROOT - name of the root element for the entire XML. By default: "root"

* SETS - comma separated list of elements directly under the root. If SETS has fewer names then actual number of resultsets, when for each unexpected resultset the name would be constructed in the format "section-#".<br>
If the SETS key is omitted, then NISQL would expect just one resultset and all rows from it would be nested directly under root. The extra resulstes would become _section-#_ elements under the root.

* ROWS - comma separated list of names for records. Each name on the list correspond to the name of set in SETS. If omitted (or ROWS has fewer names than SETS), then rows for undefined set would have name "row".


Example, assuming we have a table student with columns _sname varchar(30)_ and _age numeric(2)_:<br>
`nisql "DSN=MyDB" "select sname as Name, age as Age from student" out.json`<br>
Can produce an out.json with a contents:
<pre>{ "root": [
	{ "row": {"Name:"Maria White","Age:"21"} ,
	{ "row": {"Name:"Charles Harris","Age:"22"} ,
	{ "row": {"Name:"Susan Martin","Age:"20"} ,
	{ "row": {"Name:"Joseph Thompson","Age:"19"} ,
	{ "row": {"Name:"Christopher Garcia","Age:"20"}
]}
</pre>

By defining ROOT and ROWS keys<br>
`nisql "DSN=MyDB" "select sname as Name, age as Age from student" out.xml -f"root=students;rows=student"`<br>
We can get:
<pre>{ "students": [
	{ "student": {"Name:"Maria White","Age:"21"} ,
	{ "student": {"Name:"Charles Harris","Age:"22"} ,
	{ "student": {"Name:"Susan Martin","Age:"20"} ,
	{ "student": {"Name:"Joseph Thompson","Age:"19"} ,
	{ "student": {"Name:"Christopher Garcia","Age:"20"}
]}
</pre>

And if we add FieldPerLine key:<br>
`nisql "DSN=MyDB" "select sname as Name, age as Age from student" out.xml -f"root=students;rows=studnet;fieldperline=on"`<br>
We can get:
<pre>{ "students": [
	{ "student": {
		"Name":"Maria White",
		"Age":"21"
	},
	{ "student": {
		"Name":"Charles Harris",
		"Age":"22"
	},
	{ "student": {
		"Name":"Susan Martin",
		"Age":"20"
	},
	{ "student": {
		"Name":"Joseph Thompson",
		"Age":"19"
	},
	{ "student": {
		"Name":"Christopher Garcia",
		"Age":"20"
	}
]}
</pre>
