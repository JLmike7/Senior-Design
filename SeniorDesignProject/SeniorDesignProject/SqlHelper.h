#pragma once
#include <stdlib.h>
#include <iostream>

/*
Include directly the different
headers from cppconn/ and mysql_driver.h + mysql_util.h
(and mysql_connection.h). This will reduce your build time!
*/

#include "sql\cppconn\driver.h"
#include "sql\cppconn\exception.h"
#include "sql\cppconn\resultset.h"
#include "sql\cppconn\statement.h"

class SqlHelper
{
public:
	SqlHelper();
	~SqlHelper();
private:
	Driver *driver;
	Connection *con;
	Statement *stmt;
	ResultSet *res;
};