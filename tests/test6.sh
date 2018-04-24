#!/bin/sh
# MySQL's pecularity: Option=67108864 required for multiple sets
cd ..
conn="DSN=mysql1;UID=jim;PWD=123;Option=67108864"
src/nisql $conn tests/three_selects.sql out.txt
src/nisql $conn tests/three_selects.sql out.csv
src/nisql $conn tests/three_selects.sql out.xml
src/nisql $conn tests/three_selects.sql out.json


src/nisql $conn tests/three_selects.sql students.txt -f"Sets=classes.txt,rooms.txt"
src/nisql $conn tests/three_selects.sql students.csv -f"Sets=classes.csv,rooms.csv"
src/nisql $conn tests/three_selects.sql students_classes_rooms.xml -f"Sets=students,classes,rooms"
src/nisql $conn tests/three_selects.sql students_classes_rooms.json -f"Sets=students,classes,rooms"

