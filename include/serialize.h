#ifndef __SERIALIZE_HEADER__
#define __SERIALIZE_HEADER__

#include "bin_Serialization.h"
#include "xml_Serialization.h"

namespace ser {
    /* binary normal type */
    template <typename T>
    void serialize(const T &obj, const string &path) {
        stringstream buf;
        binSerialization::SerializeFrom(obj, buf);
        ofstream FILE(path, ios::app | ios::binary);
        FILE << buf.str();
        FILE.close();
    }
    /* For pointers */
    template <typename T>
    void serialize(const T &obj, const string &path, size_t size) {
        stringstream buf;
        binSerialization::SerializeFrom(obj, buf, size);
        ofstream FILE(path, ios::app | ios::binary);
        FILE << buf.str();
        FILE.close();
    }
    /* binary user defined type */
    template <typename ...Args>
    void user_serialize(const string &path, const Args&...args) {
        int arr[] = {(serialize(args, path), 0)...};
        arr[0] = arr[1];
    }
    
    /* xml normal type */
    template <typename T>
    void serialize_xml(const T &obj, const string &type_name, const string &path) {
        xmlSerialization::xmlSerialization ser_xml(path.c_str());
        ser_xml.SerializeFrom(obj, type_name, ser_xml.GetXmlRoot());
    }
    /* For pointers */
    template <typename T>
    void serialize_xml(const T &obj, const string &type_name, const string &path, size_t size) {
        xmlSerialization::xmlSerialization ser_xml(path.c_str());
        ser_xml.SerializeFrom(obj, type_name, ser_xml.GetXmlRoot(), size);
    }
    /* xml user defined types */
    template <typename ...Args>
    void user_serialize_xml(const string &type_name, const string &path, const Args&... args) {
        int arr[] = {(serialize_xml(args, type_name, path), 0)...};
        arr[0] = arr[1];
    }
}  // namespace ser

namespace des {
    /* binary normal type */
    template <typename T>
    void deserialize(T &obj, const string &path) {
        stringstream buf;
        ifstream FILE(path, ios::out | ios::binary);
        buf << FILE.rdbuf();
        FILE.close();
        binDeserialization::DeserializeTo(obj, buf);
    }
    /* For pointers */
    template <typename T>
    void deserialize(T &obj, const string &path, size_t size) {
        stringstream buf;
        ifstream FILE(path, ios::out | ios::binary);
        buf << FILE.rdbuf();
        FILE.close();
        binDeserialization::DeserializeTo(obj, buf);
    }
    /* binary user defined type */
    template <typename T>
    void deserializer(T &obj, stringstream &buf) {
        binDeserialization::DeserializeTo(obj, buf);
    }
    template <typename ...Args>
    void user_deserialize(const string &path, Args&...args) {
        stringstream buf;
        ifstream FILE(path, ios::out | ios::binary);
        buf << FILE.rdbuf();
        FILE.close();
        int arr[] = {(deserializer(args, buf), 0)...};
        arr[0] = arr[1];
    }

    /* xml normal type */
    template <typename T>
    void deserialize_xml(T &obj, const string &type_name, const string &path) {
        xmlDeserialization::xmlDeserialization des_xml(path.c_str());
        des_xml.DeserializeTo(obj, des_xml.GetXmlRoot()->FirstChildElement(type_name.c_str()));
    }
    /* For pointers */
    template <typename T>
    void deserialize_xml(T &obj, const string &type_name, const string &path, size_t size) {
        xmlDeserialization::xmlDeserialization des_xml(path.c_str());
        des_xml.DeserializeTo(obj, des_xml.GetXmlRoot()->FirstChildElement(type_name.c_str()), size);
    }
    /* xml user defined type */
    template <typename ...Args>
    void user_deserialize_xml(const string &type_name, const string &path, Args &...args) {
        int arr[] = {(deserialize_xml(args, type_name, path), 0)...};
        arr[0] = arr[1];
    }
}  // namespace des

#endif
