#!/bin/sh
echo Main tables
mysql mydb --user=jim --password=123 < dbbook.sql

echo Views and stored procedures
for a in getClassCount.sql student_in_class.sql
do
	mysql mydb --user=jim --password=123 < $a
done

echo Load data
for a in student faculty class enrolled emp dept works flights aircraft employees certified suppliers parts catalog sailors
do
	echo $a
	mysqlimport --user=jim --password=123 mydb $a.txt
done

