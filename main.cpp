#include "branch.h"
#include "checkout.h"
#include "commit.h"
#include "init.h"
#include "log.h"
#include "stage.h"

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Usage:\n"
                  << "  " << argv[0] << " init\n"
                  << "  " << argv[0] << " add <filename>\n"
                  << "  " << argv[0] << " commit <message>\n"
                  << "  " << argv[0] << " log\n"
                  << "  " << argv[0] << " checkout <commit-hash>\n"
                  << "  " << argv[0] << " branch <branch-name>\n"
                  << "  " << argv[0] << " checkout <branch-name>\n";
        return EXIT_FAILURE;
    }

    std::string command = argv[1];

    if (command == "init") {
        init();
    } else if (command == "add") {
        if (argc < 3) {
            std::cerr << "Usage: " << argv[0] << " add <filename>\n";
            return EXIT_FAILURE;
        }
        addFile(argv[2]);
    } else if (command == "commit") {
        if (argc < 3) {
            std::cerr << "Usage: " << argv[0] << " commit <message>\n";
            return EXIT_FAILURE;
        }
        commit(argv[2]);
    } else if (command == "log") {
        logCommits();
    } else if (command == "branch") {
        if (argc < 3) {
            std::cerr << "Usage: " << argv[0] << " branch <branch-name>\n";
            return EXIT_FAILURE;
        }
        createBranch(argv[2]);
    } else if (command == "checkout") {
        if (argc < 3) {
            std::cerr << "Usage: " << argv[0] << " checkout <commit-hash>|<branch-name>\n";
            return EXIT_FAILURE;
        }
        std::string arg = argv[2];

        if (fs::exists(REFS_DIR + "/" + arg)) {
            checkoutBranch(arg);  // Branch checkout
        } else {
            checkout(arg);  // Commit checkout
        }
    } else {
        std::cerr << "Unknown command: " << command << "\n";
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}
