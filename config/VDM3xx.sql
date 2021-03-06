PRAGMA encoding = "UTF-8"; 
PRAGMA auto_vacuum = 1;

/* DROP TABLE and VIEW; */
DROP TABLE IF EXISTS VDM3xx;

/* CREATE TABLE and VIEW; */
CREATE TABLE IF NOT EXISTS VDM3xx (
name VARCHAR NOT NULL, 
value VARCHAR NOT NULL, 
description VARCHAR, 
PRIMARY KEY (Name));


begin; 

/* FILL TABLE DATA */

INSERT INTO VDM3xx values ('Class',  'VDM', '类名称');
INSERT INTO VDM3xx values ('Type',   'VDM',   'VDM的类型');
INSERT INTO VDM3xx values ('XFSModule', 'XFSVDMBase.dll', 'VDM的标准模块名称');

commit; 
