#include "shared.h"

// Function to add file to the staging area
void addFile(const std::string& filename) {
    if (!isRepositoryInitialized()) {
        std::cerr << "Error: No MyGit repository found. Run './mygit init' first.\n";
        exit(EXIT_FAILURE);
    }

    // Read file content
    std::string content = readFileContent(filename);
    
    // Compute SHA-1 hash
    std::string hash = computeSHA1(content);
    
    // Store file in .mygit/objects/
    std::string objectPath = OBJECTS_DIR + "/" + hash;
    std::ofstream objectFile(objectPath, std::ios::binary);
    objectFile << content;
    objectFile.close();

    // Update the index file
    std::ofstream indexFile(INDEX_FILE, std::ios::app);
    indexFile << filename << " " << hash << "\n";
    indexFile.close();

    std::cout << "Added " << filename << " to staging area.\n";
}
