@rem Simple direc queries. Both cases should return the same result:
@rem apple orange
..\src\nisql.exe DSN=Ora1;UID=jim;PWD=123 "select 'apple', 'orange' from DUAL" out1.txt -v
..\src\nisql.exe DSN=mss1 "select 'apple', 'orange'" out2.txt -v
@type out1.txt
@type out2.txt
