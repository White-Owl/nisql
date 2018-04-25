#!/bin/sh
# MySQL's pecularity: Option=67108864 required for multiple sets
cd ..
con="DSN=mysql1;UID=jim;PWD=123;Option=67108864"
src/nisql $con "select * from student" out1.json -v -f"root=students"
src/nisql $con "select * from student" out2.json -v -f"rows=student"
src/nisql $con "select * from student" out3.json -v -f"root=students;rows=student"
src/nisql $con "select * from student; select * from class" out4.json -v
src/nisql $con "select * from student; select * from class" out5.json -v -f"SETS=student,class;ROOT=data"
src/nisql $con "select * from student; select * from class" out6.json -v -f"sets=students,classes;rows=student,class;root=data;stream=yes"
src/nisql $con "select * from student; select * from class" out7.json -v -f"sets=students,classes;rows=student,class;root=data;stream=no"
src/nisql $con "select * from student; select * from class" out8.json -v -f"sets=students,classes;rows=student,class;root=data;FieldPerLine=yes"


