#!/bin/sh
cd ..
conn="DSN=mysql1;UID=jim;PWD=123"
src/nisql $conn student out.txt -v
src/nisql $conn student out.csv -v
src/nisql $conn student out.xml -v
src/nisql $conn student out.json -v

