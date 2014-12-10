#include "stdafx.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace ProjectUnitTests
{
	TEST_CLASS(PointTest)
	{
	public:

		TEST_METHOD(TestGetX)
		{
			Point myPoint;
			Assert::AreEqual(myPoint.getX(), 0.0f);
		}
		TEST_METHOD(TestSetX)
		{
			Point myPoint;
			float x = 10.0f;
			myPoint.setX(x);
			Assert::AreEqual(myPoint.getX(), 10.0f);
		}
		TEST_METHOD(TestGetY)
		{
			Point myPoint;
			Assert::AreEqual(myPoint.getY(), 0.0f);
		}
		TEST_METHOD(TestSetY)
		{
			Point myPoint;
			float y = 10.0f;
			myPoint.setY(y);
			Assert::AreEqual(myPoint.getY(), 10.0f);
		}
		TEST_METHOD(TestGetZ)
		{
			Point myPoint;
			Assert::AreEqual(myPoint.getZ(), 0.0f);
		}
		TEST_METHOD(TestSetX)
		{
			Point myPoint;
			float z = 10.0f;
			myPoint.setZ(z);
			Assert::AreEqual(myPoint.getZ(), 10.0f);
		}
		TEST_METHOD(TestAddX)
		{
			Point myPoint;
			float x = 5.0f;
			myPoint.addX(x);
			Assert::AreEqual(myPoint.getX(), 5.0f);
		}
		TEST_METHOD(TestAddY)
		{
			Point myPoint;
			float y = 5.0f;
			myPoint.addY(y);
			Assert::AreEqual(myPoint.getY(), 5.0f);
		}
		TEST_METHOD(TestAddZ)
		{
			Point myPoint;
			float z = 5.0f;
			myPoint.addZ(z);
			Assert::AreEqual(myPoint.getZ(), 5.0f);
		}

	};
}