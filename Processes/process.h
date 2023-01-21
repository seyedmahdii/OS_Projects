#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include <iomanip>
using namespace std;

#define BASE "./testcases/1/"
#define COMMANDS BASE "commands.txt"

string getNthWord (string str, int n) {
    int counter = 0;
    string word;
    stringstream iss(str);

    // Read and print each word.
    while ((iss >> word) && counter < n - 1) {
        counter++;
    }
    return word;
}

class Process {
private:
    string ID;
    string state = "ready";
    float temp;
    string IR = "";
    float ACC;
    int PC = 0;
    vector<string> INST;

public:
    Process (string ID, string file_name) {
        this->ID = ID;

        // Reading file
        string line;

        ifstream fileStream(BASE + file_name);
        while (std::getline(fileStream, line)) {
            INST.push_back(line);
        }
        fileStream.close();
    }

    string getID () {
        return ID;
    }

    void run () {
        // Process finished
        if (PC == INST.size()) {
            state = "ready";
            cout << "No more instructions to execute!" << endl;
        } else {
            IR = INST.at(PC);
            string instruction = getNthWord(IR, 1);
            float value = float(stod(getNthWord(IR, 2)));

            if (state == "block") {
                cout << "This process is blocked!" << endl;
            }
            else {
                if (instruction == "load") {
                    temp = value;
                    ACC = value;
                } else if (instruction == "sub") {
                    temp = value;
                    ACC -= temp;
                } else if (instruction == "add") {
                    temp = value;
                    ACC += temp;
                } else if (instruction == "mul") {
                    temp = value;
                    ACC *= temp;
                }

                PC++;
            }
        }
    }

    void block () {
        state = "block";
    }

    void unblock () {
        state = "ready";
    }

    void show_context () {
        cout << "Process ID : " << ID << endl;
        cout << "Instruction Register : " << IR << endl;
        cout << "Accumulator : " << fixed << setprecision(1) << ACC << "\t\tTemp : " << temp << endl;
        cout << "Program Counter : " << PC << "\t\tState : " << state << endl;
    }

    void kill (vector<Process> &processes) {
        int i = 0;
        for (auto& it : processes) {
            if (it.getID() == ID) {
                processes.erase(processes.begin() + i);
                break;
            }
            i++;
        }
    }
};

int getProcessIndex (vector<Process> processes, string ID) {
    int i = 0;
    for (auto& it : processes) {
        if (it.getID() == ID) {
            return i;
        }
        i++;
    }
    return -1;
}