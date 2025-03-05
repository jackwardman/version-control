#include "shared.h"

// Function to restore files from a commit
void checkout(const std::string& commitHash) {
    if (!isRepositoryInitialized()) {
        std::cerr << "Error: No MyGit repository found. Run './mygit init' first.\n";
        exit(EXIT_FAILURE);
    }

    std::string commitPath = COMMITS_DIR + "/" + commitHash;
    if (!fs::exists(commitPath)) {
        std::cerr << "Error: Commit " << commitHash << " not found.\n";
        return;
    }

    std::ifstream commitFile(commitPath);
    if (!commitFile) {
        std::cerr << "Error: Unable to open commit file.\n";
        return;
    }

    std::string line;
    bool fileSection = false;
    while (std::getline(commitFile, line)) {
        if (line.find("Commit message:") == 0) {
            fileSection = true;  // Start reading files after this line
            continue;
        }
        if (line.find("Timestamp:") == 0) {
            break;  // Stop reading at the timestamp
        }

        if (fileSection) {
            std::istringstream iss(line);
            std::string filename, fileHash;
            if (iss >> filename >> fileHash) {
                std::string objectPath = OBJECTS_DIR + "/" + fileHash;
                if (fs::exists(objectPath)) {
                    std::ifstream objectFile(objectPath, std::ios::binary);
                    std::ofstream restoredFile(filename, std::ios::binary);
                    restoredFile << objectFile.rdbuf();
                    objectFile.close();
                    restoredFile.close();
                    std::cout << "Restored: " << filename << "\n";
                } else {
                    std::cerr << "Warning: File " << filename << " missing in objects.\n";
                }
            }
        }
    }
    commitFile.close();

    // Update HEAD to reflect the checked-out commit
    updateHead(commitHash);
    std::cout << "Checked out commit: " << commitHash << "\n";
}

// Function to switch branches
void checkoutBranch(const std::string& branchName) {
    if (!isRepositoryInitialized()) {
        std::cerr << "Error: No MyGit repository found. Run './mygit init' first.\n";
        exit(EXIT_FAILURE);
    }

    std::string branchPath = REFS_DIR + "/" + branchName;
    if (!fs::exists(branchPath)) {
        std::cerr << "Error: Branch '" << branchName << "' does not exist.\n";
        return;
    }

    // Update HEAD to point to the new branch
    updateHead("ref: refs/heads/" + branchName);
    std::cout << "Switched to branch '" << branchName << "'\n";
}
