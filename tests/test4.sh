#!/bin/sh
cd ..
conn="DSN=mysql1;UID=jim;PWD=123"
q1="select sname as Name, age as Age from student"
q2="select distinct major from student"

src/nisql $conn "$q1" out1.txt -v -f"hdr=1"
src/nisql $conn "$q2" out2.txt -v

src/nisql $conn "$q1" out1.csv -v -f"hdr=1"
src/nisql $conn "$q2" out2.csv -v

