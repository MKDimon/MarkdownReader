#include <gmock/gmock-matchers.h>
#include <gtest/gtest.h>

#include "blockhandlers.h"
#include "blocks.h"

using namespace testing;

TEST(BlocksTest, WarningBlock_1) {
    WarningBlock block("warning", "some content");
    ASSERT_EQ("Warning (warning):\nsome content\n", block.renderAsText());
}

TEST(BlockHandlersTests, WarningHandlersTests_1)
{
    WarningBlockHandler handler;
}
