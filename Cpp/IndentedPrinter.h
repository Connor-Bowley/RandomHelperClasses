#ifndef __RandomHelperClasses_IndentedPrinter_h
#define __RandomHelperClasses_IndentedPrinter_h

#include <string>

class IndentedPrinter {
public:
  void enter() {
    m_indents += 2;
  }
  void exit() {
    m_indents = std::max(m_indents - 2, 0);
  }
  void nextNeedsIndent() {
    this->m_nextNeedsIndent = true;
  }
  bool getNextNeedsIndent() {
    bool needs = this->m_nextNeedsIndent;
    this->m_nextNeedsIndent = false;
    return needs;
  }
  std::string indents() const {
    std::string ret = "";
    for (int i = 0; i < this->m_indents; ++i) {
      ret += " ";
    }
    return ret;
  }

  class Scope {
  public:
    Scope(IndentedPrinter& p_)
      : p(p_)
    {
      p.enter();
    }
    ~Scope() {
      p.exit();
    }
  private:
    IndentedPrinter& p;
  };

private:
  bool m_nextNeedsIndent = false;
  int m_indents = 0;
};

template <typename T>
IndentedPrinter& operator<<(IndentedPrinter& p, const T& t) {
  std::stringstream ss;
  ss << t;

  auto tstr = ss.str();

  //super poor coding here
  std::string s;
  for (const auto c : tstr) {
    if (c == '\n') {
      s += "\n";
      p.nextNeedsIndent();
    } else {
      if (p.getNextNeedsIndent()) {
        s += p.indents();
      }
      s += c;
    }
  }
  std::cout << s;
  return p;
}
template <typename T>
IndentedPrinter& operator<<(IndentedPrinter& p, T&& t) {
  std::stringstream ss;
  ss << t;

  auto tstr = ss.str();

  //super poor coding here
  std::string s;
  for (const auto c : tstr) {
    if (c == '\n') {
      s += "\n";
      p.nextNeedsIndent();
    } else {
      if (p.getNextNeedsIndent()) {
        s += p.indents();
      }
      s += c;
    }
  }
  std::cout << s;
  return p;
}

#endif
