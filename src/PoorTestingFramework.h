#ifndef __RandomHelperClasses_PoorTestingFramework_h
#define __RandomHelperClasses_PoorTestingFramework_h

#include <sstream>
#include <string>

template <class T>
class Enforcer {
public:
  Enforcer(const T& t, const std::string& file, size_t line) {
    if (t) {
      this->Good = true;
    } else {
      this->Good = false;
      this->Message << "Error at " << file << ":" << line << std::endl;
    }
  }

  void check() {
    if (!this->Good) {
      throw std::runtime_error(this->Message.str());
    }
  }

  template <class U>
  Enforcer<T>& operator()(const U& msg) {
    this->Message << msg;
    return *this;
  }
  template <class U>
  Enforcer<T>& operator()(U&& msg) {
    this->Message << msg;
    return *this;
  }

private:
  bool Good;
  std::stringstream Message;
};

template <class T>
Enforcer<T> MakeEnforcer(const T& t, const std::string& file, size_t line) {
  return Enforcer<T>(t, file, line);
}


template <typename T>
int RunTest(T test, std::string testname) {
  std::cout << "Run test " << testname << "... " << std::flush;
  try {
    test();
    std::cout << "PASSED" << std::endl;
    return 0;
  } catch (const std::exception& e) {
    std::cout << "FAILED" << std::endl;
    std::cerr << e.what() << std::endl;
    return 1; //failure
  } catch (...) {
    std::cout << "FAILED" << std::endl;
    std::cerr << "Unknown ... exception" << std::endl;
    return 1; //failure
  }
}

#define ENFORCE(x) srepModuleTesting::MakeEnforcer(x, __FILE__, __LINE__)

#define EXPECT_EQ(a, b) ENFORCE((a) == (b))("Expected ")(#a)(" == ")(#b)("\n  ")(a)(" == ")(b)("\n").check()
#define EXPECT_TRUE(a) ENFORCE(a)("Expected true:\n  ")(#a)("\n  Was false\n").check()
#define EXPECT_FALSE(a) ENFORCE(!(a))("Expected false:\n  ")(#a)("\n  Was true\n").check()

#define RUN_TEST(test) srepModuleTesting::RunTest(test, #test)

#endif
