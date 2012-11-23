#ifdef _RUN_TESTS_
#include "gtest/gtest.h"
#include "Camera.test.h"

int runUnitTests(int argc, char **argv)
{
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}

#ifdef _RUN_TESTS_AT_STARTUP_
int main(int argc, char **argv) 
{
	int res = runUnitTests(argc, argv);
	std::cin.get();
	return res;
}
#endif


#endif


