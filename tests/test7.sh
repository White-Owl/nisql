#!/bin/sh
# MySQL's pecularity: Option=67108864 required for multiple sets
cd ..
src/nisql "DSN=mysql1;UID=jim;PWD=123;Option=67108864" "select * from student" out1.xml -v -f"root=students"
src/nisql "DSN=mysql1;UID=jim;PWD=123;Option=67108864" "select * from student" out2.xml -v -f"rows=student"
src/nisql "DSN=mysql1;UID=jim;PWD=123;Option=67108864" "select * from student" out3.xml -v -f"root=students;rows=student"
src/nisql "DSN=mysql1;UID=jim;PWD=123;Option=67108864" "select * from student; select * from class" out4.xml -v
src/nisql "DSN=mysql1;UID=jim;PWD=123;Option=67108864" "select * from student; select * from class" out5.xml -v -f"SETS=student,class;ROOT=data"
src/nisql "DSN=mysql1;UID=jim;PWD=123;Option=67108864" "select * from student; select * from class" out6.xml -v -f"sets=students,classes;rows=student,class;root=data;stream=yes"
src/nisql "DSN=mysql1;UID=jim;PWD=123;Option=67108864" "select * from student; select * from class" out7.xml -v -f"sets=students,classes;rows=student,class;root=data;stream=no"
src/nisql "DSN=mysql1;UID=jim;PWD=123;Option=67108864" "select * from student; select * from class" out8.xml -v -f"sets=students,classes;rows=student,class;root=data;tags=yes"


