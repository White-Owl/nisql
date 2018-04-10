delimiter //
create PROCEDURE getClassCount(out parm1 int)
BEGIN
	SELECT count(*) into parm1 from class;
END//
delimiter ;

