#include "recordDatabase.h"
#include <atlstr.h>
#include <oledb.h>
#include <windows.h>
#include <atlbase.h>




recordDatabase::recordDatabase()
{
	id = -1;
	connect();
}


recordDatabase::~recordDatabase()
{
}

bool recordDatabase::logIn(CString name, CString pass){
	try{
		CString q = _T("");
		q.Format(_T("SELECT %d FROM accounts WHERE username == '%s' AND password == '%s';"),dbFieldNames[ID],name,pass);
		databaseEntry *results[MAX_RESULT_SIZE][MAX_FIELDS];
		clearResults(results);
		rawQuery(q,results);
		if (results[0][0]->gotten){
			id = results[0][0]->intValue;
		}

		return isLoggedIn();
	}
	catch (int e){
		id = -1;
		return false;
	}
}
bool recordDatabase::logOut(){
	id = -1;
	return true;
}
bool recordDatabase::isLoggedIn(){
	return (id >= 0);
}
bool recordDatabase::addUser(CString name, CString pass){
	try{
		CString q = _T("");
		q.Format(_T("INSERT INTO accounts (%s,%s) VALUES ('%s','%s');"), dbFieldNames[USERNAME], dbFieldNames[PASSWORD],name, pass);
		rawQuery(q,NULL);
		logIn(name, pass);
		if (isLoggedIn()){
			return true;
		}
	}
	catch (int e){
		id = -1;
		return false;
	}
}

bool recordDatabase::removeUser(){
	if (isLoggedIn()){
		try{
			CString q = _T("");
			q.Format(_T("DELETE FROM accounts WHERE %s=%d"), dbFieldNames[ID],id);
			rawQuery(q,NULL);
			logOut();
			return true;
		}
		catch (int e){
			return false;
		}
	}
	return false;
}

bool recordDatabase::getRecord(field fields[], int numFields, databaseEntry *result[MAX_FIELDS]){
	if (isLoggedIn()){
		CString q = _T("");
		CString fieldsStr = _T("");
		for (int i = 0; i < numFields; i++){
			fieldsStr += fieldNames[fields[i]];
		}
		q.Format(_T("SELECT %s FROM accounts WHERE %s = %d"), fieldsStr, dbFieldNames[ID], id);

		databaseEntry *results[MAX_RESULT_SIZE][MAX_FIELDS];
		clearResults(results);
		rawQuery(q,results);

		result = results[0];
		return true;
	}
	return false;
}
bool recordDatabase::updateRecord(field field, int value, bool onlyIfGreater){
	if (isLoggedIn()){
		databaseEntry *prevValue[MAX_FIELDS];
		bool recordGotten = getRecord({ &field }, 1, prevValue);
		if (recordGotten && (!onlyIfGreater || prevValue[0]->intValue < value)){
			CString q = _T("");
			q.Format(_T("UPDATE accounts SET %s = %d WHERE %s = %d"), fieldNames[field], value, dbFieldNames[ID], id);
			rawQuery(q,NULL);
		}
	}
	return false;
}
bool recordDatabase::addToRecord(field field, int valueToAdd){
	if (isLoggedIn()){
		databaseEntry *prevValue[MAX_FIELDS];
		bool recordGotten = getRecord({ &field }, 1, prevValue);
		if (recordGotten){
			return updateRecord(field, prevValue[0]->intValue + valueToAdd, false);
		}
	}
	return false;
}
bool recordDatabase::rawQuery(CString q,databaseEntry *results[MAX_RESULT_SIZE][MAX_FIELDS]){
	//Create command object
	SACommand cmd(&con, q.GetBuffer(MAX_STRING_SIZE));
	try{
		cmd.Execute();
		clearResults(results);
		int count = 0;
		if (results != NULL){
			while (cmd.FetchNext() && count < MAX_RESULT_SIZE){
				for (int i = 0; i < cmd.FieldCount(); i++){
					//Get the values.
					const char *strResult = (const char*)cmd.Field(i).asString();
					int intResult = (int)cmd.Field(i).asDouble();
					const char *fieldName = (const char*)cmd.Field(i).Name();
					//Populate results array
					results[count][i]->fieldName = fieldName;
					results[count][i]->intValue = intResult;
					results[count][i]->strValue = strResult;
					results[count][i]->gotten = true;
				}
				count++;
			}
		}
		con.Commit();
		q.ReleaseBuffer();
	}
	catch (SAException &e){
		printf("Database could not be reached.");
		try{
			con.Rollback();
		}
		catch (SAException &x){
			printf("Could not rollback database.  Database could not be reached!");
		}
		return false;
	}
}
bool recordDatabase::disconnect(){
	con.Disconnect();
	printf("We are disconnected!\n");
	return true;
}
bool recordDatabase::connect(){
	try
	{
		// connect to database
		// in this example it is Oracle,
		// but can also be Sybase, Informix, DB2
		// SQLServer, InterBase, SQLBase and ODBC
		con.Connect(
			"mysql1.000webhost.com:a4148308_MBM",     // database name
			"a4148308_MBM",   // user name
			"ycpcs14",   // password
			SA_Oracle_Client);

		printf("We are connected!\n");

		return true;
	}
	catch (SAException &x)
	{
		// SAConnection::Rollback()
		// can also throw an exception
		// (if a network error for example),
		// we will be ready
		try
		{
			// on error rollback changes
			con.Rollback();
		}
		catch (SAException &)
		{
			return false;
		}
		// print error message
		printf("%s\n", (const char*)x.ErrText());
		return false;
	}
}
void recordDatabase::clearResults(databaseEntry *results[MAX_RESULT_SIZE][MAX_FIELDS]){
	for (int i = 0; i < MAX_RESULT_SIZE; i++){
		for (int field = 0; field < MAX_FIELDS; field++){

			results[i][field]->fieldName = "";
			results[i][field]->intValue = 0;
			results[i][field]->strValue = "";
			results[i][field]->gotten = false;
		}
	}
}