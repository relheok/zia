#ifndef EXAMPLE_HPP_
# define EXAMPLE_HPP_

# include <iostream>
# include <memory>

class     Example {
public:
  Example();
  Example(const Example &);
  Example &operator=(const Example &);
  ~Example();

  bool          initComponent();

  std::string   &getName() const;
  void          setName(std::string const &);

private:
  std::unique_ptr<Example>  _ptr{nullptr};
  std::string               _name;
};

#endif /* end of include guard: EXAMPLE_HPP_ */
