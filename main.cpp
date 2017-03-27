#include <iostream>
#include <fstream>
#include <vector>
#include <deque>

using namespace std;

void findLongestPath_Recursive(std::vector<string> &lab, int r, int c, int deep, std::vector<int> &path);

const int directions[4][2] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};
const char dirsign[4] = {'^', '>', 'v', '<'};

bool maxPathIsChanged;
int maxLenOfPath = 0;
std::vector<int> maxPath;

int main(int argc, char *argv[]) {

    // Check if a file is given and load labyrinth
    if (argc < 2) {
        std::cerr << "Usage: " << "CplusplusChallenge" << " inputfile" << std::endl;
        return 1;
    }

    std::ifstream infile(argv[1]);
    std::string line;
    std::vector<std::string> lab;
    while (std::getline(infile, line)) {
        lab.push_back(line);
    }

    // Find the longest path
    int max = 0, maxStartFromR  = -1, maxStartFromC = -1;
    std::vector<int> path;
    for (int i = 0; i < lab.size(); i++) {
        for (int j = 0; j < lab[i].size(); j++) {
            if (lab[i][j] == '.') {
                maxPathIsChanged = false;
                findLongestPath_Recursive(lab, i, j, 0, path);
                if (maxPathIsChanged) {
                    maxStartFromR = i;
                    maxStartFromC = j;
                }
            }
        }
    }

    // Write the length of the longest path and the schema

    // I use arrows to show the path, because it hard to show the path
    // properly if the length is greater than 10
    int n = 0;
    if (maxStartFromR != -1) {
        int r = maxStartFromR;
        int c = maxStartFromC;
        lab[r][c] = '*';
        n++;
        for (auto& d : maxPath) {
            r += directions[d][0];
            c += directions[d][1];
            lab[r][c] = dirsign[d];
            n++;
        }
    }
    std::cout << n << std::endl;
    for (const auto& row : lab) {
        std::cout << row << std::endl;
    }

    return 0;
}


void findLongestPath_Recursive(std::vector<string> &lab, int r, int c, int deep, std::vector<int> &path) {

    // Go through four directions
    lab[r][c] = '#';
    for (int i = 0; i < 4; i++) {
        int nr = r + directions[i][0];
        int nc = c + directions[i][1];

        if (nr < 0 || nr >= lab.size()) {
            continue;
        }
        const auto& line = lab[nr];
        if (nc < 0 || nc >= line.size()) {
            continue;
        }
        if (line[nc] != '.') {
            continue;
        }
        path.push_back(i);
        findLongestPath_Recursive(lab, nr, nc, deep+1, path);
        path.pop_back();
    }
    lab[r][c] = '.';
    if (deep > maxLenOfPath) {
        maxPathIsChanged = true;
        maxLenOfPath = deep;
        maxPath = path;
    }
}

