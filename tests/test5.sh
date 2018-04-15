#!/bin/sh
cd ..
src/nisql "DSN=mysql1;UID=jim;PWD=123;Option=67108864" "select * from student; select * from class" out.txt -v -f"hdr=1"
src/nisql "DSN=mysql1;UID=jim;PWD=123;Option=67108864" "select * from student; select * from class" stud.txt -v -f"hdr=yes;sets=cls.txt"

