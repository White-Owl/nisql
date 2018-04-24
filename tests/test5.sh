#!/bin/sh
cd ..
conn="DSN=mysql1;UID=jim;PWD=123;Option=67108864"
qry="select * from student; select * from class"

src/nisql $conn "$qry" out.txt -v -f"hdr=1"
src/nisql $conn "$qry" stud.txt -v -f"hdr=yes;sets=cls.txt"

src/nisql $conn "$qry" out.csv -v -f"hdr=1"
src/nisql $conn "$qry" stud.csv -v -f"hdr=yes;sets=cls.csv"

