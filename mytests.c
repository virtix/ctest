#include <unistd.h>
#include <stdlib.h>
#include "ctest.h"

// basic test without setup/teardown
CTEST(suite1, test1) {
    usleep(2000);
}

// there are many different ASSERT macro's (see ctest.h)
CTEST(suite1, test2) {
    ASSERT_EQUAL(1,2);
}

CTEST(suite2, test1) {
    ASSERT_STR("foo", "bar");
}

CTEST(suite3, test3) {
}


// A test suite with a setup/teardown function
// This is converted into a struct that's automatically passed to all tests in the suite
CTEST_DATA(memtest) {
    unsigned char* buffer;
};

// Optional setup function for suite, called before every test in suite
CTEST_SETUP(memtest) {
    CTEST_LOG("%s() data=%p buffer=%p", __func__, data, data->buffer);
    data->buffer = (unsigned char*)malloc(1024);
}

// Optional teardown function for suite, called after every test in suite
CTEST_TEARDOWN(memtest) {
    CTEST_LOG("%s() data=%p buffer=%p", __func__, data, data->buffer);
    if (data->buffer) free(data->buffer);
}

// These tests are called with the struct* (named data) as argument
CTEST2(memtest, test1) {
    CTEST_LOG("%s()  data=%p  buffer=%p", __func__, data, data->buffer);
}

CTEST2_SKIP(memtest, test3) {
    ASSERT_FAIL();
}

CTEST2(memtest, test2) {
    CTEST_LOG("%s()  data=%p  buffer=%p", __func__, data, data->buffer);
    
    ASSERT_FAIL();
}


CTEST_DATA(fail) {};

// Asserts can also be used in setup/teardown functions
CTEST_SETUP(fail) {
    ASSERT_FAIL();
}

CTEST2(fail, test1) {}



CTEST_DATA(weaklinkage) {
    int number;
};

// This suite has data, but no setup/teardown
CTEST2(weaklinkage, test1) {
    CTEST_LOG("%s()", __func__);
}

CTEST2(weaklinkage, test2) {
    CTEST_LOG("%s()", __func__);
}


CTEST_DATA(nosetup) {
    int value;
};

CTEST_TEARDOWN(nosetup) {
    CTEST_LOG("%s()", __func__);
}

CTEST2(nosetup, test1) {
    CTEST_LOG("%s()", __func__);
}


// more ASSERT examples
CTEST(ctest, test_assert_str) {
    ASSERT_STR("foo", "foo");
    ASSERT_STR("foo", "bar");
}

CTEST(ctest, test_assert_equal) {
    ASSERT_EQUAL(123, 123);
    ASSERT_EQUAL(123, 456);
}

CTEST(ctest, test_assert_not_equal) {
    ASSERT_NOT_EQUAL(123, 456);
    ASSERT_NOT_EQUAL(123, 123);
}


CTEST(ctest, test_assert_null) {
    ASSERT_NULL(NULL);
    ASSERT_NULL((void*)0xdeadbeef);
}

CTEST(ctest, test_assert_not_null) {
    ASSERT_NOT_NULL((void*)0xdeadbeef);
    ASSERT_NOT_NULL(NULL);
}

CTEST(ctest, test_assert_true) {
    ASSERT_TRUE(1);
    ASSERT_TRUE(0);
}

CTEST(ctest, test_assert_false) {
    ASSERT_FALSE(0);
    ASSERT_FALSE(1);
}

CTEST_SKIP(ctest, test_skip) {
    ASSERT_FAIL();
}

CTEST(ctest, test_assert_fail) {
    ASSERT_FAIL();
}

