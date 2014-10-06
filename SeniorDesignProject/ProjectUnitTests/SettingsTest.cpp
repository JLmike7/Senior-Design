#include "stdafx.h"


using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace ProjectUnitTests
{
	TEST_CLASS(SettingsTest)
	{
	public:
		
		TEST_METHOD(TestGetFF)
		{
			bool FF = false;
			// Test get friendly fire
			Settings mySettings;
			Assert::AreEqual(mySettings.getFF(), FF);
		}
		TEST_METHOD(TestSetFF)
		{
			bool FF = true;
			// Test set set friendly fire
			Settings mySettings;
			mySettings.setFF(FF);
			Assert::AreEqual(mySettings.getFF(), FF);
		}
		TEST_METHOD(TestGetIsFullScreen)
		{
			bool FS = true;;
			// Test Get  is full screeen
			Settings mySettings;
			Assert::AreEqual(mySettings.getIsFullScreen(), FS);
		}
		TEST_METHOD(TestSetIsFullScreen)
		{
			bool FS = false;;
			// Test set is full screen
			Settings mySettings;
			mySettings.setIsFullScreen(FS);
			Assert::AreEqual(mySettings.getIsFullScreen(), FS);
		}
		TEST_METHOD(TestGetDifficulty)
		{
			int dif = 2;
			// Test get difficulty
			Settings mySettings;
			Assert::AreEqual(mySettings.getDifficulty(), dif);
		}
		TEST_METHOD(TestSetDifficulty)
		{
			int difficulty = 9001;  //WHAT! THATS IMPOSSIBLE!
			// Test set difficulty
			Settings mySettings;
			mySettings.setDifficulty(difficulty);
			Assert::AreEqual(mySettings.getDifficulty(), difficulty);
		}
		TEST_METHOD(TestGetTextureLevel)
		{
			int tex = 2;
			// Test get texture level
			Settings mySettings;
			Assert::AreEqual(mySettings.getTextureLevel(), tex);
		}

		TEST_METHOD(TestSetTextureLevel)
		{
			int tex = 3;
			// Test set texture level
			Settings mySettings;
			mySettings.setTextureLevel(tex);
			Assert::AreEqual(mySettings.getTextureLevel(), tex);
		}
		TEST_METHOD(TestGetDetailLevel)
		{
			int det = 2;
			// Test get detail level
			Settings mySettings;
			Assert::AreEqual(mySettings.getDetailLevel(), det);
		}
		TEST_METHOD(TestSetDetailLevel)
		{
			int det = 10;
			// Test et detail level
			Settings mySettings;
			mySettings.setDetailLevel(det);
			Assert::AreEqual(mySettings.getDetailLevel(), det);
		}

		TEST_METHOD(TestGetMovementSensitivity)
		{
			int MS = 5;
			// Test get movement sensitivity
			Settings mySettings;
			Assert::AreEqual(mySettings.getMovementSensitivity(), MS);
		}
		TEST_METHOD(TestSetMovementSensitivity)
		{
			int MS = 1;
			// Test Set movement sensitivity
			Settings mySettings;
			mySettings.setMovementSensitivity(MS);
			Assert::AreEqual(mySettings.getMovementSensitivity(), MS);
		}
		TEST_METHOD(TestGetLookSensitivity)
		{
			int LS = 5;
			// Test Get look sensitivity
			Settings mySettings;
			Assert::AreEqual(mySettings.getLookSensitivity(), LS);
		}
		TEST_METHOD(TestSetLookSensivity)
		{
			int LS = 1;
			// Test set look sensitivity
			Settings mySettings;
			mySettings.setLookSensitivity(LS);
			Assert::AreEqual(mySettings.getLookSensitivity(), LS);
		}

	};
}