#ifndef __OBJECT_SERIALIZATION_H__
#define __OBJECT_SERIALIZATION_H__

#define ARITHMETIC_TYPE typename std::enable_if<std::is_arithmetic<T>::value>::type
#define STRING_TYPE typename std::enable_if<std::is_same<T, std::string>::value>::type

#endif