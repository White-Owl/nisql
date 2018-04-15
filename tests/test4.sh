#!/bin/sh
cd ..
src/nisql "DSN=mysql1;UID=jim;PWD=123" "select sname as Name, age as Age from student" out1.txt -v -f"hdr=1"
src/nisql "DSN=mysql1;UID=jim;PWD=123" "select distinct major from student" out2.txt -v

