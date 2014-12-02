#include "stdafx.h"



using namespace Microsoft::VisualStudio::CppUnitTestFramework;
	
namespace ProjectUnitTests
{		
	TEST_CLASS(PhysicsTest)
	{
	public:
		
		TEST_METHOD(TestGetGravity)
		{
			double gravity = 9.81;
			// Test get gravity
			Physics myPhysics;
			Assert::AreEqual(myPhysics.getGravity(), gravity);
		}
		TEST_METHOD(TestSetGravity)
		{
			double gravity = 5.55;
			// Test set gravity
			Physics myPhysics;
			myPhysics.setGravity(gravity);
			Assert::AreEqual(myPhysics.getGravity(), gravity);
		}
		TEST_METHOD(TestGetWind)
		{
			double wind = 3.14;
			// Test Get Wind
			Physics myPhysics;
			Assert::AreEqual(myPhysics.getWind(), wind);
		}
		TEST_METHOD(TestSetWind)
		{
			double wind = 5.55;
			// Test Set Wind
			Physics myPhysics;
			myPhysics.setWind(wind);
			Assert::AreEqual(myPhysics.getWind(), wind);
		}
		TEST_METHOD(TestGetGroundHeight)
		{
			float GH = 0;
			// Test Get Ground Height
			Physics myPhysics;
			Assert::AreEqual(myPhysics.getGroundHeight(), GH);
		}
		TEST_METHOD(TestSetGroundHeight)
		{
			float GH = 5.55;
			// Test Set Ground Height
			Physics myPhysics;
			myPhysics.setGroundHeight(GH);
			Assert::AreEqual(myPhysics.getGroundHeight(), GH);
		}

		TEST_METHOD(TestGetWaterChoppiness)
		{
			float WC = 1;
			// Test Get Water Chopiness
			Physics myPhysics;
			Assert::AreEqual(myPhysics.getWaterChoppiness(), WC);
		}
		TEST_METHOD(TestSetWaterChoppiness)
		{
			float WC = 5.55;
			// Test Set water choppiness
			Physics myPhysics;
			myPhysics.setWaterChoppiness(WC);
			Assert::AreEqual(myPhysics.getWaterChoppiness(), WC);
		}
	};
}
