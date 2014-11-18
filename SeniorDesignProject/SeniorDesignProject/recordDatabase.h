#pragma once
/*#include <cstddef>
#include <atlstr.h>
#include <SQLAPI.h>

#define MAX_STRING_SIZE 512
#define MAX_RESULT_SIZE 64
#define MAX_FIELDS 10

enum field{ ID, HEADSHOTS, KILLS, DEATHS, USERNAME, PASSWORD};
static const char *fieldNames[] = { "id", "headshots", "kills", "deaths" , "username"};
static const char *dbFieldNames[] = { "id", "headshots", "kills", "deaths", "username" };

struct databaseEntry{
	const char *strValue;
	int intValue;
	const char *fieldName;
	bool gotten;
};

class recordDatabase{
public:
	recordDatabase();
	~recordDatabase();

	//returns false if failure.
	bool logIn(CString name, CString pass);
	//returns false if failure.
	bool addUser(CString name, CString pass);
	bool logOut();
	bool isLoggedIn();

	bool removeUser();

	//Returns null if failure
	bool getRecord(field fields[], int numFields, databaseEntry *result[MAX_FIELDS]);
	//returns false if failure.
	bool updateRecord(field field, int value, bool onlyIfGreater);
	//returns false if failure.
	bool addToRecord(field field, int valueToAdd);
	//Connects to the database.
	bool connect();
	//Disconnects from the database.
	bool disconnect();
private:
	int id;
	SAConnection con;

	//Executes a raw query.
	bool rawQuery(CString q,databaseEntry *results[MAX_RESULT_SIZE][MAX_FIELDS]);
	//Clears the results array.
	void clearResults(databaseEntry *results[MAX_RESULT_SIZE][MAX_FIELDS]);
};*/