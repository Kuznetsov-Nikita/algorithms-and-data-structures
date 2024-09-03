#include <fstream>
#include <string>
#include <vector>
 
int main() {
    std::ifstream f_input("number.in");
    std::ofstream f_output("number.out");
    std::vector<std::string> scraps;
 
    do {
        std::string s;
        f_input >> s;
        scraps.push_back(s);
    } while (!f_input.eof());
 
    for (int i = scraps.size() - 1; i > 0; --i) {
        for (int j = 0; j < i; ++j) {
            if (scraps[j + 1] + scraps[j] > scraps[j] + scraps[j + 1]) {
                std::swap(scraps[j], scraps[j + 1]);
            }
        }
    }
 
    for (int i = 0; i < scraps.size(); ++i) {
        f_output << scraps[i];
    }
 
    f_input.close();
    f_output.close();
 
    return 0;
}