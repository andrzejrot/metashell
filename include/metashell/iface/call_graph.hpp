#ifndef METASHELL_IFACE_CALL_GRAPH_HPP
#define METASHELL_IFACE_CALL_GRAPH_HPP

// Metashell - Interactive C++ template metaprogramming shell
// Copyright (C) 2014, Abel Sinkovics (abel@sinkovics.hu)
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.

#include <metashell/call_graph_node.hpp>

#include <boost/range/adaptor/type_erased.hpp>
#include <boost/iterator/iterator_categories.hpp>

#include <vector>

namespace metashell
{
  namespace iface
  {
    typedef
      boost::any_range<
        const call_graph_node,
        boost::forward_traversal_tag
      >
      call_graph;
  }
}

#endif
