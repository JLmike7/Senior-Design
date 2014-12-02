#include "stdafx.h"
#include "CppUnitTest.h"
#include <atlbase.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace ProjectUnitTests
{
	TEST_CLASS(recordDatabaseTest)
	{
	public:
		TEST_METHOD(TestAddUser)
		{
			recordDatabase db;
			Assert::IsTrue(db.addUser(_T("USER"), _T("PASS")));
		}
		TEST_METHOD(TestLogIn)
		{
			recordDatabase db;
			Assert::IsTrue(db.logIn(_T("USER"), _T("PASS")));
		}
		TEST_METHOD(TestGetField)
		{
			recordDatabase db;
			databaseEntry *result[MAX_FIELDS];
			Assert::IsTrue(db.getRecord({ID},1,result));
			Assert::AreEqual(result[0].intValue, 1);
		}

	};
}