#include "init.h"
#include "stage.h"
#include "commit.h"

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr   << "Usage:\n"
                    << "  " << argv[0] << " init\n"
                    << "  " << argv[0] << " add <filename>\n"
                    << "  " << argv[0] << " commit <message>\n";
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
    }
    return 0;
}
