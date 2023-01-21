#include "process.h"

int main() {
    int loop = 0;
    string input;
    vector<Process> processes;
    cout << COMMANDS << endl;
    ifstream fileStream(COMMANDS);
    while (std::getline(fileStream, input)) {
        cout << ">> Loop :  " << loop << endl;
        loop++;

        string command = getNthWord(input, 1);
        string ID = getNthWord(input, 2);
        int processIndex = getProcessIndex(processes, ID);

        if (command == "create_process") {
            string file_name = getNthWord(input, 3);
            Process process(ID, file_name);
            processes.push_back(process);
        }
        else if (processIndex == -1) {
            cout << "Process doesn't exist!" << endl;
        }
        else {
            if (command == "run_process") {
                processes.at(processIndex).run();
            }
            else if (command == "block_process") {
                processes.at(processIndex).block();
            }
            else if (command == "unblock_process") {
                processes.at(processIndex).unblock();
            }
            else if (command == "kill_process") {
                processes.at(processIndex).kill(processes);
            }
            else if (command == "show_context") {
                processes.at(processIndex).show_context();
            }
        }
    }
    fileStream.close();

    return 0;
}
