#include <string>
#include <vector>
#include "KnickKnacker.h"

KnickKnacker::~KnickKnacker() {
  delete broker;
}

unsigned int KnickKnacker::createIssue(std::string title, std::string desc,
   Issue::Status status, Issue::Priority priority) {
  std::vector<Issue*> issues = broker->readAllIssues();
  unsigned int id;
  if (!issues.empty()) {
    id = issues.back()->getID() + 1;
  } else {
    id = 1;
  }
  for (Issue* i : issues) {
    delete i;
  }
  issues.clear();
  Issue* issue = new Issue(id, title, desc, status, priority);
  broker->appendIssue(issue);
  delete issue;
  return id;
}

Issue KnickKnacker::getIssueByID(unsigned int id) {
  Issue* pIssue = broker->getIssueByID(id);
  Issue issue = *pIssue;
  delete pIssue;
  return issue;
}

bool KnickKnacker::updateIssue(unsigned int id, std::string title,
   std::string desc, Issue::Status status, Issue::Priority priority) {
  std::vector<Issue*> issues = broker->readAllIssues();
  bool updated = false;
  for (Issue* i : issues) {
    if (i->getID() == id) {
      if (!title.empty()) {
        i->updateTitle(title);
      }
      if (!desc.empty()) {
        i->updateDescription(desc);
      }
      i->updateStatus(status);
      i->updatePriority(priority);
      updated = true;
      break;
    }
  }
  broker->overwriteIssues(issues);
  for (Issue* i : issues) {
    delete i;
  }
  issues.clear();
  return updated;
}

bool KnickKnacker::deleteIssueByID(unsigned int id) {
  std::vector<Issue*> issues = broker->readAllIssues();
  bool found = false;
  for (std::vector<Issue*>::iterator it = issues.begin();
    it != issues.end(); ++it) {
    if ((*it)->getID() == id) {
      it = issues.erase(it);
      found = true;
      break;
    }
  }
  broker->overwriteIssues(issues);
  for (Issue* i : issues) {
    delete i;
  }
  issues.clear();
  return found;
}

std::vector<Issue> KnickKnacker::getAllIssues() {
  std::vector<Issue> issues;
  std::vector<Issue*> pIssues = broker->readAllIssues();
  for (Issue* i : pIssues) {
    issues.push_back(*i);
    delete i;
  }
  pIssues.clear();
  return issues;
}

std::vector<User> KnickKnacker::getAllUsers() {
  std::vector<User> users;
  std::vector<User*> pUsers = broker->readAllUsers();
  for (User* u : pUsers) {
    users.push_back(*u);
    delete u;
  }
  pUsers.clear();
  return users;
}

unsigned int KnickKnacker::createUser(std::string first, std::string last,
   std::string username) {
  std::vector<User*> users = broker->readAllUsers();
  unsigned int id;
  if (!users.empty()) {
    id = users.back()->getID() + 1;
  } else {
    id = 1;
  }
  for (User* u : users) {
    delete u;
  }
  users.clear();
  User* user = new User(id, first, last, username);
  broker->appendUser(user);
  delete user;
  return id;
}

User KnickKnacker::getUserByID(unsigned int id) {
  User* pUser = broker->getUserByID(id);
  User user = *pUser;
  delete pUser;
  return user;
}

unsigned int KnickKnacker::createComment(unsigned int i_id, unsigned int u_id,
   std::string value) {
  std::vector<Comment*> comments = broker->readAllComments();
  unsigned int id;
  if (!comments.empty()) {
    id = comments.back()->getID() + 1;
  } else {
    id = 1;
  }
  for (Comment* c : comments) {
    delete c;
  }
  comments.clear();
  Comment* comment = new Comment(id, i_id, u_id, value);
  broker->appendComment(comment);
  delete comment;
  return id;
}

std::vector<Comment> KnickKnacker::getComments(unsigned int i_id) {
  std::vector<Comment*> pComments = broker->getCommentsByIID(i_id);
  std::vector<Comment> comments;
  for (Comment* c : pComments) {
    comments.push_back(*c);
    delete c;
  }
  pComments.clear();
  return comments;
}
