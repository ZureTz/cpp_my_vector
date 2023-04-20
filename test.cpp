#include "include/myvector"
#include <cmath>
#include <cstddef>
#include <cstdlib>
#include <fstream>
#include <initializer_list>
#include <iostream>
#include <ostream>

// output the vector using operator "<<"
template <typename T>
std::ostream &operator<<(std::ostream &os, const my::vector<T> &vect) {
  if (vect.empty()) {
    os << "[]" << std::endl;
    return os;
  }

  os << '[';
  for (typename my::vector<T>::iterator it = vect.begin(); it != vect.end() - 1;
       it++) {
    os << *it << ", ";
  }
  os << vect.back() << ']' << std::endl;

  return os;
}

std::ostream &output(std::ostream &os) {

  // using default constructor
  my::vector<int> vect1;
  os << vect1;

  // push back two "int"s
  vect1.push_back(3).push_back(2);

  // element access
  os << vect1.at(0) << std::endl;

  os << std::endl;

  // using copy constructor (also using overloaded "=" operator)
  my::vector<int> vect2(vect1);
  vect2.at(1) = 3;
  os << vect1.at(1) << " " << vect2.at(1) << std::endl;

  // using overloaded "=" operator
  // testing if they are two different vectors
  (vect2 = vect1).at(0) = 0;
  os << vect1.at(0) << " " << vect2.at(0) << std::endl;

  os << std::endl;

  // using template with type "double"
  my::vector<double> vect3{M_PI, M_E, M_LN2};
  os << vect3;

  // test if empty
  os << vect3.empty() << std::endl;

  os << std::endl;

  my::vector<int> vect4;
  // test if empty when it initializes
  os << vect4.empty() << std::endl;
  // using "resize()"
  vect4.resize(9);
  // using "size()" and "length"
  os << vect4.size() << std::endl
     << vect4.length()
     << std::endl
     // to know actual capacity
     << vect4.capacity() << std::endl;

  os << std::endl;

  // initialize with "initializer_list"
  my::vector<int> vect5{
      1, 2, 3, 4, 5, 6, 7, 8, 9,
  };
  // using "front()" and "end()"
  os << vect5.front() << " " << vect5.back() << std::endl;

  os << std::endl;

  // using overloaded "=" operator
  auto vect6 = vect5;
  // using overloaded comparison operators
  os << (vect6 == vect5) << std::endl;
  os << (vect6 != vect5) << std::endl;
  vect6.push_back(10);
  os << (vect6 == vect5) << std::endl;
  os << (vect6 != vect5) << std::endl;
  // using range-based "for" loop
  os << vect6;

  os << std::endl;

  // reverse the vector
  vect6.reverse();
  os << vect6;

  vect6.resize(vect6.size() + 2);
  os << vect6;

  vect6.pop_back();
  os << vect6;

  vect6.pop_front();
  os << vect6;

  os << vect6.slice(vect6.begin(), vect6.end() - 2);

  // using "clear"
  vect6.clear();
  os << vect6;

  // using "insert"

  // swapping two vectors
  vect6.swap(vect5);
  os << vect6;

  os << std::endl;

  my::vector<int> insert_vector{1, 2, 3, 4, 5};
  insert_vector = {1, 2, 3, 4, 5, 6};
  os << insert_vector;

  os << std::endl;

  my::vector<int> vect7{0, 1, 2, 3, 4, 5};
  my::vector<int> vect8{1, 2, 3};
  vect1.insert(vect1.begin() + 3, vect2.begin(), vect2.end());
  os << vect1;
  vect1.insert(vect1.begin(), static_cast<size_t>(3), 3);
  os << vect1;
  vect1.insert(vect1.begin() + 2, {2, 0, 4, 2, 5, 4});
  os << vect1;
  vect1.insert(vect1.end(), 1145);
  os << vect1;
  vect1.erase(vect1.begin() + 3);
  os << vect1;
  vect1.erase(vect1.begin() + 2, vect1.end() - 7);
  os << vect1;
  vect1.push_back(3).push_front(6).push_back(9);
  os << vect1;
  vect1.reverse();
  os << vect1;

  return os;
}

int main(int argc, char const *argv[]) {
  std::fstream file;
  file.open("result.txt");
  if (!file.is_open()) {
    std::cerr << "file is not open!" << std::endl;
    exit(EXIT_FAILURE);
  }
  output(file);
  file.close();


  return 0;
}