/*The Files*/
INSERT INTO FILE  (file_name,num_props)
VALUES ('JSnow.vcf','0');

INSERT INTO FILE  (file_name,num_props)
VALUES ('Stark.vcf','1');

INSERT INTO FILE  (file_name,num_props)
VALUES ('Bethesda.vcf','8');

INSERT INTO FILE  (file_name,num_props)
VALUES ('meme.vcf','20');

INSERT INTO FILE  (file_name,num_props)
VALUES ('Lannister.vcf','6');

/*The address*/
INSERT INTO ADDRESS (address)
VALUES ('Westeros');

INSERT INTO ADDRESS (address)
VALUES ('USA');

INSERT INTO ADDRESS (address)
VALUES ('Iceland');

INSERT INTO ADDRESS (address)
VALUES ('United Kingdom');

/*the People*/
INSERT INTO INDIVIDUAL (name,birthday,source_file,address)
VALUES ( 'John Snow','2004-11-11','1','1');

INSERT INTO INDIVIDUAL (name,birthday,source_file,address)
VALUES ( 'Sansa Stark','2006-12-12','2','1');

INSERT INTO INDIVIDUAL (name,birthday,source_file,address)
VALUES ( 'Rob Stark','2000-12-12','2','1');

INSERT INTO INDIVIDUAL (name,birthday,source_file,address)
VALUES ( 'Ned Stark','1980-12-10','2','1');

INSERT INTO INDIVIDUAL (name,birthday,source_file,address)
VALUES ( 'Todd Howard','1971-04-25','3','2');

INSERT INTO INDIVIDUAL (name,birthday,source_file,address)
VALUES ( 'Stefán Karl Stefánsson','1971-04-25','4','3');

INSERT INTO INDIVIDUAL (name,birthday,source_file,address)
VALUES ( 'Rick Astley','1966-02-06','4','4');

INSERT INTO INDIVIDUAL (name,birthday,source_file,address)
VALUES ( 'Tyrion Lannister','1968-03-02','5','1');



