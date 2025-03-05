#include "shared.h"

void commit(const std::string& message) {
    if (!isRepositoryInitialized()) {
        std::cerr << "Error: No MyGit repository found. Run './mygit init' first.\n";
        exit(EXIT_FAILURE);
    }

    // Read staged files from index
    std::ifstream indexFile(INDEX_FILE);
    if (!indexFile) {
        std::cerr << "Error: No files staged for commit.\n";
        return;
    }

    std::ostringstream commitData;
    commitData << "Commit message: " << message << "\n";

    // Get the parent commit (current HEAD commit)
    std::string parentCommit = getHeadCommit();
    if (!parentCommit.empty()) {
        commitData << "Parent: " << parentCommit << "\n";
    }

    std::string line;
    while (std::getline(indexFile, line)) {
        commitData << line << "\n";
    }
    indexFile.close();

    // Generate a timestamp
    std::time_t now = std::time(nullptr);
    commitData << "Timestamp: " << now << "\n";

    // Compute commit hash
    std::string commitHash = computeSHA1(commitData.str());

    // Store commit data
    std::string commitPath = COMMITS_DIR + "/" + commitHash;
    std::ofstream commitFile(commitPath);
    commitFile << commitData.str();
    commitFile.close();

    // Update HEAD to reflect the new commit
    updateHead(commitHash);

    // Clear the staging area
    std::ofstream clearIndex(INDEX_FILE, std::ios::trunc);
    clearIndex.close();

    std::cout << "Committed changes with hash: " << commitHash << "\n";
}
