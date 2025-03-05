#include "shared.h"

void logCommits() {
    if (!isRepositoryInitialized()) {
        std::cerr << "Error: No MyGit repository found. Run './mygit init' first.\n";
        exit(EXIT_FAILURE);
    }

    std::string commitHash = getHeadCommit();
    if (commitHash.empty()) {
        std::cout << "No commits found.\n";
        return;
    }

    std::cout << "Commit history:\n\n";

    while (!commitHash.empty()) {
        std::string commitPath = COMMITS_DIR + "/" + commitHash;
        std::ifstream commitFile(commitPath);
        
        if (!commitFile) {
            std::cerr << "Error: Commit file " << commitPath << " not found.\n";
            return;
        }

        std::string line, commitMessage, timestamp, parentCommit;
        while (std::getline(commitFile, line)) {
            if (line.rfind("Commit message:", 0) == 0) {
                commitMessage = line.substr(15);  // Extract commit message
                commitMessage.erase(0, commitMessage.find_first_not_of(" ")); // Trim leading spaces
            } else if (line.rfind("Parent:", 0) == 0) {
                parentCommit = line.substr(7);  // Extract parent hash
                parentCommit.erase(0, parentCommit.find_first_not_of(" ")); // Trim leading spaces
                parentCommit.erase(parentCommit.find_last_not_of(" \n\r\t") + 1); // Trim trailing spaces/newlines
            } else if (line.rfind("Timestamp:", 0) == 0) {
                timestamp = line.substr(10);  // Extract timestamp
            }
        }

        // Convert timestamp to human-readable format
        std::time_t timeValue = std::stoll(timestamp);
        std::string readableTime = std::ctime(&timeValue);
        readableTime.pop_back();  // Remove newline from ctime()

        std::cout << "Commit: " << commitHash << "\n";
        std::cout << "Date:   " << readableTime << "\n";
        std::cout << "Message: " << commitMessage << "\n";
        if (!parentCommit.empty()) {
            std::cout << "Parent: " << parentCommit << "\n";
        }
        std::cout << "\n";

        // Move to the parent commit
        commitHash = parentCommit.empty() ? "" : parentCommit;
    }
}
