#include <gtest/gtest.h>
#include "dynagraph.h"
#include <string.h>

TEST(GraphTest, BasicAssertions) {
    no nos[2];
    strcpy(nos[0].nome, "A");
    nos[0].conexoes = NULL;
    strcpy(nos[1].nome, "B");
    nos[1].conexoes = NULL;

    liga(nos, nos + 1, 10);

    EXPECT_EQ(nos[0].conexoes->peso, 10);
    EXPECT_EQ(nos[1].conexoes->peso, 10);
    EXPECT_EQ(nos[0].conexoes->no, nos + 1);
    EXPECT_EQ(nos[1].conexoes->no, nos);
}
