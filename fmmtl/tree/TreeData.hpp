#pragma once


/** Maps boxes and box iterators to data and data iterators
 */
template <typename T, typename Tree>
struct BoxBind {
  typedef std::vector<T> container_type;
  typedef typename container_type::iterator iterator;
  typedef typename container_type::const_iterator const_iterator;

  container_type data;

  BoxBind(const Tree&, unsigned size)
      : data(size) {
  }

  T& operator[](const typename Tree::box_type& box) {
    return data[box.index()];
  }
  const T& operator[](const typename Tree::box_type& box) const {
    return data[box.index()];
  }

  iterator operator[](const typename Tree::box_iterator& bi) {
    return data.begin() + (*bi).index();
  }
  const_iterator operator[](const typename Tree::box_iterator& bi) const {
    return data.begin() + (*bi).index();
  }
};

template <typename T, typename Tree>
BoxBind<T,Tree> make_box_binding(const Tree& tree) {
  return {tree, tree.boxes()};
}


/** Maps bodies and body iterators to data and data iterators
 */
template <typename T, typename Tree>
struct BodyBind {
  typedef std::vector<T> container_type;
  typedef typename container_type::iterator iterator;
  typedef typename container_type::const_iterator const_iterator;

  //const Tree& tree;
  container_type data;

  struct BodyDataRange {
    iterator b, e;
    iterator begin() { return b; }
    iterator end()   { return e; }
  };

  BodyBind(const Tree& tree)
      : data(tree.bodies()) {
  }
  template <typename Range>
  BodyBind(const Tree& tree, const Range& range)
      : data(tree.body_permute(range.begin(), tree.body_begin()),
             tree.body_permute(range.begin(), tree.body_end())) {
  }

  iterator begin() { return data.begin(); }
  iterator end()   { return data.end(); }

  T& operator[](const typename Tree::body_type& body) {
    return data[body.index()];
  }
  const T& operator[](const typename Tree::body_type& body) const {
    return data[body.index()];
  }

  iterator operator[](const typename Tree::body_iterator& bi) {
    return data.begin() + bi.index();
  }
  const_iterator operator[](const typename Tree::body_iterator& bi) const {
    return data.begin() + bi.index();
  }

  BodyDataRange operator[](const typename Tree::box_type& box) {
    return {operator[](box.body_begin()), operator[](box.body_end())};
  }
};

template <typename Tree, typename Range>
BodyBind<typename Range::value_type,Tree>
make_body_binding(const Tree& tree, const Range& range) {
  return {tree, range};
}
