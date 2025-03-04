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
const std::string INDEX_FILE = REPO_DIR + "/index";

// Function to check if the repository is initialized
bool isRepositoryInitialized() {
    return fs::exists(REPO_DIR);
}

// Function to compute SHA-1 hash of a file content
std::string computeSHA1(const std::string& content) {
    unsigned char hash[SHA_DIGEST_LENGTH];
    SHA1(reinterpret_cast<const unsigned char*>(content.c_str()), content.size(), hash);

    std::ostringstream oss;
    for (unsigned char byte : hash) {
        oss << std::hex << (int)byte;
    }
    return oss.str();
}

// Function to read file content
std::string readFileContent(const std::string& filename) {
    std::ifstream file(filename, std::ios::binary);
    if (!file) {
        std::cerr << "Error: Could not open file " << filename << "\n";
        exit(EXIT_FAILURE);
    }
    std::ostringstream ss;
    ss << file.rdbuf();
    return ss.str();
}
