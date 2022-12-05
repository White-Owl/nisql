# nisql

NISQL (short for Non Interactive SQL) is a tool designed to be used in a scheduled environment. It allows user to connect through ODBC to any database, execute any SQL script, and dump the resultset or multiple resultsets into the file(s).

The NISQL is written in OS and RDBMS independent way, so it can be used in any environment.

The intended way to use *nisql* is to put it in a shell script like this:
```
#!/bin/sh

today=`date +%F`
csvfile="/tmp/daily_report_for_$today.csv"

nisql DSN=MyDB daily_report.sql $csvfile -f"HDR=yes"

mail boss@mycompany.com --attach=$csvfile -s"Daily report for $today" <<EOT
Dear Boss,
Here is an automated report for $today
EOT
```
This assumes that `MyDB` is a DSN to connect to the database. And `daily_report.sql` contains a SQL statement (or multiple statements) which are resulted in a single resultset.
Just put this script to the `cron` and done.
