#include <string>
#include <vector>

using std::string;
using std::vector;

class Solution {
public:
  string longestCommonPrefix(vector<string> &strs) {
    if (strs.size() == 0)
      return "";

    std::string prefix = strs[0];
    size_t prefix_size = prefix.size();
    for (auto si = strs.begin() + 1; si != strs.end() and prefix_size > 0;
         ++si) {
      for (size_t i = 0; i < prefix_size; ++i) {
        if (prefix[i] != si->at(i)) {
          prefix_size = i;
          break;
        }
      }
    }
    return prefix.substr(0, prefix_size);
  }
};
