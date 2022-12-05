The connection string for NISQL is using the ODBC standard for connection strings.
The format of that string is described in a function [SQLDriverConnect()](https://docs.microsoft.com/en-us/sql/odbc/reference/syntax/sqldriverconnect-function?view=sql-server-2017#comments).

Which in short boils down to:
* If your database does not require login credentials or the credentials can be stored inside the DSN, then the connection string can be just a:<br>
 `DSN=MyDSN`
* If you have to pass the credentials from outside the DSN, then the connection string become:<br>
 `DSN=MyDSN;UID=user;PWD=password`
* If you require some additional connection options (and cannot store them inside the DSN):<br>
 `DSN=MyDSN;UID=user;PWD=password;key1=val;key2=val`
* If you by some reason cannot create a DSN, you can use:<br>
 `DRIVER={some ODBC driver};key1=val;key2=val`

The list of additional keys and which values they can have are described in the documentation of your RDBMS and its ODBC drivers.