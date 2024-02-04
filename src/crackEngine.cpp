#include <crackEngine.h>

CrackEngine::CrackEngine() : processingDone(false) {}

CrackEngine::~CrackEngine() { safeShutdown(); }

void CrackEngine::initiate(size_t numThreads, size_t numCUDAThreads,
                           size_t chunkSize) {

  loadHashesFromFile("hashes.txt");

  loadPasswordsFromFile("passwords.txt");

  initializePasswordQueue();

  std::vector<std::thread> threads;
  for (size_t i = 0; i < numThreads; ++i) {
    threads.emplace_back(&CrackEngine::processHashes, this);
  }

  std::vector<std::thread> cudaThreads;
  for (size_t i = 0; i < numCUDAThreads; ++i) {
    cudaThreads.emplace_back(&CrackEngine::processPasswordsOnGPU, this);
  }

  for (auto &thread : threads) {
    thread.join();
  }

  for (auto &thread : cudaThreads) {
    thread.join();
  }
}

void CrackEngine::setTarget(const std::string &hashFilePath) {
  loadHashesFromFile(hashFilePath);
}

void CrackEngine::setSource(const std::string &passwordFilePath) {

  loadPasswordsFromFile(passwordFilePath);
}

void CrackEngine::safeShutdown() {
  processingDone = true;
  passwordQueueCondition.notify_all();
}

std::vector<std::string> CrackEngine::getCrackedPasswords() {

  return crackedPasswords;
}

void CrackEngine::loadHashesFromFile(const std::string &filePath) {}

void CrackEngine::loadPasswordsFromFile(const std::string &filePath) {}

void CrackEngine::initializePasswordQueue() {}

void CrackEngine::processHashes() {}

void CrackEngine::processPasswordsOnGPU() {
  while (true) {
    std::unique_lock<std::mutex> lock(passwordQueueMutex);

    passwordQueueCondition.wait(
        lock, [&] { return !passwordQueue.empty() || processingDone; });

    if (!passwordQueue.empty()) {
      std::string password = passwordQueue.front();
      passwordQueue.pop();
      lock.unlock();

      {
        std::lock_guard<std::mutex> hashListLock(hashListMutex);
        crackedPasswords.push_back("Cracked: " + password);
      }
    } else if (processingDone) {

      break;
    }
  }
}
