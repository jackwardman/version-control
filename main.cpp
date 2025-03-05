#include "checkout.h"
#include "commit.h"
#include "init.h"
#include "log.h"
#include "stage.h"

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr   << "Usage:\n"
                    << "  " << argv[0] << " init\n"
                    << "  " << argv[0] << " add <filename>\n"
                    << "  " << argv[0] << " commit <message>\n"
                    << "  " << argv[0] << " log\n"
                    << "  " << argv[0] << " checkout <commit-hash>\n";
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
    } else if (command == "checkout") {
        if (argc < 3) {
            std::cerr << "Usage: " << argv[0] << " checkout <commit-hash>\n";
            return EXIT_FAILURE;
        }
        checkout(argv[2]);
    }
    return 0;
}
