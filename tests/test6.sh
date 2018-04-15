#!/bin/sh
# MySQL's pecularity: Option=67108864 required for multiple sets
cd ..
src/nisql "DSN=mysql1;UID=jim;PWD=123;Option=67108864" tests/three_selects.sql out.txt -v -f"hdr=yes"

