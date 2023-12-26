//
// Created by nikita on 26.12.23.
//

#include "Tree.h"

Tree::Tree(std::string name, std::vector<Tree::Ptr> nodes) : node(std::move(name)), children(std::move(nodes)) {}

Tree::Tree(std::string name) : node(std::move(name)) {}

std::ostream& operator<<(std::ostream& out, Tree::Ptr const& node) noexcept {
  for (auto const& child : node->children) {
    out << node->node << " -> " << child->node << '\n' << child;
  }
}
