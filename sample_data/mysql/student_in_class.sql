CREATE VIEW STUDENT_IN_CLASS 
AS
select
    s.SNAME as Student,
    e.CNAME as Class
from student s
join enrolled e on s.snum=e.SNUM;

