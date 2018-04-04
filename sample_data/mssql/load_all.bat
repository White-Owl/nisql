@echo off
echo Main tables
sqlcmd -E -i dbbook.sql
@echo Views and stored procedures
for %%a in (getClasses.sql student_in_class.sql) do sqlcmd -E -i%%a
@echo Load data
for %%a in (student faculty class enrolled emp dept works flights
           aircraft employees certified suppliers parts catalog
           sailors) do (
	echo %%a
	bcp nisql_tst.dbo.%%a in %%a.txt -T -c -t,
)