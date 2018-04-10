drop table sailors;
drop table catalog;
drop table parts;
drop table suppliers;
drop table certified;
drop table employees;
drop table aircraft;
drop table flights;
drop table works;
drop table dept;
drop table emp;
drop table enrolled;
drop table class;
drop table faculty;
drop table student;

create table student(
	snum numeric(9,0) primary key,
	sname varchar(30),
	major varchar(25),
	standing varchar(2),
	age numeric(3,0)
	);
create table faculty(
	fid numeric(9,0) primary key,
	fname varchar(30),
	deptid numeric(2,0)
	);
create table class(
	name varchar(40) primary key,
	meets_at varchar(20),
	room varchar(10),
	fid numeric(9,0),
	foreign key(fid) references faculty(fid)
	);
create table enrolled(
	snum numeric(9,0),
	cname varchar(40),
	primary key(snum,cname),
	foreign key(snum) references student(snum),
	foreign key(cname) references class(name)
	);
create table emp(
	eid numeric(9,0) primary key,
	ename varchar(30),
	age numeric(3,0),
	salary numeric(10,2)
	);
create table dept(
	did numeric(2,0) primary key,
	dname varchar(20),
	budget numeric(10,2),
	managerid numeric(9,0),
	foreign key(managerid) references emp(eid)
	);
create table works(
	eid numeric(9,0),
	did numeric(2,0),
	pct_time numeric(3,0),
	primary key(eid,did),
	foreign key(eid) references emp(eid),
	foreign key(did) references dept(did)
	);
create table flights(
	flno numeric(4,0) primary key,
	origin varchar(20),
	destination varchar(20),
	distance numeric(6,0),
	departs date,
	arrives date,
	price numeric(7,2)
	);
create table aircraft(
	aid numeric(9,0) primary key,
	aname varchar(30),
	crusingrange numeric(6,0)
	);
create table employees(
	eid numeric(9,0) primary key,
	ename varchar(30),
	salary numeric(10,2)
	);
create table certified(
	eid numeric(9,0),
	aid numeric(9,0),
	primary key(eid,aid),
	foreign key(eid) references employees(eid),
	foreign key(aid) references aircraft(aid)
	);
create table suppliers(
	sid numeric(9,0) primary key,
	sname varchar(30),
	address varchar(40)
	);
create table parts(
	pid numeric(9,0) primary key,
	pname varchar(40),
	color varchar(15)
	);
create table catalog(
	sid numeric(9,0),
	pid numeric(9,0),
	cost numeric(10,2),
	primary key(sid,pid),
	foreign key(sid) references suppliers(sid),
	foreign key(pid) references parts(pid)
	);
create table sailors(
	sid numeric(9,0) primary key,
	sname varchar(30),
	rating numeric(2,0),
	age numeric(4,1)
	);
