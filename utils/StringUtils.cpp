#include "StringUtils.h"

namespace StringUtils {

std::string getPaddedNumberString(int n, int length) {
    // Create an empty string stream
    std::stringstream sstream;
    // Convert the number to a string normally, without padding
	const std::string nStr = std::to_string(n);
    // If the string's length is less than the fixed length requested, then we need padding
	if (nStr.length() < length) {
        // Pad the string with the remaining number of zeros
        // by appending that many zeros to the empty string stream
		for (int i = 0; i < length - nStr.length(); i++) {
			sstream << '0';
		}
	}
    // After the appended zeros (if any) append the number itself
	sstream << nStr;
    // Return the resulting string from the string stream
	return sstream.str();
}

} // namespace StringUtils