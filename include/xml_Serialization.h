#ifndef __xml_Serialization_HEADER__
#define __xml_Serialization_HEADER__

#include "tinyxml2.h"
#include "macro.h"
#include <fstream>
#include <iostream>
#include <memory>
#include <sstream>
#include <string>
#include <type_traits>

#include <list>
#include <map>
#include <set>
#include <utility>
#include <vector>

using namespace std;
using namespace tinyxml2;

namespace xmlSerialization {
    class xmlSerialization
    {
      private:
        XMLDocument xmldoc;
        const char *path;
        XMLElement *xmlroot;
      public:
        xmlSerialization(const char *Path) : path(Path) {
            if(xmldoc.LoadFile(path)) {
                fstream FILE(path);
                FILE.close();
                xmldoc.LoadFile(path);
            }
            //xmlroot = xmldoc.RootElement();
            if(!xmldoc.FirstChildElement()) {
                xmlroot = xmldoc.NewElement("serialization");
                xmldoc.InsertFirstChild(xmlroot);
            }
            else
            {
                xmlroot = xmldoc.FirstChildElement();
            }
        }
        XMLElement* GetXmlRoot() {
            return xmlroot;
        }
        ~xmlSerialization() {
            xmldoc.SaveFile(path);
        }
        /* Arithmetic */
        template <typename T>
        ARITHMETIC_TYPE SerializeFrom(const T &obj, const string &node, XMLElement *parent) {
            XMLElement *new_node = xmldoc.NewElement(node.c_str());
            new_node->SetAttribute("val", obj);
            parent->InsertEndChild(new_node);
        }
        /* string */
        template <typename T>
        STRING_TYPE SerializeFrom(const T &obj, const string &node, XMLElement *parent) {
            XMLElement *new_node = xmldoc.NewElement(node.c_str());
            new_node->SetAttribute("val", const_cast<char*>(obj.c_str()));
            parent->InsertEndChild(new_node);
        }
        /* bool */
        template <typename T>
        void SerializeFrom(const bool &obj, const string &node, XMLElement *parent) {
            XMLElement *new_node = xmldoc.NewElement(node.c_str());
            new_node->SetAttribute("val", obj ? 1 : 0);
            parent->InsertEndChild(new_node);
        }
        /* pair */
        template <typename T1, typename T2>
        void SerializeFrom(const std::pair<T1,T2> &obj, const string &node, XMLElement *parent) {
            XMLElement *new_node = xmldoc.NewElement(node.c_str());
            parent->InsertEndChild(new_node);
            SerializeFrom(obj.first, "first", new_node);
            SerializeFrom(obj.second, "second", new_node);
        }
        /* vector */
        template <typename T>
        void SerializeFrom(const std::vector<T> &obj, const string &node, XMLElement *parent) {
            XMLElement *new_node = xmldoc.NewElement(node.c_str());
            new_node->SetAttribute("size", obj.size());
            parent->InsertEndChild(new_node);
            for (auto& item : obj)
                SerializeFrom(item, "vector_elem", new_node);
        }
        /* list */
        template <typename T>
        void SerializeFrom(const std::list<T> &obj, const string &node, XMLElement *parent) {
            XMLElement *new_node = xmldoc.NewElement(node.c_str());
            new_node->SetAttribute("size", obj.size());
            parent->InsertEndChild(new_node);
            for (auto& item : obj)
                SerializeFrom(item, "list_elem", new_node);
        }
        /* set */
        template <typename T>
        void SerializeFrom(const std::set<T> &obj, const string &node, XMLElement *parent) {
            XMLElement *new_node = xmldoc.NewElement(node.c_str());
            new_node->SetAttribute("size", obj.size());
            parent->InsertEndChild(new_node);
            for(auto& item : obj)
                SerializeFrom(item, "set_elem", new_node);
        }
        /* map */
        template <typename T1, typename T2>
        void SerializeFrom(const std::map<T1,T2> &obj, const string &node, XMLElement *parent) {
            XMLElement *new_node = xmldoc.NewElement(node.c_str());
            new_node->SetAttribute("size", obj.size());
            parent->InsertEndChild(new_node);
            for(auto& item : obj)
                SerializeFrom<T1, T2>(item, "map_elem", new_node);
        }
        /* pointers */
        template <typename T>
        void SerializeFrom(const T* obj, const string &node, XMLElement *parent, size_t size) {
            XMLElement *new_node = xmldoc.NewElement(node.c_str());
            new_node->SetAttribute("size", size);
            parent->InsertEndChild(new_node);
            for(size_t i = 0; i < size; i++)
                SerializeFrom(*(obj+i), "ptr_", new_node);
        }
        /* unique_ptr */
        template <typename T>
        void SerializeFrom(const std::unique_ptr<T> &obj, const string &node, XMLElement *parent) {
            XMLElement *new_node = xmldoc.NewElement(node.c_str());
            parent->InsertEndChild(new_node);
            SerializeFrom(*obj, "unique_ptr", new_node);
        }
        /* shared_ptr */
        template <typename T>
        void SerializeFrom(const std::shared_ptr<T> &obj, const string &node, XMLElement *parent) {
            XMLElement *new_node = xmldoc.NewElement(node.c_str());
            parent->InsertEndChild(new_node);
            SerializeFrom(*obj, "shared_ptr", new_node);
        }
    };
}  // namespace xmlSerialization

namespace xmlDeserialization {
    class xmlDeserialization {
      private:
        /* class members */
        XMLDocument xmldoc;
        XMLElement *xmlroot;
        const char *path;
        stringstream buf;
      public:
        /* class methods */
        xmlDeserialization(const char *Path) : path(Path) {
            xmldoc.LoadFile(path);
            xmlroot = xmldoc.RootElement();
        }
        XMLElement* GetXmlRoot() {
            return xmlroot;
        }
        ~xmlDeserialization() {
            xmlroot->DeleteChild(xmlroot->FirstChild());
            xmldoc.SaveFile(path);
        }

        /* Arithetic */
        template <typename T>
        ARITHMETIC_TYPE DeserializeTo(T &obj, XMLElement *first_elem) {
            buf << first_elem->Attribute("val");
            buf >> obj;
            buf.clear();
        }
        /* string */
        template <typename T>
        STRING_TYPE DeserializeTo(T &obj, XMLElement *first_elem) {
            buf << first_elem->Attribute("val");
            buf >> obj;
            buf.clear();
        }
        /* pair */
        template <typename T1, typename T2>
        void DeserializeTo(std::pair<T1, T2> &obj, XMLElement *first_elem) {
            T1 item1;
            T2 item2;
            DeserializeTo(item1, first_elem->FirstChildElement("first"));
            DeserializeTo(item2, first_elem->FirstChildElement("first")->NextSiblingElement("second"));
            obj = {item1, item2};
        }
        /* vector */
        template <typename T>
        void DeserializeTo(std::vector<T> &obj, XMLElement *first_elem) {
            size_t size;
            buf << first_elem->Attribute("size");
            buf >> size;
            buf.clear();
            obj.resize(size);

            XMLElement *next_child = first_elem->FirstChildElement("vector_elem");
            for(auto& item : obj) {
                DeserializeTo(item, next_child);
                next_child = next_child->NextSiblingElement();
            }
        }
        /* list */
        template <typename T>
        void DeserializeTo(std::list<T> &obj, XMLElement *first_elem) {
            size_t size;
            buf << first_elem->Attribute("size");
            buf >> size;
            buf.clear();
            obj.resize(size);

            XMLElement *next_child = first_elem->FirstChildElement("list_elem");
            for(auto& item : obj) {
                DeserializeTo(item, next_child);
                next_child = next_child->NextSiblingElement();
            }
        }
        /* set */
        template <typename T>
        void DeserializeTo(std::set<T> &obj, XMLElement *first_elem) {
            obj.clear();
            XMLElement *next_child = first_elem->FirstChildElement("set_elem");
            while (next_child)
            {
                T item;
                DeserializeTo(item, next_child);
                obj.insert(item);
                next_child = next_child->NextSiblingElement();
            }
        }
        /* map */
        template <typename T1, typename T2>
        void DeserializeTo(std::map<T1, T2> &obj, XMLElement *first_elem) {
            obj.clear();
            XMLElement *next_child = first_elem->FirstChildElement("map_elem");
            while(next_child)
            {
                T1 item1;
                T2 item2;
                DeserializeTo(item1, next_child->FirstChildElement("first"));
                DeserializeTo(item2, next_child->FirstChildElement("first")->NextSiblingElement("second"));
                obj.insert({item1, item2});
                next_child = next_child->NextSiblingElement();
            }
        }

        /* pointers */
        template <typename T>
        void DeserializeTo(T *obj, XMLElement *first_elem, size_t size) {
            XMLElement *next_child = first_elem->FirstChildElement("ptr_");
            for(size_t i = 0; i < size; i++) {
                DeserializeTo(obj[i], next_child);
                next_child = next_child->NextSiblingElement();
            }
        }
        /* unique_ptr */
        template <typename T>
        void DeserializeTo(std::unique_ptr<T> &obj, XMLElement *first_elem) {
            obj = std::unique_ptr<T>(new T);
            DeserializeTo(*obj, first_elem->FirstChildElement());
        }
        /* shared_ptr */
        template <typename T>
        void DeserializeTo(std::shared_ptr<T> &obj, XMLElement *first_elem) {
            obj = std::shared_ptr<T>(new T);
            DeserializeTo(*obj, first_elem);
        }
    };
}  // namespace xmlDeserialization

#endif