#ifndef __TEST_HEADER__
#define __TEST_HEADER__
#include <iostream>
#include <vector>

struct UserDefinedType {
    int idx;
    std::string name;
    std::vector<double> data;
    void Print() {
        std::cout << "idx = " << idx << ", name = " << name << std::endl;
        for(auto& item : data)
            std::cout << item << " ";
        std::cout << std::endl;
    }
};

std::int32_t ERROR = 0;
std::int32_t error = 0;

void bin_arithmetic_test();
void bin_string_test();
void bin_vector_test();
void bin_set_test();
void bin_map_test();
void bin_ptr_test();
void bin_nested_test();
void bin_user_test();
void xml_arithmetic_test();
void xml_string_test();
void xml_vector_test();
void xml_list_test();
void xml_set_test();
void xml_map_test();
void xml_ptr_test();
void xml_nested_test();
void xml_user_test();
void bin_serialization_test();
void xml_serialization_test();

template <typename T1, typename T2>
bool IsEquel(T1 &obj1,T2 &obj2);
bool IsEquel(UserDefinedType &obj1, UserDefinedType &obj2);

#endif