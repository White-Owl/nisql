Dump the resultset into a XML file.

Recognized formating options are:
* STREAM - boolean option which defines should we write the whole file as one string, or should we format the XML to be read by humans? By default - no.

* TAGS - boolean. Should each column be an element inside the record element or no? By default no and each record would be written as &lt;row col1="value" col2="value2"/&gt;

* ROOT - name of the root element for the entire XML. By default: "root"

* SETS - comma separated list of elements directly under the root. If SETS has fewer names then actual number of resultsets, when for each unexpected resultset the name would be constructed in the format "section-#".<br>
If the SETS key is omitted, then NISQL would expect just one resultset and all rows from it would be nested directly under root. The extra resulstes would become &lt;section-#&gt; elements under the root.

* ROWS - comma separated list of names for records. Each name on the list correspond to the name of set in SETS. If omitted (or ROWS has fewer names than SETS), then rows for undefined set would have name "row".


Example, assuming we have a table student with columns _sname varchar(30)_ and _age numeric(2)_:<br>
`nisql "DSN=MyDB" "select sname as Name, age as Age from student" out.xml`<br>
Can produce an out.xml with a contents:
<pre>&lt;root>
    &lt;row Name="Maria White" Age="21"/>
    &lt;row Name="Charles Harris" Age="22"/>
    &lt;row Name="Susan Martin" Age="20"/>
    &lt;row Name="Joseph Thompson" Age="19"/>
    &lt;row Name="Christopher Garcia" Age="20"/>
&lt;/root>
</pre>

By defining ROOT and ROWS keys<br>
`nisql "DSN=MyDB" "select sname as Name, age as Age from student" out.xml -f"root=students;rows=student"`<br>
We can get:
<pre>&lt;students>
    &lt;student Name="Maria White" Age="21"/>
    &lt;student Name="Charles Harris" Age="22"/>
    &lt;student Name="Susan Martin" Age="20"/>
    &lt;student Name="Joseph Thompson" Age="19"/>
    &lt;student Name="Christopher Garcia" Age="20"/>
&lt;/students>
</pre>

And if we add TAGS key:<br>
`nisql "DSN=MyDB" "select sname as Name, age as Age from student" out.xml -f"root=students;rows=student;tags=on"`<br>
We can get:
<pre>&lt;students>
    &lt;student>
        &lt;Name>
            Maria White
        &lt;/Name>
        &lt;Age>
            21
        &lt;/Age>
    &lt;/student>
    &lt;student>
        &lt;Name>
            Charles Harris
        &lt;/Name>
        &lt;Age>
            22
        &lt;/Age>
    &lt;/student>
    &lt;student>
        &lt;Name>
            Susan Martin
        &lt;/Name>
        &lt;Age>
            20
        &lt;/Age>
    &lt;/student>
    &lt;student>
        &lt;Name>
            Joseph Thompson
        &lt;/Name>
        &lt;Age>
            19
        &lt;/Age>
    &lt;/student>
    &lt;student>
        &lt;Name>
            Christopher Garcia
        &lt;/Name>
        &lt;Age>
            20
        &lt;/Age>
    &lt;/student>
&lt;/students>
</pre>
