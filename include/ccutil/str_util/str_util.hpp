#pragma once

#include <vector>
#include <string>

namespace cc {

/**
 * @brief Splits string into a list of string by a delimiter delim
 * 
 * @param str String to split
 * @param delim Character that splits the string
 * @param depth How many splits to do. 0 = all splits possible
 * @return std::vector<std::string> List of section after splitting.
 */
std::vector<std::string> split(std::string str, char delim, std::size_t depth = 0);
/**
 * @brief Trim leading whitespaces from string. Resturn result.
 * 
 * @param s String to trim, will not be changed.
 * @return std::string Copy of s with whitespaces trimmed.
 */
std::string ltrim_cpy(const std::string &s);
/**
 * @brief Trim trailing whitespaces from string. Resturn result.
 * 
 * @param s String to trim, will not be changed.
 * @return std::string Copy of s with whitespaces trimmed.
 */
std::string rtrim_cpy(const std::string &s);
/**
 * @brief Trim both traling and leading whitespaces. Returns result
 * 
 * @param s String to trim, will not be changed.
 * @return std::string Copy of s with whitespaces trimmed.
 */
std::string trim_cpy(const std::string &s);
/**
 * @brief Trim leading whitespaces from string. 
 * 
 * @param s String to trim, will be changed.
 * @return std::string Reference to s
 */
std::string &ltrim(std::string &s);
/**
 * @brief Trim trailing whitespaces from string.
 * 
 * @param s String to trim, will be changed.
 * @return std::string Reference to s
 */
std::string &rtrim(std::string &s);
/**
 * @brief Trim both traling and leading whitespaces.
 * 
 * @param s String to trim, will be changed.
 * @return std::string Reference to s
 */
std::string &trim(std::string &s);

} // NAMESPACE CC
