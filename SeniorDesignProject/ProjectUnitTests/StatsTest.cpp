#include "stdafx.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace ProjectUnitTests
{
	TEST_CLASS(StatsTest)
	{
	public:
		
		TEST_METHOD(TestGetMaxHealth)
		{
			int maxHealth = 100;
			// Test get max health
			Stats myStats;
			Assert::AreEqual(myStats.getMaxHealth(), maxHealth);
		}

		TEST_METHOD(TestSetMaxHealth)
		{
			// Test set health
			Stats myStats;
			myStats.setMaxHealth(50);
			Assert::AreEqual(myStats.getMaxHealth(), 50);

		}

		TEST_METHOD(TestGetHealth)
		{
			int health = 100;
			// Test get health
			Stats myStats;
			Assert::AreEqual(myStats.getHealth(), health);

		}

		TEST_METHOD(TestSetHealth)
		{
			// Test set health
			Stats myStats;
			myStats.setHealth(20);
			Assert::AreEqual(myStats.getHealth(), 20);

		}

		TEST_METHOD(TestGetStrength)
		{
			int strength = 50;
			// Test get strength
			Stats myStats;
			Assert::AreEqual(myStats.getStrength(), strength);
		}

		TEST_METHOD(TestSetStrength)
		{
			// Test set strength
			Stats myStats;
			myStats.setStrength(1); //Tis but a puny welp
			Assert::AreEqual(myStats.getStrength(), 1);

		}

		TEST_METHOD(TestGetLives)
		{
			int lives = 3;
			// Test get lives
			Stats myStats;
			Assert::AreEqual(myStats.getLives(), lives);

		}

		TEST_METHOD(TestSetLives)
		{
			// Test set lives
			Stats myStats;
			myStats.setLives(0); //You're dead bruh
			Assert::AreEqual(myStats.getLives(), 0);

		}

		TEST_METHOD(TestGetMaxCrawl)
		{
			//Test get max crawl
			float crawl = 25.0f;
			Stats myStats;
			Assert::AreEqual(myStats.getMaxCrawl(), crawl);

		}

		TEST_METHOD(TestSetMaxCrawl)
		{
			// Test set max crawl
			Stats myStats;
			myStats.setMaxCrawl(15.0f);
			Assert::AreEqual(myStats.getMaxCrawl(), 15.0f);

		}

		TEST_METHOD(TestGetMaxWalk)
		{
			// Test get max walk
			float walk = 60.0f;
			Stats myStats;
			Assert::AreEqual(myStats.getMaxWalk(), walk);

		}

		TEST_METHOD(TestSetMaxWalk)
		{
			// Test set max walk
			Stats myStats;
			myStats.setMaxWalk(100.0f);
			Assert::AreEqual(myStats.getMaxWalk(), 100.0f);

		}

		TEST_METHOD(TestGetMaxRun)
		{
			// Test get max run
			float run = 100.0f;
			Stats myStats;
			Assert::AreEqual(myStats.getMaxRun(), run);

		}

		TEST_METHOD(TestSetMaxRun)
		{
			// Test set max run
			Stats myStats;
			myStats.setMaxRun(200.0f);
			Assert::AreEqual(myStats.getMaxRun(), 200.0f);

		}

		TEST_METHOD(TestGetMaxSpeed)
		{
			// Test get max speed
			float speed = 200.0f;
			Stats myStats;
			Assert::AreEqual(myStats.getMaxSpeed(), speed);

		}

		TEST_METHOD(TestSetMaxSpeed)
		{
			// Test set max speed
			Stats myStats;
			myStats.setMaxSpeed(400.0f);
			Assert::AreEqual(myStats.getMaxSpeed(), 400.0f);

		}

		TEST_METHOD(TestGetInUse)
		{
			// Test get in use
			bool use = false;
			Stats myStats;
			Assert::AreEqual(myStats.getInUse(), use);

		}

		TEST_METHOD(TestSetInUse)
		{
			// Test set in use
			Stats myStats;
			myStats.setInUse(true);
			Assert::AreEqual(myStats.getInUse(), true);

		}

	};
}