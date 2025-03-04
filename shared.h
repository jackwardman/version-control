#pragma once

#include <iostream>
#include <filesystem>
#include <fstream>
#include <sstream>
#include <openssl/sha.h>

namespace fs = std::filesystem;

const std::string REPO_DIR = ".mygit";
const std::string OBJECTS_DIR = REPO_DIR + "/objects";
const std::string COMMITS_DIR = REPO_DIR + "/commits";
const std::string HEAD_FILE = REPO_DIR + "/HEAD";

// Function to check if the repository is initialized
bool isRepositoryInitialized() {
    return fs::exists(REPO_DIR);
}
