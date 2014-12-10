#include "stdafx.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace ProjectUnitTests
{
	TEST_CLASS(CameraMainTest)
	{
	public:

		TEST_METHOD(TestGetCamYaw)
		{
			CameraMain myCamera;
			Assert::AreEqual(myCamera.getCamYaw(), 0.0f);
		}
		TEST_METHOD(TestSetCamYaw)
		{
			CameraMain myCamera;
			float yaw = 0.0f;
			myCamera.setCamYaw(yaw);
			Assert::AreEqual(myCamera.getCamYaw(), yaw);
		}
		TEST_METHOD(TestGetCamPitch)
		{
			CameraMain myCamera;
			Assert::AreEqual(myCamera.getCamPitch(), 0.0f);
		}
		TEST_METHOD(TestSetCamPitch)
		{
			CameraMain myCamera;
			float pitch = 0.0f;
			myCamera.setCamPitch(pitch);
			Assert::AreEqual(myCamera.getCamPitch(), pitch);
		}
		TEST_METHOD(TestGetMoveLeftRight)
		{
			CameraMain myCamera;
			Assert::AreEqual(myCamera.getMoveLeftRight(), 0.0f);
		}
		TEST_METHOD(TestSetMoveLeftRight)
		{
			CameraMain myCamera;
			float moveLeftRight = 0.0f;
			myCamera.setMoveLeftRight(moveLeftRight);
			Assert::AreEqual(myCamera.getMoveLeftRight(), moveLeftRight);
		}
		TEST_METHOD(TestGetMoveBackForward)
		{
			CameraMain myCamera;
			Assert::AreEqual(myCamera.getMoveBackForward(), 0.0f);
		}
		TEST_METHOD(TestSetMoveBackForward)
		{
			CameraMain myCamera;
			float moveBackForward = 0.0f;
			myCamera.setMoveBackForward(moveBackForward);
			Assert::AreEqual(myCamera.getMoveBackForward(), moveBackForward);
		}

	};
}