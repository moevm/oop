#ifndef LOGIC_THIRD_PARTY_INCLUDES_HPP
#define LOGIC_THIRD_PARTY_INCLUDES_HPP

// CPP
#include <exception>
#include <iostream>
#include <fstream>
#include <sstream>
#include <numeric>
#include <memory>
#include <random>
#include <string>
#include <vector>
#include <chrono>
#include <queue>
#include <list>
#include <map>
#include <set>
// C
#include <ctime> // TODO change to <chrono>
// Third party
#include "../utils/json.hpp"
using json = nlohmann::json; // Because I use this too frequently
// Ugly macros
#ifdef _MSC_VER // Because it is microsoft windows aka 'must die' aka 'I can't in ANSI' aka 'беды с башкой'
#define __func__ __FUNCTION__
#endif

#define STRINGIFY(x) #x // Deserved. (this cool feature translates literal to "literal")
#define TOSTRING(x) STRINGIFY(x) // Because cpp compiler is too stupid and can't in macro recursion
#define AT __FILE__ ":" TOSTRING(__LINE__) "\n - " // Because debugger kinda sucks when I use C# & JS & C++ at the same time
#define TRACE(x) std::cout << "TRACE: " << AT << (x) << std::endl // Just a little happy obsolete macro
#define LOCATED(x) AT x // Because it looks pretty cool

/// For the sake of readability. This freaking language just doesn't support attributes.
/// God damn I'm creating serialization without reflection
/// Path to clearing your soul:
/// Learn c++
/// Break up with a girl
/// Make useless define
#define N_S /*Non serialized*/
#define OBSOLETE /*Obsolete*/
/// *You are here*
/// <doctype=html />
/// Delet yuself
/// Epik vin

#endif //LOGIC_THIRD_PARTY_INCLUDES_HPP
