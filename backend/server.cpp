#include <cstdlib>
#include <fstream>
#include <iostream>
#include <random>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>
#include <httplib.h>

#define PATH_TO_DATA "data/data.dat"

using namespace std;
using namespace httplib;

vector<string> read_all_lines(const string& data_name) {
    ifstream file(data_name);

    if (!file.is_open()) {
        throw runtime_error("Error to open file: " + data_name);
    }

    vector<string> lines;
    string line;

    while (getline(file, line)) {
        if (!line.empty()) lines.push_back(line);
    }

    return lines;
}

string get_random_line(const vector<string>& lines) {
    if (lines.empty()) throw runtime_error("Data file is empty!");

    static random_device rd;
    static mt19937 gen(rd());
    uniform_int_distribution<> dis(0, lines.size() - 1);

    return lines[dis(gen)];
}

string lines_parser() {
    string path = PATH_TO_DATA;
    vector<string> lines = read_all_lines(path);
    return get_random_line(lines);
}

string jsonify(string text) {
    stringstream ss;
    for (char c : text) {
        switch (c) {
            case '"': ss << "\\\""; break;
            case '\\': ss << "\\\\"; break;
            case '\n': ss << "\\n"; break;
            case '\r': ss << "\\r"; break;
            case '\t': ss << "\\t"; break;
            default: ss << c; break;
        }
    }
    return "{\"text\":\"" + ss.str() + "\"}";
}

int main() {
    Server srv;

    srv.Get("/typing", [](const Request&, Response& res) {
        try {
            string text = lines_parser();
            string json_response = jsonify(text); // Формируем JSON
            res.set_content(json_response, "application/json"); // Отправляем
        } catch (const exception& e) {
            res.set_content("{\"error\":\"" + string(e.what()) + "\"}", "application/json");
        }
    });

    cout << "C++ Server is running on http://localhost:8081/typing" << endl;
    srv.listen("localhost", 8081);

    return 0;
}
