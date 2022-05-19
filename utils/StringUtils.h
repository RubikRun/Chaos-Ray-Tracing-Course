#pragma once

#include <string>
#include <sstream>

namespace StringUtils {

/// Returns an integer as a string padded with zeros so that it is of some fixed length
std::string getPaddedNumberString(int n, int length);

} // namespace StringUtils