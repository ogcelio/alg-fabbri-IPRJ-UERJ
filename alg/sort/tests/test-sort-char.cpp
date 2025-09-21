#include "gtest/gtest.h"
#include "../sort-char.h"
#include <cstring>

TEST(SortCharTest, Simple) {
    char str[] = "badcfe";
    sort_char(str);
    ASSERT_STREQ("abcdef", str);
}
