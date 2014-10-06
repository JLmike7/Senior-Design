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
			// Test get team
			Biped myBiped;
			Assert::AreEqual(myBiped.getTeam(), team);
		}
		TEST_METHOD(TestSetTeam)
		{
			// Test set team
			Biped myBiped;
			myBiped.setTeam(2);
			Assert::AreEqual(myBiped.getTeam(), 2);
		}
		TEST_METHOD(TestGetFiring)
		{
			bool fire = false;
			// Test get firing
			Biped myBiped;
			Assert::AreEqual(myBiped.firing(), fire);
		}
		TEST_METHOD(TestTakeHit)
		{
			// Test hit
			Biped myBiped;
			Assert::AreEqual(myBiped.takeHit(10), 90);
		}
		TEST_METHOD(TestGetCameraHeight)
		{
			float height = 5.0f;
			// Test get difficulty
			Biped myBiped;
			Assert::AreEqual(myBiped.getCameraHeight(), height);
		}
		TEST_METHOD(TestSetCameraHeight)
		{
			// Test set difficulty
			Biped myBiped;
			myBiped.setCameraHeight(10.0f);
			Assert::AreEqual(myBiped.getCameraHeight(), 10.0f);
		}
		TEST_METHOD(TestGetCrawlCameraHeight)
		{
			float height = 5.0f;
			// Test get texture level
			Biped myBiped;
			Assert::AreEqual(myBiped.getCrawlCameraHeight(), height);
		}

		TEST_METHOD(TestSetCrawlCameraHeight)
		{
			// Test set texture level
			Biped myBiped;
			myBiped.setCrawlCameraHeight(10.0f);
			Assert::AreEqual(myBiped.getCrawlCameraHeight(), 10.0f);
		}
		TEST_METHOD(TestGetTeamColor)
		{
			int color = 1;
			// Test get detail level
			Biped myBiped;
			Assert::AreEqual(myBiped.getTeamColor(), color);
		}
		TEST_METHOD(TestSetTeamColor)
		{
			// Test et detail level
			Biped myBiped;
			myBiped.setTeamColor(2);
			Assert::AreEqual(myBiped.getTeamColor(), 2);
		}

		TEST_METHOD(TestGetDeath)
		{
			bool death = false;
			// Test get movement sensitivity
			Biped myBiped;
			Assert::AreEqual(myBiped.getDeath(), death);
		}
		TEST_METHOD(TestSetDeath)
		{
			// Test Set movement sensitivity
			Biped myBiped;
			myBiped.setDeath(true);
			Assert::AreEqual(myBiped.getDeath(), true);
		}

	};
}