#include "../lib/XmlParser.hpp"
#include <iostream>

void parseElement(tinyxml2::XMLElement* element, XmlStructure& structure) {
    if (!element) {
        return;
    }

    XmlMap combinedData;

    const tinyxml2::XMLAttribute* attribute = element->FirstAttribute();
    while (attribute) {
        combinedData[attribute->Name()] = attribute->Value();
        attribute = attribute->Next();
    }

    tinyxml2::XMLElement* child = element->FirstChildElement();
    while (child) {
        if (child->GetText() && child->GetText()[0] != '\0') {
            combinedData[child->Name()] = child->GetText();
        }
        child = child->NextSiblingElement();
    }

    structure.push_back(combinedData);
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
        tinyxml2::XMLElement* element = root->FirstChildElement();
        while (element) {
            parseElement(element, structure);
            element = element->NextSiblingElement();
        }
    }

    return structure;
}

