CREATE TABLE FILE (
		 id int AUTO_INCREMENT PRIMARY KEY,
		 file_name varchar(60) NOT NULL,
		 num_props int NOT NULL
		 );

CREATE TABLE ADDRESS (
		 id int AUTO_INCREMENT PRIMARY KEY,
		 address varchar(256) NOT NULL 
		 );

CREATE TABLE INDIVIDUAL (
		 id int AUTO_INCREMENT PRIMARY KEY,
		 name varchar(256) NOT NULL,
		 birthday DATETIME,
		 source_file int,
		 address int,
		 FOREIGN KEY (source_file) REFERENCES FILE(id) ON DELETE CASCADE,
		 FOREIGN KEY (address) REFERENCES ADDRESS(id)
		 );
