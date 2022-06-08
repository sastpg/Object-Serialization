#ifndef __bin_Serialization_HEADER__
#define __bin_Serialization_HEADER__

#include "macro.h"
#include <iostream>
#include <sstream>
#include <fstream>
#include <memory>
#include <type_traits>
#include <string>
#include <vector>
#include <list>
#include <set>
#include <map>
#include <utility>

using namespace std;

namespace binSerialization {
    /* Arithmetic */
    template <typename T>
    ARITHMETIC_TYPE SerializeFrom(const T &obj, stringstream &buf) {
        buf.write((char*) &obj, sizeof(T));
    }
    /* string */
    template<typename T>
    STRING_TYPE SerializeFrom(const T &obj, stringstream &buf) {
        unsigned int size = obj.size();
        buf.write((char*) &size, sizeof(size));
        buf.write(obj.c_str(), sizeof(char)*size);
    }
    /* pair */
    template<typename T1, typename T2>
    void SerializeFrom(const std::pair<T1, T2> &obj, stringstream &buf) {
        SerializeFrom(obj.first, buf);
        SerializeFrom(obj.second, buf);
    }
    /* vector */
    template <typename T>
    void SerializeFrom(const std::vector<T> &obj, stringstream &buf) {
        unsigned int size = obj.size();
        buf.write((char*) &size, sizeof(size));
        for(auto& item : obj)
            SerializeFrom(item, buf);
    }
    /* list */
    template <typename T>
    void SerializeFrom(const std::list<T> &obj, stringstream &buf) {
        unsigned int size = obj.size();
        buf.write((char*) &size, sizeof(size));
        for(auto& item : obj)
            SerializeFrom(item, buf);
    }
    /* set */
    template <typename T>
    void SerializeFrom(const std::set<T> &obj, stringstream &buf) {
        unsigned int size = obj.size();
        buf.write((char*) &size, sizeof(size));
        for(auto& item : obj)
            SerializeFrom(item, buf);
    }
    /* map */
    template <typename T1, typename T2>
    void SerializeFrom(const std::map<T1, T2> &obj, stringstream &buf) {
        unsigned int size = obj.size();
        buf.write((char*) &size, sizeof(size));
        for(auto& item : obj)
            SerializeFrom<T1, T2>(item, buf);
    }
    /* bonus: unique_ptr */
    template <typename T>
    void SerializeFrom(const std::unique_ptr<T> &obj, stringstream &buf) {
        SerializeFrom(*obj, buf);
    }
    /* bonus: shared_ptr */
    template <typename T>
    void SerializeFrom(const std::shared_ptr<T> &obj, stringstream &buf) {
        SerializeFrom(*obj, buf);
    }
    /* basic_ptr */
    template <typename T>
    void SerializeFrom(T *const &obj, stringstream &buf, size_t size) {
        buf.write((char*) &size, sizeof(size));
        for(size_t i = 0; i < size; i++)
            SerializeFrom(*(obj+i), buf);
    }
    /* unique_ptr overload */
    template <typename T>
    void SerializeFrom(const std::unique_ptr<T[]> &obj, stringstream &buf, size_t size) {
        buf.write((char*) &size, sizeof(size));
        for(size_t i = 0; i < size;i ++)
            SerializeFrom(obj[i], buf);
    }
    /* shared_ptr overload */
    template <typename T>
    void SerializeFrom(const std::shared_ptr<T[]> &obj, stringstream &buf, size_t size) {
        buf.write((char*)&size, sizeof(size));
        for(size_t i = 0; i < size;i ++)
            SerializeFrom(obj[i], buf);
    }
}  // namespace binSerialization

namespace binDeserialization {
    /* Arithmetic */
    template <typename T>
    ARITHMETIC_TYPE DeserializeTo(T &obj, stringstream &buf) {
        buf.read((char*)&obj, sizeof(T));
    }
    /* string */
    template<typename T>
    STRING_TYPE DeserializeTo(T &obj, stringstream &buf) {
        unsigned int size;
        buf.read((char*) &size, sizeof(size));
        obj.resize(size);
        buf.read(const_cast<char*>(obj.c_str()), sizeof(char)*size);
    }    
    /* pair */
    template<typename T1, typename T2>
    void DeserializeTo(std::pair<T1, T2> &obj, stringstream &buf) {
        DeserializeTo(obj.first, buf);
        DeserializeTo(obj.second, buf);
    }
    /* vector */
    template <typename T>
    void DeserializeTo(std::vector<T> &obj, stringstream &buf) {
        unsigned int size;
        obj.clear();
        buf.read((char*) &size, sizeof(size));
        for(unsigned int i = 0; i < size; i++) {
            T item;
            DeserializeTo(item, buf);
            obj.push_back(item);
        }
    }
    /* list */
    template <typename T>
    void DeserializeTo(std::list<T> &obj, stringstream &buf) {
        unsigned int size = 0; 
        buf.read((char*) &size, sizeof(size));
        obj.resize(size);
        
        for(auto& item : obj)
            DeserializeTo(item, buf);
    }
    /* set */
    template <typename T>
    void DeserializeTo(std::set<T> &obj, stringstream &buf) {
        unsigned int size;
        obj.clear();
        buf.read((char*) &size, sizeof(size));
        for(unsigned int i = 0; i < size; i++) {
            T item;
            DeserializeTo(item, buf);
            obj.insert(item);
        }
    }
    /* map */
    template <typename T1, typename T2>
    void DeserializeTo(std::map<T1, T2> &obj, stringstream &buf) {
        unsigned int size;
        buf.read((char*)&size, sizeof(unsigned int));
        for(unsigned int i=0; i < size; i++) {
            T1 item1;
            T2 item2;
            DeserializeTo(item1, buf);
            DeserializeTo(item2, buf);
            obj.insert({item1, item2});
        }
    }
    /* bonus: unique_ptr */
    template <typename T>
    void DeserializeTo(std::unique_ptr<T> &obj, stringstream &buf) {
        obj = std::unique_ptr<T>(new T);
        DeserializeTo(*obj, buf);
    }
    /* bonus: shared_ptr */
    template <typename T>
    void DeserializeTo(std::shared_ptr<T> &obj, stringstream &buf) {
        obj = std::shared_ptr<T>(new T);
        DeserializeTo(*obj, buf);
    }
    /* basic_ptr */
    template <typename T>
    void DeserializeTo(T *&obj, stringstream &buf) {
        size_t size;
        buf.read((char*) &size, sizeof(size));
        obj = new T[size];
        for(size_t i = 0 ;i < size; i++)
            DeserializeTo(*(obj+i), buf);
    }
    /* unique_ptr overload */

}  // namespace binDeserialization

#endif