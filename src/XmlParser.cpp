#include "../lib/XmlParser.hpp"
#include <iostream>

void parseElement(tinyxml2::XMLElement* element, XmlStructure& structure, XmlMap& combinedData) {
    if (!element) {
        return;
    }

    const char* elementName = element->Name();
    const tinyxml2::XMLAttribute* attribute = element->FirstAttribute();
    while (attribute) {
        combinedData[attribute->Name()] = attribute->Value();
        attribute = attribute->Next();
    }

    if (element->GetText() && element->GetText()[0] != '\0') {
        combinedData[elementName] = element->GetText();
    }

    tinyxml2::XMLElement* child = element->FirstChildElement();
    bool hasChild = false;
    while (child) {
        hasChild = true;
        parseElement(child, structure, combinedData);
        child = child->NextSiblingElement();
    }

    if (!hasChild && !combinedData.empty()) {
        structure.push_back(combinedData);
        combinedData.clear(); 
    }
}

XmlStructure parseXML(const std::string& filename) {
    tinyxml2::XMLDocument doc;
    if (doc.LoadFile(filename.c_str()) != tinyxml2::XML_SUCCESS) {
        std::cerr << "File can't be opened: " << filename << std::endl;
        return {};
    }

    XmlStructure structure;
    tinyxml2::XMLElement* root = doc.RootElement();
    if (root) {
        XmlMap combinedData;
        parseElement(root, structure, combinedData);
    }

    return structure;
}

