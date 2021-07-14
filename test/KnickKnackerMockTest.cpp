#include "KnickKnacker.h"
#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include <vector>

using namespace ::testing;

class MockKnickKnackerIO : public KnickKnackerIO {
 public:
   explicit MockKnickKnackerIO() {}
   virtual ~MockKnickKnackerIO() {}

   MOCK_METHOD0(readAllIssues, std::vector<Issue*>());
   MOCK_METHOD1(getIssueByID, Issue*(unsigned int id));
   MOCK_METHOD1(getUserByID, User*(unsigned int id));
   MOCK_METHOD1(getCommentsByIID, std::vector<Comment*>(unsigned int i_id));
   MOCK_METHOD0(readAllComments, std::vector<Comment*>());
   MOCK_METHOD0(readAllUsers, std::vector<User*>());
   MOCK_METHOD1(overwriteIssues, void(std::vector<Issue*> issues));
   MOCK_METHOD1(overwriteComments, void(std::vector<Comment*> comments));
   MOCK_METHOD1(overwriteUsers, void(std::vector<User*> users));
   MOCK_METHOD1(appendIssue, void(Issue* issue));
   MOCK_METHOD1(appendComment, void(Comment* comment));
   MOCK_METHOD1(appendUser, void(User* user));
};

TEST(KnickKnackerMockTest, createInitialIssueTest) {
  std::vector<Issue*>  iss;
  MockKnickKnackerIO* mockIO = new MockKnickKnackerIO();

  Expectation read =
  EXPECT_CALL(*mockIO, readAllIssues())
  .Times(1)
  .WillOnce(Return(iss));

  EXPECT_CALL(*mockIO, appendIssue(_))
  .Times(1)
  .After(read)
  .WillOnce(Return());

  KnickKnacker* k = new KnickKnacker(mockIO);
  unsigned int id = k->createIssue("title", "testing", Issue::New, Issue::Top);
  EXPECT_EQ(1, id);
  delete k;
}

TEST(KnickKnackerMockTest, createAdditionalIssueTest) {
  std::vector<Issue*>  iss;
  Issue* issue = new Issue(1, "title", "test", 0, Issue::New, Issue::Low, "os");
  iss.push_back(issue);
  MockKnickKnackerIO* mockIO = new MockKnickKnackerIO();

  Expectation read =
  EXPECT_CALL(*mockIO, readAllIssues())
  .Times(1)
  .WillOnce(Return(iss));

  EXPECT_CALL(*mockIO, appendIssue(_))
  .Times(1)
  .After(read)
  .WillOnce(Return());

  KnickKnacker* k = new KnickKnacker(mockIO);
  unsigned int id = k->createIssue("title", "testing", Issue::New, Issue::Top);
  EXPECT_EQ(2, id);
  delete k;
}

TEST(KnickKnackerMockTest, getIssueByIDTest) {
  Issue* issue = new Issue(2, "title", "test", Issue::New, Issue::Low);
  MockKnickKnackerIO* mockIO = new MockKnickKnackerIO();

  EXPECT_CALL(*mockIO, getIssueByID(_))
  .Times(1)
  .WillOnce(Return(issue));

  KnickKnacker* k = new KnickKnacker(mockIO);
  Issue issueR = k->getIssueByID(2);
  EXPECT_EQ(2, issueR.getID());
  EXPECT_EQ("title", issueR.getTitle());
  EXPECT_EQ("test", issueR.getDescription());
  EXPECT_EQ("New", issueR.getStatus());
  EXPECT_EQ("Low", issueR.getPriority());
  EXPECT_EQ("No OS", issueR.getOS());
  delete k;
}

TEST(KnickKnackerMockTest, updateIssueTest) {
  std::vector<Issue*> iss;
  Issue* issue = new Issue(2, "title", "test", Issue::New, Issue::Low);
  iss.push_back(issue);
  MockKnickKnackerIO* mockIO = new MockKnickKnackerIO();

  Expectation read =
  EXPECT_CALL(*mockIO, readAllIssues())
  .Times(1)
  .WillOnce(Return(iss));
  EXPECT_CALL(*mockIO, overwriteIssues(_))
  .Times(1)
  .After(read)
  .WillOnce(Return());

  KnickKnacker* k = new KnickKnacker(mockIO);
  bool updateC = k->updateIssue(2, "new title", "new test", Issue::Assigned,
  Issue::Top);
  EXPECT_EQ(true, updateC);
  delete k;
}

TEST(KnickKnackerMockTest, deleteIssueByIDTest) {
  std::vector<Issue*> iss;
  Issue* issue = new Issue(2, "title", "test", Issue::New, Issue::Low);
  iss.push_back(issue);
  MockKnickKnackerIO* mockIO = new MockKnickKnackerIO();

  Expectation read =
  EXPECT_CALL(*mockIO, readAllIssues())
  .Times(1)
  .WillOnce(Return(iss));

  EXPECT_CALL(*mockIO, overwriteIssues(_))
  .Times(1)
  .After(read)
  .WillOnce(Return());

  KnickKnacker* k = new KnickKnacker(mockIO);
  bool updateC = k->deleteIssueByID(2);
  EXPECT_EQ(true, updateC);
  delete k;
}

TEST(KnickKnackerMockTest, getAllIssuesEmptyTest) {
  std::vector<Issue*> iss;
  MockKnickKnackerIO* mockIO = new MockKnickKnackerIO();

  EXPECT_CALL(*mockIO, readAllIssues())
  .Times(1)
  .WillOnce(Return(iss));

  KnickKnacker* k = new KnickKnacker(mockIO);
  std::vector<Issue> all = k->getAllIssues();
  EXPECT_EQ(0, all.size());
  delete k;
}

TEST(KnickKnackerMockTest, getAllIssuesNotEmptyTest) {
  std::vector<Issue*> iss;
  Issue* issue = new Issue(2, "title", "test", Issue::New, Issue::Low);
  Issue* issue2 = new Issue(3, "title2", "test2", Issue::Assigned, Issue::High);
  iss.push_back(issue);
  iss.push_back(issue2);
  MockKnickKnackerIO* mockIO = new MockKnickKnackerIO();

  EXPECT_CALL(*mockIO, readAllIssues())
  .Times(1)
  .WillOnce(Return(iss));

  KnickKnacker* k = new KnickKnacker(mockIO);
  std::vector<Issue> all = k->getAllIssues();
  EXPECT_EQ(2, all.size());
  EXPECT_EQ(2, all[0].getID());
  EXPECT_EQ(3, all[1].getID());
  EXPECT_EQ("title", all[0].getTitle());
  EXPECT_EQ("title2", all[1].getTitle());
  EXPECT_EQ("test", all[0].getDescription());
  EXPECT_EQ("test2", all[1].getDescription());
  EXPECT_EQ("New", all[0].getStatus());
  EXPECT_EQ("Assigned", all[1].getStatus());
  EXPECT_EQ("Low", all[0].getPriority());
  EXPECT_EQ("High", all[1].getPriority());
  EXPECT_TRUE(all[0].getOS() == all[1].getOS());
  delete k;
}

TEST(KnickKnackerMockTest, getAllUsersEmptyTest) {
  std::vector<User*> users;
  MockKnickKnackerIO* mockIO = new MockKnickKnackerIO();

  EXPECT_CALL(*mockIO, readAllUsers())
  .Times(1)
  .WillOnce(Return(users));

  KnickKnacker* k = new KnickKnacker(mockIO);
  std::vector<User> all = k->getAllUsers();
  EXPECT_EQ(0, all.size());
  delete k;
}

TEST(KnickKnackerMockTest, getAllUsersNotEmptyTest) {
  std::vector<User*> users;
  User* user1 = new User(1, "First1", "Last1", "User1");
  User* user2 = new User(2, "First2", "Last2", "User2");
  users.push_back(user1);
  users.push_back(user2);
  MockKnickKnackerIO* mockIO = new MockKnickKnackerIO();

  EXPECT_CALL(*mockIO, readAllUsers())
  .Times(1)
  .WillOnce(Return(users));

  KnickKnacker* k = new KnickKnacker(mockIO);
  std::vector<User> all = k->getAllUsers();
  EXPECT_EQ(2, all.size());
  EXPECT_EQ(1, all[0].getID());
  EXPECT_EQ(2, all[1].getID());
  EXPECT_EQ("First1", all[0].getFirstName());
  EXPECT_EQ("First2", all[1].getFirstName());
  EXPECT_EQ("Last1", all[0].getLastName());
  EXPECT_EQ("Last2", all[1].getLastName());
  EXPECT_EQ("User1", all[0].getUsername());
  EXPECT_EQ("User2", all[1].getUsername());
  delete k;
}

TEST(KnickKnackerMockTest, createInitialUserTest) {
  std::vector<User*> users;
  MockKnickKnackerIO* mockIO = new MockKnickKnackerIO();

  Expectation read =
  EXPECT_CALL(*mockIO, readAllUsers())
  .Times(1)
  .WillOnce(Return(users));

  EXPECT_CALL(*mockIO, appendUser(_))
  .Times(1)
  .After(read)
  .WillOnce(Return());

  KnickKnacker* k = new KnickKnacker(mockIO);
  unsigned int id = k->createUser("First2", "Last2", "User2");
  EXPECT_EQ(1, id);
  delete k;
}

TEST(KnickKnackerMockTest, createAdditionalUserTest) {
  std::vector<User*> users;
  User* user = new User(1, "First", "Last", "User");
  users.push_back(user);
  MockKnickKnackerIO* mockIO = new MockKnickKnackerIO();

  Expectation read =
  EXPECT_CALL(*mockIO, readAllUsers())
  .Times(1)
  .WillOnce(Return(users));

  EXPECT_CALL(*mockIO, appendUser(_))
  .Times(1)
  .After(read)
  .WillOnce(Return());

  KnickKnacker* k = new KnickKnacker(mockIO);
  unsigned int id = k->createUser("First2", "Last2", "User2");
  EXPECT_EQ(2, id);
  delete k;
}

TEST(KnickKnackerMockTest, getUserByIDTest) {
  User* user = new User(30, "First", "Last", "User");
  MockKnickKnackerIO* mockIO = new MockKnickKnackerIO();

  EXPECT_CALL(*mockIO, getUserByID(_))
  .Times(1)
  .WillOnce(Return(user));

  KnickKnacker* k = new KnickKnacker(mockIO);
  User userR = k->getUserByID(30);
  EXPECT_EQ(30, userR.getID());
  EXPECT_EQ("First", userR.getFirstName());
  EXPECT_EQ("Last", userR.getLastName());
  EXPECT_EQ("User", userR.getUsername());
  delete k;
}

TEST(KnickKnackerMockTest, createInitialCommentTest) {
  std::vector<Comment*> cmts;
  MockKnickKnackerIO* mockIO = new MockKnickKnackerIO();

  Expectation read =
  EXPECT_CALL(*mockIO, readAllComments())
  .Times(1)
  .WillOnce(Return(cmts));

  EXPECT_CALL(*mockIO, appendComment(_))
  .Times(1)
  .After(read)
  .WillOnce(Return());

  KnickKnacker* k = new KnickKnacker(mockIO);
  unsigned int id = k->createComment(10, 259, "testing description");
  EXPECT_EQ(1, id);
  delete k;
}

TEST(KnickKnackerMockTest, createAdditionalCommentTest) {
  std::vector<Comment*> cmts;
  Comment* com = new Comment(1, 12, 242, "test description");
  cmts.push_back(com);
  MockKnickKnackerIO* mockIO = new MockKnickKnackerIO();

  Expectation read =
  EXPECT_CALL(*mockIO, readAllComments())
  .Times(1)
  .WillOnce(Return(cmts));

  EXPECT_CALL(*mockIO, appendComment(_))
  .Times(1)
  .After(read)
  .WillOnce(Return());

  KnickKnacker* k = new KnickKnacker(mockIO);
  unsigned int id = k->createComment(10, 259, "testing description");
  EXPECT_EQ(2, id);
  delete k;
}

TEST(KnickKnackerMockTest, getCommentsEmptyTest) {
  std::vector<Comment*> cmts;
  MockKnickKnackerIO* mockIO = new MockKnickKnackerIO();

  EXPECT_CALL(*mockIO, getCommentsByIID(_))
  .Times(1)
  .WillOnce(Return(cmts));

  KnickKnacker* k = new KnickKnacker(mockIO);
  std::vector<Comment> all = k->getComments(12);
  EXPECT_EQ(0, all.size());
  delete k;
}

TEST(KnickKnackerMockTest, getCommentsNotEmptyTest) {
  std::vector<Comment*> cmts;
  Comment* com = new Comment(1, 15, 260, "test description1");
  Comment* com2 = new Comment(2, 15, 242, "test description2");
  cmts.push_back(com);
  cmts.push_back(com2);
  MockKnickKnackerIO* mockIO = new MockKnickKnackerIO();

  EXPECT_CALL(*mockIO, getCommentsByIID(_))
  .Times(1)
  .WillOnce(Return(cmts));

  KnickKnacker* k = new KnickKnacker(mockIO);
  std::vector<Comment> all = k->getComments(15);
  EXPECT_EQ(2, all.size());
  EXPECT_EQ(1, all[0].getID());
  EXPECT_EQ(2, all[1].getID());
  EXPECT_EQ(15, all[0].getIssueID());
  EXPECT_EQ(15, all[1].getIssueID());
  EXPECT_EQ(260, all[0].getUserID());
  EXPECT_EQ(242, all[1].getUserID());
  EXPECT_EQ("test description1", all[0].getValue());
  EXPECT_EQ("test description2", all[1].getValue());
  delete k;
}
