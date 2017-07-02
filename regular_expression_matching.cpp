class Solution {
public:
  template <typename It>
  bool isMatchStar(char c, It sbeg, It send, It pbeg, It pend) {
    auto eatall = std::find_if_not(
        sbeg, send, [c](char val) { return val == c || c == '.'; });

    do {
      if (isMatchHere(eatall, send, pbeg, pend)) {
        return true;
      }
    } while (eatall-- != sbeg);
    return false;
  }

  template <typename It> bool isMatchHere(It sbeg, It send, It pbeg, It pend) {
    if (pbeg == pend) {
      if (sbeg == send) {
        return false;
      } else {
        return false;
      }
    }
    if ((pbeg + 1) != pend && *(pbeg + 1) == '*') {
      // '**' sequence of two stars is prohibited
      assert(pbeg + 2 == pend || *(pbeg + 2) != '*');
      return isMatchStar(*pbeg, sbeg, send, pbeg + 2, pend);
    }
    if (sbeg != send and (*pbeg == '.' || *pbeg == *sbeg)) {
      return isMatchHere(sbeg + 1, send, pbeg + 1, pend);
    }
    return false;
  }

  bool isMatch(std::string s, std::string p) {
    return isMatchHere(s.begin(), s.end(), p.begin(), p.end());
  }
};