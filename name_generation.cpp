
#include <string>
#include <vector>



int main() {
    std::string input;
    std::string title;
    std::string author;
    std::string date;
    std::string otuTable;
    std::string otuTax;
    std::vector<std::string> sampleVec;
    std::vector<std::pair<std::string, std::string>> varVec;
    std::vector<std::pair<std::string, std::string>> contVec;
    std::vector<std::string> colVec = {"blue", "red", "black", "orange", "green", "purple", "turquoise", "gray50"};

    std::cout << "Welcome to the R Automation Program! Here we will walk through the process of creating some RMarkdown commands.\n"
        << "Do you want to generate a list of your sample names? Type in <label> if so, otherwise type anything else "
        << "(make sure you have <DONE> at the end of your shared doc): ";

    std::cin >> input;
    if (input == "label") {
        std::cin >> input;
        while (input != "DONE") {
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
}