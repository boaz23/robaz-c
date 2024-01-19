#include "tests-common.h"
#include "math-ext.h"

TEST_GROUP(powi);
TEST_SETUP(powi) {
}

TEST_TEAR_DOWN(powi) {
}

TEST(powi, powi_tests) {
	TEST_ASSERT_EQUAL(1, powi(3, 0));
	TEST_ASSERT_EQUAL(3, powi(3, 1));
	TEST_ASSERT_EQUAL(3*3, powi(3, 2));
	TEST_ASSERT_EQUAL(3*3*3, powi(3, 3));
	TEST_ASSERT_EQUAL(3*3*3*3, powi(3, 4));
	TEST_ASSERT_EQUAL(3*3*3*3*3, powi(3, 5));
}

TEST_GROUP_RUNNER(powi) {
	RUN_TEST_CASE(powi, powi_tests);
}

static void RunAllTests(void) {
	RUN_TEST_GROUP(powi);
}

int main(int argc, const char * argv[]) {
	return UnityMain(argc, argv, RunAllTests);
}
