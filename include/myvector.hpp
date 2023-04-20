#ifndef __MYVECTOR_H
#define __MYVECTOR_H

/*
This is a library developed by myself to realize the same function as
std::vector. It can be used in dynamic arrays with the ability to resize itself
automatically when an element is inserted or deleted, with their storage being
handled automatically by the container.

* vectors are automatically allocated and freed/destructed, preventing memory
  leak
* insert or delete a element as you want
* using iterator to point at the memory addresses of containers
*/

#include <algorithm>
#include <cstddef>
#include <cstdlib>
#include <initializer_list>
#include <iostream>
#include <type_traits>

// using initializer_list to initialize a vector
#include <initializer_list>

namespace my {

template <typename T> class vector {
public:
  /* Forward declaration */
  class iterator;
  class const_iterator;

  /* Type definitions */
  typedef T element_type;
  typedef T *element_pointer;
  typedef T &element_reference;
  typedef T &&element_right_reference;
  typedef const T *const_element_pointer;
  typedef const T &const_element_reference;
  typedef size_t size_type;
  typedef vector<T> self_type;

  /* Constructors */

  // Default
  vector();

  // Length Constructor
  vector(const int length);

  // Copy Constructor
  vector(const self_type &source);

  // Construct from another one using range (begin and end)
  // using iterator
  vector(const_iterator first, const_iterator last);

  // Move Constructor
  vector(self_type &&source);

  // Initialization List Constructor
  explicit vector(const std::initializer_list<element_type> init_list);

  /* Destructor */
  ~vector();

  /* Get info */

  // returns true if the list is empty
  bool empty() const;

  // Returns the length/size of the vector
  // Complexity: Constant(O(1)), using iterator substraction
  size_type size() const;

  // Same as size();
  size_type length() const;

  // Capacity
  size_type capacity() const;

  // Returning a certain element
  element_reference operator[](const int pos);
  element_reference at(const int pos);

  /* ELEMENT ACCESS  */

  // Returns a direct reference to the front element, throws if list is empty
  element_reference front();
  const_element_reference front() const;

  // Returns a direct reference to the rear element, throws if list is empty
  element_reference back();
  const_element_reference back() const;

  /* Iterators */

  iterator begin();
  const_iterator begin() const;

  iterator end();
  const_iterator end() const;

  /****** COMPARISON OPERATORS ******/

  // Compares sizes, then comapres each element of the list for equality
  bool operator==(const self_type &rhs) const;

  // returns the logical NOT of the equality comparison
  bool operator!=(const self_type &rhs) const;

  /* Modifiers */

  // Resize the vector
  self_type &resize(const int size);

  // Push element in front
  self_type &push_front(element_right_reference argument);
  self_type &push_front(const_element_reference argument);

  // Push element in back
  self_type &push_back(element_right_reference argument);
  self_type &push_back(const_element_reference argument);

  // pop element in front
  self_type &pop_front();

  // pop element in back
  self_type &pop_back();
  // pop back and return the value and store it to a virable.
  element_type pop_back(element_reference out_param);

  // Remove all elements
  self_type &clear();

  // Reverse all elements in order
  self_type &reverse();

  // Sort the vector, using STL
  self_type &sort();
  template <typename Compare> self_type &sort(Compare &&comp);

  // Slice
  self_type slice(const_iterator begin, const_iterator end);

  // swap two vectors
  // may use std::swap
  void swap(self_type &object);

  // assign the value in a special way
  self_type &operator=(const self_type &object);

private:
  element_pointer vector_address = nullptr;
  element_pointer vector_end = nullptr;
  element_pointer vector_actual_end = nullptr;

public:
  class const_iterator {
  public:
    /* Type definitions */
    typedef const_iterator self_type;

    /* Constructors */
    // default: iterator are set to nullptr
    const_iterator(element_pointer ptr = nullptr) : pointer(ptr) {}

    /* Operator overloads */
    // dereference
    const_element_reference operator*() const;

    // comparison operators
    bool operator>(const self_type &rhs) const;
    bool operator>=(const self_type &rhs) const;
    bool operator<(const self_type &rhs) const;
    bool operator<=(const self_type &rhs) const;
    bool operator!=(const self_type &rhs) const;
    bool operator==(const self_type &rhs) const;

#if 0
    // returns increased value, not changing pointer itself
    self_type &operator+=(int num) const;
    self_type &operator++() const;
    // return pointer itself
    self_type operator++(int) const;
#endif

    // plus or substract
    self_type operator+(int rhs);
    self_type operator-(int rhs);

#if 0
    // returns decreased value, not changing pointer itself
    self_type &operator-=(int num) const;
    self_type &operator--() const;
    // returns pointer itself
    self_type operator--(int) const;
#endif

    // "-" to calculate the range
    int operator-(self_type &rhs) const;

    friend vector<T>;

  private:
    element_pointer pointer;
  };

  class iterator : public const_iterator {
  public:
    /* Type definitions */
    typedef iterator self_type;

    /* Constructors */
    // default: iterator are set to nullptr
    iterator(element_pointer ptr = nullptr) : const_iterator(ptr) {}
    iterator(const const_iterator &it) : const_iterator(it) {}
    iterator(const_iterator &&it) : const_iterator(it) {}

    /* Operator overloads */
    // dereference
    element_reference operator*();

    // self-increase
    self_type &operator+=(int num);
    self_type &operator++();
    self_type operator++(int);

    // self-decrease
    self_type &operator-=(int num);
    self_type &operator--();
    self_type operator--(int);
  };
};

} // namespace my
#endif
