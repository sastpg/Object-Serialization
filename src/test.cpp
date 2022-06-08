/**
 * @file test.cpp
 * @author kc.zhang, Zhejiang University
 * @brief a tool for serialization/deserialization
 * @version 0.1.0
 * @date 2022-06-08
 * NOTE: bonus smart pointers are supported
 * @copyright Copyright (c) 2022
 * 
 * binary serialization interface:
 *     types in std: template <typename T>
 *                   void serialize(const T &obj, const string &path);
 *     user defined: template <typename ...Args>
 *                   void user_serialize(const string &path, const Args&...args);
 * binary deserialization interface:
 *     types in std: template <typename T>
 *                   void deserialize(T &obj, const string &path);
 *     user defined: template <typename ...Args>
 *                   void user_deserialize(const string &path, Args&...args);
 *                   
 * XML serialization interface:
 *     types in std: template <typename T>
 *                   void serialize_xml(const T &obj, const string &type_name, const string &path)
 *     user defined: template <typename ...Args>
 *                   void u_serialize_xml(const string &type_name, const string &path, const Args&... args)
 * XML deserialization interface:
 *     types in std: template <typename T>
 *                   void deserialize_xml(T &obj, const string &type_name, const string &path)
 *     user defined: template <typename ...Args>
 *                   void user_deserialize_xml(const string &type_name, const string &path, Args &...args)
 */

#include "../include/serialize.h"
#include "../include/test.h"

using namespace ser;
using namespace des;

int main()
{
    std::cout<<"\033[32m[==========] \033[0mRunning 2 tests from 1 test suite\033[0m"<<std::endl;
    std::cout<<"\033[32m[----------] \033[0mGlobal test environment set-up\033[0m"<<std::endl;
    std::cout<<"\033[32m[ RUN      ] \033[0mtest.BinarySerializationTest\033[0m"<<std::endl;
    ofstream fout("test_all.txt"); // file stream object
	streambuf* pOld =cout.rdbuf(fout.rdbuf());
    cout << "/************   Binary Serialization Test   ************/" << endl;
    bin_serialization_test();
    cout.rdbuf(pOld);
    if(ERROR)
        std::cout<<"\033[31m[  FAILED  ] \033[0mERROE!\033[0m"<<std::endl;
    else
        std::cout<<"\033[32m[       OK ] \033[0mBinarySerializationTest\033[0m"<<std::endl;
    error += ERROR;
    ERROR = 0;
    std::cout<<"\033[32m[ RUN      ] \033[0mtest.XMLSerializationTest\033[0m"<<std::endl;
	pOld =cout.rdbuf(fout.rdbuf());
    cout << "/************    XML Serialization Test    ************/" << endl;
    xml_serialization_test();
    cout.rdbuf(pOld);
    if(ERROR)
        std::cout<<"\033[31m[  FAILED  ] \033[0mXMLSerializationTest\033[0m"<<std::endl;
    else
        std::cout<<"\033[32m[       OK ] \033[0mBinarySerializationTest\033[0m"<<std::endl;
    error += ERROR;
    std::cout<<"\033[32m[----------] \033[0mGlobal test environment tear-down\033[0m"<<std::endl;
    if(error)
        std::cout<<"\033[31m[  FAILED  ]\033[0m "  << error << " errors." << std::endl;
    else
        std::cout<<"\033[32m[  PASSED  ] \033[0m2 tests.\033[0m"<<std::endl;
}

void bin_serialization_test() {
    bin_arithmetic_test();
    bin_string_test();
    bin_vector_test();
    bin_set_test();
    bin_map_test();
    bin_ptr_test();
    bin_nested_test();
    bin_user_test();
}

void xml_serialization_test() {
    xml_arithmetic_test();
    xml_string_test();
    xml_vector_test();
    // xml_list_test();
    xml_set_test();
    xml_map_test();
    xml_ptr_test();
    xml_nested_test();
    xml_user_test();
}

void bin_arithmetic_test() {
    int i1 = 2, i2 = 0;
    double d1 = 6.666, d2 = 0;

    serialize(i1, "../test/bin_int.data");
    serialize(d1, "../test/bin_double.data");
    deserialize(i2, "../test/bin_int.data");
    deserialize(d2, "../test/bin_double.data");

    cout << "---------- Arithmetic Bianry test ----------" << endl;
    cout << "(1) int" << endl;
    cout << "Before serialization: " << endl << "i1 = " << i1 << endl;
    cout << "After serialization: " << endl << "i2 = " << i2 << endl;
    cout << "is_equal: " << (IsEquel(i1, i2) ? "True" : "False") << endl;
    cout << "(2) double" << endl;
    cout << "Before serialization: " << endl << "d1 = " << d1 << endl;
    cout << "After serialization: " << endl << "d2 = " << d2 << endl;
    cout << "is_equal: " << (IsEquel(d1, d2) ? "True" : "False") << endl;
}

void bin_string_test() {
    string str1 = "Hello, world! It's night now!", str2 = "";
    serialize(str1, "../test/bin_string.data");
    deserialize(str2, "../test/bin_string.data");

    cout << "----------- string Bianry test -----------" << endl;
    cout << "Before serialization: " << endl << "str1 = " << str1 << endl;
    cout << "After serialization: " << endl << "str2 = " << str2 << endl;
    cout << "is_equal: " << (IsEquel(str1, str2) ? "True" : "False") << endl;
}

void bin_vector_test() {
    vector<string> v1 = {"Hello", "World", "Hi", "C++"}, v2 = {};
    serialize(v1, "../test/bin_vector.data");
    deserialize(v2, "../test/bin_vector.data");

    cout << "--------- std::vector Bianry test ---------" << endl;
    cout << "Before serialization: " << endl;
    for(auto& item : v1)
        cout << item << " ";
    cout << endl;
    cout << "After serialization: " << endl;
    for(auto& item : v2)
        cout << item << " ";
    cout << endl;
    cout << "is_equal: " << (IsEquel(v1, v2) ? "True" : "False") << endl;
}

void bin_set_test() {
    set<double> s1 = {0.22, 6.666, 8.888888, 9.9999999}, s2 = {};
    serialize(s1, "../test/bin_set.data");
    deserialize(s2, "../test/bin_set.data");

    cout << "---------- std::set Bianry test ----------" << endl;
    cout << "Before serialization: " << endl;
    for(auto& item : s1)
        cout << item << " ";
    cout << endl;
    cout << "After serialization: " << endl;
    for(auto& item : s2)
        cout << item << " ";
    cout << endl;
    cout << "is_equal: " << (IsEquel(s1, s2) ? "True" : "False") << endl;
}

void bin_map_test() {
    map<string, float> m1 = {{"apple", 1.5}, {"banana", 2.1}, {"peach", 3.6}}, m2 = {};
    serialize(m1, "../test/bin_map.data");
    deserialize(m2, "../test/bin_map.data");

    cout << "---------- std::map Bianry test ----------" << endl;
    cout << "Before serialization: " << endl;
    for(auto& item : m1)
        cout << "{" << item.first << ", " << item.second << "} ";
    cout << endl;
    cout << "After serialization: " << endl;
    for(auto& item : m2)
        cout << "{" << item.first << ", " << item.second << "} ";
    cout << endl;
    cout << "is_equal: " << (IsEquel(m1, m2) ? "True" : "False") << endl;
}

void bin_ptr_test() {
    int *p1 = new int[5], *p2 = new int[5];
    unique_ptr<double> up1 = unique_ptr<double>(new double(6.66)), up2;
    for(int i = 0; i < 5; i++)
        p1[i] = i * i;
    
    serialize(p1, "../test/bin_ptr.data", 5);
    deserialize(p2, "../test/bin_ptr.data", 5);
    serialize(up1, "../test/bin_uptr.data");
    deserialize(up2, "../test/bin_uptr.data");
    cout << "-------- unique_ptr Bianry test ----------" << endl;
    cout << "(1)int *" << endl << "Before serialization: " << endl << "p1: ";
    for(int i = 0; i < 5; i++)
        cout << p1[i] << " ";
    cout << endl;
    cout << "After serialization: " << endl << "p2: ";
    for(int i = 0; i < 5; i++)
        cout << p2[i] << " ";
    cout << endl;
    int flag = 1;
    for(int i = 0; i < 5; i++) {
        if(*(p1+i) != *(p2+i)) {
            flag = 0;
            ERROR++;
            break;
        }
    }
    cout << "is_equal: " << (flag ? "True" : "False") << endl;
    cout << "(2)unique_ptr<double>" << endl << "Before serialization: " << endl << "up1: " << *up1 << endl;
    cout << "After serialization: " << endl << "up2: " << *up2 << endl;
    if(*up1 != *up2) {
        flag = 0;
        ERROR++;
    }
    cout << "is_equal: " << (flag ? "True" : "False") << endl;
}

void bin_nested_test() {
    list<pair<string, float>> l1 = {{"potato", 4.0}, {"tomato", 3.2}, {"cloth", 108.98}}, l2 = {};
    serialize(l1, "../test/bin_nested.data");
    deserialize(l2, "../test/bin_nested.data");

    cout << "----------- Nested Bianry test -----------" << endl;
    cout << "list<pair<string, float>>" << endl << "Before serialization: " << endl;
    for(auto& item : l1)
        cout << "{" << item.first << ", " << item.second << "} ";
    cout << endl;
    cout << "After serialization: " << endl;
    for(auto& item : l2)
        cout << "{" << item.first << ", " << item.second << "} ";
    cout << endl;
    cout << "is_equal: " << (IsEquel(l1, l2) ? "True" : "False") << endl;
}

void bin_user_test() {
    UserDefinedType president1 = { 72, "Trump", {1.2, 3.4, 6, 8} }, president2;
    user_serialize("../test/bin_user.data", president1.idx, president1.name, president1.data);
    user_deserialize("../test/bin_user.data", president2.idx, president2.name, president2.data);
    
    cout << "-----------  User Bianry test  -----------" << endl;
    cout << "Before serialization: " << endl;
    president1.Print();
    cout << "After serialization: " << endl;
    president2.Print();
    cout << "is_equal: " << (IsEquel(president1, president2) ? "True" : "False") << endl;
}

void xml_arithmetic_test() {
    int i1 = 2, i2 = 0;
    double d1 = 6.666, d2 = 0;

    serialize_xml(i1, "int" , "../test/xml_int.xml");
    serialize_xml(d1, "double" ,"../test/xml_double.xml");
    deserialize_xml(i2, "int" , "../test/xml_int.xml");
    deserialize_xml(d2, "double" ,"../test/xml_double.xml");

    cout << "---------- Arithmetic XML test ----------" << endl;
    cout << "(1) int" << endl;
    cout << "Before serialization: " << endl << "i1 = " << i1 << endl;
    cout << "After serialization: " << endl << "i2 = " << i2 << endl;
    cout << "is_equal: " << (IsEquel(i1, i2) ? "True" : "False") << endl;
    cout << "(2) double" << endl;
    cout << "Before serialization: " << endl << "d1 = " << d1 << endl;
    cout << "After serialization: " << endl << "d2 = " << d2 << endl;
    cout << "is_equal: " << (IsEquel(d1, d2) ? "True" : "False") << endl;
}

void xml_string_test() {
    string str1 = "Hello,world!", str2 = "";
    serialize_xml(str1, "string", "../test/xml_string.xml");
    deserialize_xml(str2, "string", "../test/xml_string.xml");

    cout << "------------ string XML test ------------" << endl;
    cout << "Before serialization: " << endl << "str1 = " << str1 << endl;
    cout << "After serialization: " << endl << "str2 = " << str2 << endl;
    cout << "is_equal: " << (IsEquel(str1, str2) ? "True" : "False") << endl;
}

void xml_vector_test() {
    vector<string> v1 = {"Hello", "World", "Hi", "C++"}, v2 = {};
    serialize_xml(v1, "vector", "../test/xml_vector.xml");
    deserialize_xml(v2, "vector", "../test/xml_vector.xml");

    cout << "--------- std::vector XML test ----------" << endl;
    cout << "Before serialization: " << endl;
    for(auto& item : v1)
        cout << item << " ";
    cout << endl;
    cout << "After serialization: " << endl;
    for(auto& item : v2)
        cout << item << " ";
    cout << endl;
    cout << "is_equal: " << (IsEquel(v1, v2) ? "True" : "False") << endl;
}

void xml_list_test() {
    list<char> l1 = {'A', 'E', 'I', 'O', 'U'}, l2;
    serialize_xml(l1, "list", "../test/xml_list.xml");
    deserialize_xml(l2, "list", "../test/xml_list.xml");

    cout << "---------- std::list XML test -----------" << endl;
    cout << "Before serialization: " << endl;
    for(auto& item : l1)
        cout << item << " ";
    cout << endl;
    cout << "After serialization: " << endl;
    for(auto& item : l2)
        cout << item << " ";
    cout << endl;
    cout << "is_equal: " << (IsEquel(l1, l2) ? "True" : "False") << endl;
}

void xml_set_test() {
    set<double> s1 = {0.22, 6.666, 8.888888, 9.9999999}, s2 = {};
    serialize_xml(s1, "set", "../test/xml_set.xml");
    deserialize_xml(s2, "set", "../test/xml_set.xml");

    cout << "----------- std::set XML test -----------" << endl;
    cout << "Before serialization: " << endl;
    for(auto& item : s1)
        cout << item << " ";
    cout << endl;
    cout << "After serialization: " << endl;
    for(auto& item : s2)
        cout << item << " ";
    cout << endl;
    cout << "is_equal: " << (IsEquel(s1, s2) ? "True" : "False") << endl;
}

void xml_map_test() {
    map<string, float> m1 = {{"apple", 1.5}, {"banana", 2.1}, {"peach", 3.6}}, m2 = {};
    serialize_xml(m1, "map", "../test/xml_map.xml");
    deserialize_xml(m2, "map", "../test/xml_map.xml");

    cout << "----------- std::map XML test -----------" << endl;
    cout << "Before serialization: " << endl;
    for(auto& item : m1)
        cout << "{" << item.first << ", " << item.second << "} ";
    cout << endl;
    cout << "After serialization: " << endl;
    for(auto& item : m2)
        cout << "{" << item.first << ", " << item.second << "} ";
    cout << endl;
    cout << "is_equal: " << (IsEquel(m1, m2) ? "True" : "False") << endl;
}

void xml_ptr_test() {
    int *p1 = new int[5], *p2 = new int[5];
    unique_ptr<double> up1 = unique_ptr<double>(new double(6.66)), up2;
    for(int i = 0; i < 5; i++)
        p1[i] = i * i;
    
    serialize_xml(p1, "int_ptr", "../test/xml_ptr.xml", 5);
    deserialize_xml(p2, "int_ptr", "../test/xml_ptr.xml", 5);
    serialize_xml(up1, "unique_ptr", "../test/xml_uptr.xml");
    deserialize_xml(up2, "unique_ptr", "../test/xml_uptr.xml");
    cout << "---------- pointers XML test -----------" << endl;
    cout << "(1)int *" << endl << "Before serialization: " << endl << "p1: ";
    for(int i = 0; i < 5; i++)
        cout << p1[i] << " ";
    cout << endl;
    cout << "After serialization: " << endl << "p2: ";
    for(int i = 0; i < 5; i++)
        cout << p2[i] << " ";
    cout << endl;
    int flag = 1;
    for(int i = 0; i < 5; i++) {
        if(*(p1+i) != *(p2+i)) {
            flag = 0;
            ERROR++;
            break;
        }
    }
    cout << "is_equal: " << (flag ? "True" : "False") << endl;
    cout << "(2)unique_ptr<double>" << endl << "Before serialization: " << endl << "up1: " << *up1 << endl;
    cout << "After serialization: " << endl << "up2: " << *up2 << endl;
    if(*up1 != *up2) {
        flag = 0;
        ERROR++;
    }
    cout << "is_equal: " << (flag ? "True" : "False") << endl;
}

void xml_nested_test() {
    map<string, vector<int>> m1 = {{"Red", {255, 0, 0}}, {"Blue", {0 ,125, 255}}, {"Green", {0, 255, 0}}}, m2 = {};
    serialize_xml(m1, "map_nested", "../test/xml_nested.xml");
    deserialize_xml(m2, "map_nested", "../test/xml_nested.xml");

    cout << "-----------  Nested XML test  -----------" << endl;
    cout << "map<string, vector<float>>" << endl << "Before serialization: " << endl;
    for(auto& i : m1) {
        cout << "{" << i.first << ", {";
        for(auto& j : i.second)
            cout << j << " ";
        cout << "} }" << endl;
    }
    cout << "After serialization: " << endl;
    for(auto& i : m2) {
        cout << "{" << i.first << ", {";
        for(auto& j : i.second)
            cout << j << " ";
        cout << "} }" << endl;
    }
    cout << "is_equal: " << (IsEquel(m1, m2) ? "True" : "False") << endl;
}

void xml_user_test() {
    UserDefinedType president1 = { 56, "Obama", {12.6, 2008, 6.2, 8} }, president2;
    user_serialize_xml("user", "../test/xml_user.xml", president1.idx, president1.name, president1.data);
    user_deserialize_xml("user", "../test/xml_user.xml", president2.idx, president2.name, president2.data);

    cout << "------------  User XML test  ------------" << endl;
    cout << "Before serialization: " << endl;
    president1.Print();
    cout << "After serialization: " << endl;
    president2.Print();
    cout << "is_equal: " << (IsEquel(president1, president2) ? "True" : "False") << endl;
}

/* judge whether two objects are equal */
template <typename T1, typename T2>
bool IsEquel(T1 &obj1,T2 &obj2) {
    if(obj1 == obj2)
        return true;
    ERROR++;
    return false;
}
bool IsEquel(UserDefinedType &obj1, UserDefinedType &obj2) {
    if(obj1.idx == obj2.idx && obj1.name == obj2.name && obj1.data == obj2.data)
        return true;
    ERROR++;
    return false;
}
