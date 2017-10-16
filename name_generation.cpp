// Program that takes in .shared file generated from mothur SOP and generates names of all the samples

#include <string>
#include <vector>

int main() {
    std::string input;
    std::string otuTable;
    std::string otuTax;
    std::vector<std::string> sampleVec;
    std::vector<std::pair<std::string, std::string>> varVec;
    std::vector<std::pair<std::string, std::string>> contVec;
    std::vector<std::string> colVec = {"blue", "red", "black", "orange", "green", "purple", "turquoise", "gray50"};

    // Read in everything and parse out the sample names
    while (std::cin >> input) {
        if (input == "0.03") {
            std::cin >> input;
            sampleVec.push_back(input);
        }
        std::cin >> input;
    }
    
    for (auto x : sampleVec) {
        std::cout << x << "\n";
    }
}