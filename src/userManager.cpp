#include <UserManager.h>
#include <fstream>
#include <hashManager.h>
#include <iostream>
#include <random>
#include <regex>
#include <sstream>

int UserManager::loginUser(const std::string &username,
                           const std::string &password) {
  if (!checkUser(username)) {
    return 1; // User does not exist
  }

  std::ifstream file(filename);
  std::string line;

  while (std::getline(file, line)) {
    std::istringstream iss(line);
    std::string storedUsername, storedPassword, storedSalt;
    std::getline(iss, storedUsername, ',');
    std::getline(iss, storedPassword, ',');
    std::getline(iss, storedSalt);

    if (storedUsername == username) {
      std::string newPasswordHash = createHash(password, storedSalt);

      if (newPasswordHash != storedPassword) {
        file.close();
        return 2; // incorrect password
      } else {
        file.close();
        return 0; // Login successful
      }
    }
  }

  file.close();
  return 1; // User does not exist
}

int UserManager::registerUser(const std::string &username,
                              const std::string &password) {

  if (!isUsernameValid(username) && !isPasswordValid(password)) {
    return 3; // Both username and password are incorrect
  } else if (!isUsernameValid(username)) {
    return 1; // Username is incorrect
  } else if (!isPasswordValid(password)) {
    return 2; // Password is incorrect
  }

  if (!checkUser(username)) {
    std::string salt = createSalt();
    std::string hashedPassword = createHash(password, salt);
    storeUser(username, hashedPassword, salt);
    std::cout << username + "," + hashedPassword + "," + salt << std::endl;
    return 0; // Registration successful

  } else {

    return 1; // Username already exists
  }
}

void UserManager::storeUser(const std::string &username,
                            const std::string &password,
                            const std::string &salt) {
  std::ofstream file(filename, std::ios::app);
  file << username << "," << password << "," << salt << std::endl;
  file.close();
}

bool UserManager::checkUser(const std::string &username) {
  std::ifstream file(filename);
  std::string line;

  while (std::getline(file, line)) {
    std::istringstream iss(line);
    std::string storedUsername;
    std::getline(iss, storedUsername, ',');

    if (storedUsername == username) {
      file.close();
      return true; // User found
    }
  }

  file.close();
  return false; // User not found
}

std::string UserManager::createSalt() {
  const int saltLength = 16;

  std::unordered_set<std::string> existingSalts;
  while (true) {
    std::string salt = generateRandomSalt(saltLength);

    if (isSaltUnique(salt)) {
      return salt;
    }
  }
}

bool UserManager::isSaltUnique(const std::string &salt) {
  std::ifstream file(filename);
  std::string line;

  // Read existing salts from the file
  while (std::getline(file, line)) {
    std::istringstream iss(line);
    std::string storedUsername, storedPassword, storedSalt;
    std::getline(iss, storedUsername, ',');
    std::getline(iss, storedPassword, ',');
    std::getline(iss, storedSalt);

    // Add the existing salt to the set
    existingSalts.insert(storedSalt);
  }

  file.close();

  // Check if the generated salt is unique
  return existingSalts.find(salt) == existingSalts.end();
}

std::string UserManager::generateRandomSalt(int length) {
  // Generate a random salt using a random number generator
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<> dis('!', '~'); // ASCII printable characters

  std::string salt;
  for (int i = 0; i < length; ++i) {
    salt += static_cast<char>(dis(gen));
  }

  return salt;
}
std::string UserManager::createHash(const std::string &password,
                                    const std::string &salt) {
  return HashManager::md5Hash(password + salt);
}

bool UserManager::isPasswordValid(const std::string &password) {

  if (password.length() < 8) {
    return false;
  }

  if (std::none_of(password.begin(), password.end(), ::isupper)) {
    return false;
  }

  if (std::none_of(password.begin(), password.end(), ::islower)) {
    return false;
  }

  if (std::none_of(password.begin(), password.end(), ::isdigit)) {
    return false;
  }

  if (std::all_of(password.begin(), password.end(), ::isalnum)) {
    return false;
  }

  return true;
}

bool UserManager::isUsernameValid(const std::string &username) {
  // Username must be in the format abc@abc.abc and must contain "@" and "."
  std::regex emailRegex("[A-Za-z0-9._%+-]+@[A-Za-z0-9.-]+\\.[A-Z|a-z]{2,}");
  return std::regex_match(username, emailRegex);
}
