#include"shared.h"

// Function to initialize the repository
void init() {
    if (isRepositoryInitialized()) {
        std::cout << "Repository already initialized.\n";
        return;
    }

    createDirectory(REPO_DIR);
    createDirectory(OBJECTS_DIR);
    createDirectory(COMMITS_DIR);
    
    std::ofstream headFile(HEAD_FILE);
    if (!headFile) {
        std::cerr << "Error creating HEAD file.\n";
        exit(EXIT_FAILURE);
    }
    headFile << "ref: refs/heads/main\n";
    headFile.close();

    std::cout << "Initialized empty MyGit repository in " << REPO_DIR << "/\n";
}
