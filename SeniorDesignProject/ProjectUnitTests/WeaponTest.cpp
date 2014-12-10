#include "stdafx.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace ProjectUnitTests
{
	TEST_CLASS(WeaponTest)
	{
	public:
		
		TEST_METHOD(TestGetRange)
		{
			float range = 10.0f;
			// Test get range
			Weapon myWeapon;
			Assert::AreEqual(myWeapon.getRange(), range);
		}

		TEST_METHOD(TestSetRange)
		{
			// Test set range
			Weapon myWeapon;
			myWeapon.setRange(50.0f);
			Assert::AreEqual(myWeapon.getRange(), 50.0f);
		}

		TEST_METHOD(TestGetSpread)
		{
			float spread = 2.0f;
			// Test get spread
			Weapon myWeapon;
			Assert::AreEqual(myWeapon.getSpread(), spread);
		}

		TEST_METHOD(TestSetSpread)
		{
			// Test set spread
			Weapon myWeapon;
			myWeapon.setSpread(3.0f);
			Assert::AreEqual(myWeapon.getSpread(), 3.0f);
		}

		TEST_METHOD(TestGetAccuracy)
		{
			float accuracy = 85.0f;
			// Test get accuracy
			Weapon myWeapon;
			Assert::AreEqual(myWeapon.getAccuracy(), accuracy);
		}

		TEST_METHOD(TestSetAccuracy)
		{
			// Test set accuracy
			Weapon myWeapon;
			myWeapon.setAccuracy(10.0f); 
			Assert::AreEqual(myWeapon.getAccuracy(), 10.0f);

		}

		TEST_METHOD(TestGetAttack)
		{
			float attack = 20.0f;
			// Test get attack
			Weapon myWeapon;
			Assert::AreEqual(myWeapon.getAttack(), attack);

		}

		TEST_METHOD(TestSetAttack)
		{
			// Test set attack
			Weapon myWeapon;
			myWeapon.setAttack(0.0f); 
			Assert::AreEqual(myWeapon.getAttack(), 0.0f);

		}

		TEST_METHOD(TestGetDefend)
		{
			//Test get defend
			float defend = 10.0f;
			Weapon myWeapon;
			Assert::AreEqual(myWeapon.getDefend(), defend);

		}

		TEST_METHOD(TestSetDefend)
		{
			// Test set defend
			Weapon myWeapon;
			myWeapon.setDefend(15.0f);
			Assert::AreEqual(myWeapon.getDefend(), 15.0f);

		}

		TEST_METHOD(TestGetReload)
		{
			// Test get get reload
			int reload = 2;
			Weapon myWeapon;
			Assert::AreEqual(myWeapon.getReloadTime(), reload);

		}

		TEST_METHOD(TestSetReload)
		{
			// Test set reload
			Weapon myWeapon;
			myWeapon.setReloadTime(1);
			Assert::AreEqual(myWeapon.getReloadTime(), 1);

		}

		TEST_METHOD(TestGetMagSize)
		{
			// Test get mag size
			int magSize = 8;
			Weapon myWeapon;
			Assert::AreEqual(myWeapon.getMagSize(), magSize);

		}

		TEST_METHOD(TestSetMagSize)
		{
			// Test set reload
			Weapon myWeapon;
			myWeapon.setMagSize(12);
			Assert::AreEqual(myWeapon.getMagSize(), 12);

		}

		TEST_METHOD(TestGetExtraClips)
		{
			// Test get mag size
			int clips = 3;
			Weapon myWeapon;
			Assert::AreEqual(myWeapon.getExtraClips(), clips);

		}

		TEST_METHOD(TestSetExtraClips)
		{
			// Test set reload
			Weapon myWeapon;
			myWeapon.setExtraClips(12);
			Assert::AreEqual(myWeapon.getExtraClips(), 12);

		}

	};
}