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
const std::string REFS_DIR = REPO_DIR + "/refs/heads";
const std::string HEAD_FILE = REPO_DIR + "/HEAD";
const std::string INDEX_FILE = REPO_DIR + "/index";

// Function to check if the repository is initialized
bool isRepositoryInitialized() {
    return fs::exists(REPO_DIR);
}

// Function to create directories
void createDirectory(const std::string& path) {
    if (!fs::exists(path)) {
        fs::create_directory(path);
    }
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

// Function to update HEAD file with the latest commit hash
void updateHead(const std::string& commitHash) {
    std::ofstream headFile(HEAD_FILE);
    if (!headFile) {
        std::cerr << "Error: Unable to update HEAD file.\n";
        return;
    }
    headFile << commitHash << "\n";
}

// Function to get the current HEAD reference
std::string getHeadReference() {
    std::ifstream headFile(HEAD_FILE);
    if (!headFile) return "";
    
    std::string ref;
    std::getline(headFile, ref);
    return ref;
}

// Function to get the latest commit from HEAD
std::string getHeadCommit() {
    std::string headRef = getHeadReference();
    if (headRef.rfind("ref: ", 0) == 0) {  // If HEAD points to a branch
        std::string branchPath = REPO_DIR + "/" + headRef.substr(5);
        std::ifstream branchFile(branchPath);
        if (!branchFile) return "";
        std::string commitHash;
        std::getline(branchFile, commitHash);
        return commitHash;
    }
    return headRef;  // Otherwise, HEAD directly contains a commit hash
}
