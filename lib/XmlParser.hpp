#ifndef XMLPARSER_H
#define XMLPARSER_H

#include <string>
#include <map>
#include <vector>
#include <tinyxml2.h>

using XmlMap = std::map<std::string, std::string>;
using XmlStructure = std::vector<XmlMap>;

void parseElement(tinyxml2::XMLElement* element, XmlStructure& structure,XmlMap& combinedData);// const std::string& parent = "");

XmlStructure parseXML(const std::string& filename);

#endif

