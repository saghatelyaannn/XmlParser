#include <iostream>
#include <vector>
#include <map>
#include <string>

using XmlMap = std::map<std::string, std::string>;
using XmlStructure = std::vector<XmlMap>;
XmlStructure structure = {
    { {"ID", "1"}, {"FirstName", "John"}, {"Surname", "Doe"}, {"Age", "21"}, {"Major", "Computer Science"} },
    { {"ID", "2"}, {"FirstName", "Jane"}, {"Surname", "Smith"}, {"Age", "22"}, {"Major", "Mathematics"} },
    { {"ID", "3"}, {"FirstName", "Michael"}, {"Surname", "Johnson"}, {"Age", "23"}, {"Major", "Physics"} },
};

void printXmlStructure(const XmlStructure& structure) {
    for (const auto& map : structure) {
        for (const auto& pair : map) {
            std::cout << pair.first << ": " << pair.second << std::endl;
        }
        std::cout << std::endl;
    }
}

int main() {
	printXmlStructure(structure);
	return 0;
}	
