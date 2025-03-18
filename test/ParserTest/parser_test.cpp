#include "gtest/gtest.h"

extern "C" {
#include "parser/parse.h"
};

const char* minimal = "C 1,2,3 1,0,0 90\n"
                      "A 0.69 4,5,6\n"
                      "L 0.42 7,8,9\n"
;

TEST(Dummy, Dummy) {
    SUCCEED();
}
