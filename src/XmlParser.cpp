#include "../lib/XmlParser.hpp"
#include <fstream>
#include <iostream>
#include <stdexcept>


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
    try {
        tinyxml2::XMLDocument doc;

        if (doc.LoadFile(filename.c_str()) != tinyxml2::XML_SUCCESS) {
            throw std::runtime_error("File can't be opened: " + filename);
        }

        XmlStructure structure;
        tinyxml2::XMLElement* root = doc.RootElement();
        if (!root) {
            throw std::runtime_error("No root element in XML: " + filename);
        }

        tinyxml2::XMLElement* element = root->FirstChildElement();
        while (element) {
            parseElement(element, structure);
            element = element->NextSiblingElement();
        }

        return structure;

    } catch (const std::runtime_error& e) {
        std::cerr << "Ошибка: " << e.what() << std::endl;
        return {};
    }
}

