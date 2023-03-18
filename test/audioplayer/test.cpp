#include <iostream>
#include <gtest/gtest.h>

TEST(RendererTest, SteadyWindow)
{
    
    EXPECT_TRUE(true);
}

int main(int argc, char** argv)
{
    printf("Running main() from %s\n", __FILE__);
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}