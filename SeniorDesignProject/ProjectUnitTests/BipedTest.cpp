#include "stdafx.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace ProjectUnitTests
{
	TEST_CLASS(BipedTest)
	{
	public:
		
		TEST_METHOD(TestGetTeam)
		{
			int team = 1;
			Biped myBiped;
			Assert::AreEqual(myBiped.getTeam(), team);
		}
		TEST_METHOD(TestSetTeam)
		{
			Biped myBiped;
			myBiped.setTeam(2);
			Assert::AreEqual(myBiped.getTeam(), 2);
		}
		TEST_METHOD(TestGetDeath)
		{
			bool death = false;
			Biped myBiped;
			Assert::AreEqual(myBiped.getDeath(), death);
		}
		TEST_METHOD(TestSetDeath)
		{
			Biped myBiped;
			myBiped.setDeath(true);
			Assert::AreEqual(myBiped.getDeath(), true);
		}

	};
}