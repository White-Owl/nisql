@rem Since Oracle is (usually) case sensitive, then the first call should
@rem succeesfully find the table, while the second one should fail to do so.
..\src\nisql.exe DSN=Ora1;UID=jim;PWD=123 DEPT out1.txt -v
..\src\nisql.exe DSN=Ora1;UID=jim;PWD=123 dept out2.txt -v

@rem MS SQL Server is setup as case insesitive, so both cases should work
..\src\nisql.exe DSN=mss1 DEPT out1.txt -v
..\src\nisql.exe DSN=mss1 dept out2.txt -v
