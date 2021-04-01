//
// Created by gianni on 16/02/2021.
//

#include                            <iostream>
#include                            <list>
#include                            <string>
#include                            <tuple>
#include                            <set>
#include                            <fstream>
#include                            <algorithm>

using namespace                     std;

tuple<list<string>, int>            solver(const string *path, string param)
{
    list<string> anagrams;
    ifstream file(*path, ios::in);
    if (file) {
        string line;
        while (getline(file,line)) {
            if (line.size() <= 11) {
                string rawLine = line;
                transform(rawLine.begin(), rawLine.end(), rawLine.begin(), ::tolower);
                sort(rawLine.begin(), rawLine.end());
                if (rawLine == param) {
                    anagrams.push_back(line);
                    cout << line << endl;
                }
            }
        }
    }
    else {
        return make_tuple(anagrams, 3);
    }
    file.close();
    return make_tuple(anagrams, 0);
}

int                                 main(int argc, char* argv[])
{
    list<string> result;
    string dict;

    if (argc == 3 && argv[1] && (string)argv[1] == "-d") {
        dict = argv[2];
    }
    else {
        // Arguments invalides, on retourne 2
        return 2;
    }
    string currentParam;

    // On boucle jusqu'à un EOF / Ctrl +D
    while (cin >> currentParam) {
        transform(currentParam.begin(), currentParam.end(), currentParam.begin(), ::tolower);
        sort(currentParam.begin(), currentParam.end());
        currentParam.erase(remove(currentParam.begin(), currentParam.end(), '"'), currentParam.end());
        result.push_back(currentParam);

        tuple<list<string>, int> solverData = solver(&dict, currentParam);
        list <string> anagrams = get<0>(solverData);
        int solverStatus = get<1>(solverData);
        if (solverStatus == 3) {
            return 3;
        }
        if (anagrams.empty()) {
            return 1;
        }
    }

    return 0;
}