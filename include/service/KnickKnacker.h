/**
* @class KnickKnacker
* @brief
* This class is meant to act as the main service of our issue
* tracking system.
* @author $Author: Victor Besson $
*/

#ifndef KNICKNACKER_H
#define KNICKNACKER_H

#include "KnickKnackerIO.h"
#include "Issue.h"
#include "User.h"
#include <vector>
#include <string>

class KnickKnacker {
 public:
  /**
  * Constructor.
  */
  KnickKnacker() : broker(new KnickKnackerIO()) {}
  /**
  * Constructor for testing.
  * @param b KnickKnackerIO used as the broker for the service.
  */
  KnickKnacker(KnickKnackerIO* b) : broker(b) {}
  /**
  * Destructor.
  */
  virtual ~KnickKnacker();
  /**
  * Creates and persists a new issue
  * @param title The title of the issue
  * @param desc A description of the issue
  * @param status The status of the issue
  * @param priority The priority of the issue
  * @return The unique identifier value of the created issue
  */
  unsigned int createIssue(std::string title, std::string desc,
    Issue::Status status, Issue::Priority priority);
  /**
  * Gets the issue specified by issue ID
  * @param id The unique identifier value of the issue
  * @return The issue matching the ID, nullptr if no match found
  */
  Issue getIssueByID(unsigned int id);
  /**
  * Updates the attributes in an issue matching the ID to the
  * values specified
  * @param id The ID of the issue to update
  * @param title The new title of the issue, empty string if unchanged
  * @param desc The new description of the issue, empty string if unchanged
  * @param status The new status of the issue
  * @param priority The new priority of the issue
  * @return The updated issue object, nullptr if the ID does not match
  *   any records
  */
  bool updateIssue(unsigned int id, std::string title,
    std::string desc, Issue::Status status, Issue::Priority priority);
  /**
  * Deletes an issue matching the ID
  * @param id The unique identifier of the issue to delete
  * @return true if the issue was successfully deleted
  */
  bool deleteIssueByID(unsigned int id);
  /**
  * Returns all the issues in a list
  * @return a list of all the issues
  */
  std::vector<Issue> getAllIssues();
  /**
  * Returns all the users in a list
  * @return a list of all the users
  */
  std::vector<User> getAllUsers();
  /**
  * Creates and persists a new user.
  * @param first The first name of the user.
  * @param last The last name of the user.
  * @param username The username of the user.
  * @return The unique identifier value of the created user
  */
  unsigned int createUser(std::string first, std::string last,
     std::string username);
  /**
  * Gets the user specified by user ID
  * @param id The unique identifier value of the user
  * @return The user matching the ID, nullptr if no match found
  */
  User getUserByID(unsigned int id);
  /**
  * Creates and persists a new comment.
  * @param i_id The issue id where the comment belongs.
  * @param u_id The user id of the user who created the comment.
  * @param value The comments string value.
  * @return The unique identifier value of the created comment.
  */
  unsigned int createComment(unsigned int i_id, unsigned int u_id,
     std::string value);
  /**
  * Gets the comments in a specific issue.
  * @param i_id The unique identifier value of the issue the comments are in.
  * @return Vector of comments that are related to a specific issue.
  */
  std::vector<Comment> getComments(unsigned int i_id);

 private:
  /**
  * broker to be used for IO
  */
  KnickKnackerIO* broker;
};

#endif // KNICKNACKER_H
