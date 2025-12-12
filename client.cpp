#include <iostream>
#include <cstdio>
#include <sstream>
#include <string>

using namespace std;

int main() {
    string url = "http://127.0.0.1:5000/";

    FILE *message = popen(("curl -s " + url).c_str(), "r");
    if (!message) {
        cerr << "Failed to curl!";
        return 1;
    }

    ostringstream response;
    char c;
    while (fread(&c, 1, 1, message) == 1) {
        response << c;
    }
    pclose(message);

    cout << "Server response: " << response.str() << endl;
    return 0;
}
