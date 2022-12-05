The query to run can be defined in several ways:

* filename.sql<br>
This way of specifying a query is recognized by ".sql" extension. In this case, the NISQL will read the contents of that file and pass it into RDBMS.

* object-name<br>
The query can be represented by just a name of a table, view or stored procedure. In this case, the NISQL will use ODBC functions [SQLTables()](https://docs.microsoft.com/en-us/sql/odbc/reference/syntax/sqltables-function?view=sql-server-2017) and [SQLProcedures()](https://docs.microsoft.com/en-us/sql/odbc/reference/syntax/sqlprocedures-function?view=sql-server-2017), to check does an object with such name exist in the database? If yes, then for tables or views, the actual SQL statement executed by NISQL would become:<br>
&nbsp;&nbsp;&nbsp;  select * from object-name<br>
for stored procedures the SQL statement would be:<br>
&nbsp;&nbsp;&nbsp;  execute object-name<br>
Please note: the stored procedure have to return resultset to be usable this way, that can be done in any of the SAP Sybase RDBMSs or in MS SQL Server. The RDBMS like Oracle or MySQL has a different ideas for how stored procedures should be used.

* direct-sql-statement<br>
If the _query_ passed to NISQL does not end with ".sql" and it is not recognized as object by SQLTables() or SQLProcudres(), the NISQL assume this is a direct SQL statement and executes the query as is.


Examples:
* `nisql DSN=MyDSN huge-script.sql out.csv`<br>
_huge-script.sql_ here is a name of the file located in the current directory.
* `nisql DSN=MyDSN mydb.Customers out.csv`<br>
_mydb.Customers_ is a name of a table in a schema mydb (assuming we are working with MySQL), and the actual query would be:<br>
 `select * from mydb.Customers`
* `nisql DSN=MyDSN mydb.dbo.get_customers out.csv`<br>
_mydb.dbo.get_customers_ is a name of the stored procedure (in MS SQL Server standard), and the actual query would be: <br>
`execute mydb.dbo.Customers`<br>
Please note, that NISQL will automatically skip non-rows resultsets and you do not have to use Transact SQL command `set nocount on`
* `nisql DSN=MyDSN "select Name, Age from Students" out.csv`<br>
A direct SQL query, which would select two columns by name from a table (or view) Students
