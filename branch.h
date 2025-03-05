#include"shared.h"

// Function to create a new branch
void createBranch(const std::string& branchName) {
    if (!isRepositoryInitialized()) {
        std::cerr << "Error: No MyGit repository found. Run './mygit init' first.\n";
        exit(EXIT_FAILURE);
    }

    std::string headCommit = getHeadCommit();
    if (headCommit.empty()) {
        std::cerr << "Error: No commits in repository. Commit first before creating a branch.\n";
        return;
    }

    std::string branchPath = REFS_DIR + "/" + branchName;
    if (fs::exists(branchPath)) {
        std::cerr << "Error: Branch '" << branchName << "' already exists.\n";
        return;
    }

    std::ofstream branchFile(branchPath);
    if (!branchFile) {
        std::cerr << "Error: Unable to create branch file.\n";
        return;
    }
    branchFile << headCommit << "\n";

    std::cout << "Created branch '" << branchName << "' at commit " << headCommit << "\n";
}
