#!/bin/sh
# MySQL's pecularity: Option=67108864 required for multiple sets
cd ..
src/nisql "DSN=mysql1;UID=jim;PWD=123;Option=67108864" "select * from student" out1.json -v
src/nisql "DSN=mysql1;UID=jim;PWD=123;Option=67108864" "select * from student" out2.json -v -f"???"
src/nisql "DSN=mysql1;UID=jim;PWD=123;Option=67108864" "select * from student; select * from class" out3.json -v
src/nisql "DSN=mysql1;UID=jim;PWD=123;Option=67108864" "select * from student; select * from class" out4.json -v -f"???"

