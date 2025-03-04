#include"shared.h"

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
