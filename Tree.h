//
// Created by nikita on 26.12.23.
//

#ifndef LAB2_TREE_H
#define LAB2_TREE_H

#include <iostream>
#include <string>
#include <vector>
#include <memory>

struct Tree {
  using Ptr = std::unique_ptr<Tree>;

  std::string node;

  std::vector<Tree::Ptr> children{};

  Tree(std::string name, std::vector<Tree::Ptr> nodes);

  Tree(std::string name);

  friend std::ostream& operator<<(std::ostream& out, Tree::Ptr const& node) noexcept;
};

#endif // LAB2_TREE_H
