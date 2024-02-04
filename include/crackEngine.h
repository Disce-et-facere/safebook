#ifndef CRACK_ENGINE_H
#define CRACK_ENGINE_H

#include <condition_variable>
// #include <cuda_runtime.h>
#include <iostream>
#include <mutex>
#include <queue>
#include <string>
#include <thread>
#include <vector>

class CrackEngine {
public:
  CrackEngine();
  ~CrackEngine();

  void initiate(size_t numThreads, size_t numCUDAThreads, size_t chunkSize);
  void setTarget(const std::string &hashFilePath);
  void setSource(const std::string &passwordFilePath);
  void safeShutdown();

  std::vector<std::string> getCrackedPasswords();

private:
  std::mutex hashListMutex;
  std::mutex passwordQueueMutex;
  std::condition_variable passwordQueueCondition;

  std::vector<std::string> hashList;
  std::queue<std::string> passwordQueue;
  std::vector<std::string> crackedPasswords;

  bool processingDone;

  void loadHashesFromFile(const std::string &filePath);
  void loadPasswordsFromFile(const std::string &filePath);
  void initializePasswordQueue();
  void processHashes();
  void processPasswordsOnGPU();
};

#endif // CRACK_ENGINE_H
