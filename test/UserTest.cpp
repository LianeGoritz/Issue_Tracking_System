#include "User.h"
#include "gtest/gtest.h"

TEST(TestUser, constructorTest) {
  User u(12, "Bob", "Smith", "HisUserName");

  EXPECT_EQ(12, u.getID());
  EXPECT_EQ("Bob", u.getFirstName());
  EXPECT_EQ("Smith", u.getLastName());
  EXPECT_EQ("HisUserName", u.getUsername());

  User u2(23, "Jane", "Doe", "HerUserName");

  EXPECT_EQ(23, u2.getID());
  EXPECT_EQ("Jane", u2.getFirstName());
  EXPECT_EQ("Doe", u2.getLastName());
  EXPECT_EQ("HerUserName", u2.getUsername());
}

TEST(TestUser, updateFirstNameTest) {
  User u(15, "Bob", "Smith", "MyUserName");

  EXPECT_EQ("Bob", u.getFirstName());
  EXPECT_EQ("Smith", u.getLastName());

  u.updateFirstName("Joe");
  EXPECT_EQ("Joe", u.getFirstName());
  EXPECT_EQ("Smith", u.getLastName());
  u.updateFirstName("Linda");
  EXPECT_EQ("Linda", u.getFirstName());
  EXPECT_EQ("Smith", u.getLastName());
}

TEST(TestUser, updateLastNameTest) {
  User u(15, "Bob", "Smith", "MyUserName");

  EXPECT_EQ("Bob", u.getFirstName());
  EXPECT_EQ("Smith", u.getLastName());

  u.updateLastName("Johnson");
  EXPECT_EQ("Bob", u.getFirstName());
  EXPECT_EQ("Johnson", u.getLastName());
  u.updateLastName("Henderson");
  EXPECT_EQ("Bob", u.getFirstName());
  EXPECT_EQ("Henderson", u.getLastName());
}

TEST(TestUser, updateUsernameTest) {
  User u(15, "Bob", "Smith", "MyUserName");

  EXPECT_EQ("MyUserName", u.getUsername());

  u.updateUsername("NewOne");
  EXPECT_EQ("NewOne", u.getUsername());
  u.updateUsername("NewUsername");
  EXPECT_EQ("NewUsername", u.getUsername());
}

TEST(TestUser, getIDTest) {
  User u(12, "Bob", "Smith", "MyUserName");
  User u2(15, "Bob", "Smith", "MyUserName");

  EXPECT_EQ(12, u.getID());
  EXPECT_EQ(15, u2.getID());
}

TEST(TestUser, getFullNameTest) {
  User u(15, "Bob", "Smith", "MyUserName");
  User u2(15, "Jane", "Doe", "MyUserName");

  EXPECT_EQ("Bob Smith", u.getFullName());
  EXPECT_EQ("Jane Doe", u2.getFullName());
}

TEST(TestUser, getFirstNameTest) {
  User u(15, "Bob", "Smith", "MyUserName");
  User u2(15, "Jane", "Smith", "MyUserName");

  EXPECT_EQ("Bob", u.getFirstName());
  EXPECT_EQ("Jane", u2.getFirstName());
}

TEST(TestUser, getLastNameTest) {
  User u(15, "Jane", "Smith", "MyUserName");
  User u2(15, "Jane", "Doe", "MyUserName");

  EXPECT_EQ("Smith", u.getLastName());
  EXPECT_EQ("Doe", u2.getLastName());
}

TEST(TestUser, getUsernameTest) {
  User u(15, "Bob", "Smith", "MyUserName");
  User u2(15, "Bob", "Smith", "HisUserName");

  EXPECT_EQ("MyUserName", u.getUsername());
  EXPECT_EQ("HisUserName", u2.getUsername());
}
