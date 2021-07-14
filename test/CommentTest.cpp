#include "Comment.h"
#include "gtest/gtest.h"

TEST(TestComment, constructorTest) {
  Comment c(150, 10, 007, "comment description");

  EXPECT_EQ(150, c.getID());
  EXPECT_EQ(10, c.getIssueID());
  EXPECT_EQ(007, c.getUserID());
  EXPECT_EQ("comment description", c.getValue());

  Comment c2(1, 2, 20, "another description");

  EXPECT_EQ(1, c2.getID());
  EXPECT_EQ(2, c2.getIssueID());
  EXPECT_EQ(20, c2.getUserID());
  EXPECT_EQ("another description", c2.getValue());
}

TEST(TestComment, getIDTest) {
  Comment c(15, 39, 100, "test description");
  Comment c2(140, 39, 100, "test description");

  EXPECT_EQ(15, c.getID());
  EXPECT_EQ(140, c2.getID());
}

TEST(TestComment, getIssueIDTest) {
  Comment c(15, 39, 100, "test description");
  Comment c2(15, 12, 100, "test description");

  EXPECT_EQ(39, c.getIssueID());
  EXPECT_EQ(12, c2.getIssueID());
}

TEST(TestComment, getUserIDTest) {
  Comment c(15, 12, 7, "test description");
  Comment c2(15, 12, 100, "test description");

  EXPECT_EQ(7, c.getUserID());
  EXPECT_EQ(100, c2.getUserID());
}

TEST(TestComment, getValueTest) {
  Comment c(15, 12, 100, "test description");
  Comment c2(15, 12, 100, "different description");

  EXPECT_EQ("test description", c.getValue());
  EXPECT_EQ("different description", c2.getValue());
}
