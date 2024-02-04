#ifndef USERMANAGER_H
#define USERMANAGER_H

#include <string>
#include <unordered_set>

class UserManager {
public:
  // Public functions
  int loginUser(const std::string &username, const std::string &password);
  int registerUser(const std::string &username, const std::string &password);

protected:
  const std::string filename = "../resources/users.txt";

private:
  // Private functions
  void storeUser(const std::string &username, const std::string &password,
                 const std::string &salt);

  bool checkUser(const std::string &username);
  std::string createSalt();
  bool isSaltUnique(const std::string &salt);

  std::unordered_set<std::string> existingSalts;
  std::string generateRandomSalt(int lenght);
  std::string createHash(const std::string &password, const std::string &salt);
  bool isPasswordValid(const std::string &password);
  bool isUsernameValid(const std::string &username);
};

#endif // USERMANAGER_H
