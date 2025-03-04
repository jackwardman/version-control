#include <iostream>
#include <filesystem>
#include <fstream>

namespace fs = std::filesystem;

const std::string REPO_DIR = ".mygit";
const std::string OBJECTS_DIR = REPO_DIR + "/objects";
const std::string COMMITS_DIR = REPO_DIR + "/commits";
const std::string HEAD_FILE = REPO_DIR + "/HEAD";

void createDirectory(const std::string& path) {
    if (!fs::exists(path)) {
        fs::create_directory(path);
    } else {
        std::cout << "Directory " << path << " already exists.\n";
    }
}

void writeHeadFile() {
    std::ofstream headFile(HEAD_FILE);
    if (!headFile) {
        std::cerr << "Error creating HEAD file.\n";
        exit(EXIT_FAILURE);
    }
    headFile << "ref: refs/heads/main\n";
    headFile.close();
}

void init() {
    if (fs::exists(REPO_DIR)) {
        std::cout << "Repository already initialized.\n";
        return;
    }

    createDirectory(REPO_DIR);
    createDirectory(OBJECTS_DIR);
    createDirectory(COMMITS_DIR);
    
    writeHeadFile();

    std::cout << "Initialized empty MyGit repository in " << REPO_DIR << "/\n";
}

int main() {
    init();
    return 0;
}
