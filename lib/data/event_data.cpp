// Metashell - Interactive C++ template metaprogramming shell
// Copyright (C) 2018, Abel Sinkovics (abel@sinkovics.hu)
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

#include <metashell/data/event_data.hpp>

namespace metashell
{
  namespace data
  {
    namespace impl
    {
      namespace
      {
        template <class T>
        boost::none_t point_of_event(const T&)
        {
          return boost::none;
        }

        template <class T>
        boost::none_t source_location(const T&)
        {
          return boost::none;
        }
      }
    }

    event_data template_begin(event_kind kind,
                              const type& type,
                              const file_location& point_of_event,
                              const file_location& source_location,
                              double timestamp)
    {
      switch (kind)
      {
      case event_kind::template_instantiation:
        return event_details<event_kind::template_instantiation>{
            type, point_of_event, source_location, timestamp};
        break;
      case event_kind::default_template_argument_instantiation:
        return event_details<
            event_kind::default_template_argument_instantiation>{
            type, point_of_event, source_location, timestamp};
        break;
      case event_kind::default_function_argument_instantiation:
        return event_details<
            event_kind::default_function_argument_instantiation>{
            type, point_of_event, source_location, timestamp};
        break;
      case event_kind::explicit_template_argument_substitution:
        return event_details<
            event_kind::explicit_template_argument_substitution>{
            type, point_of_event, source_location, timestamp};
        break;
      case event_kind::deduced_template_argument_substitution:
        return event_details<
            event_kind::deduced_template_argument_substitution>{
            type, point_of_event, source_location, timestamp};
        break;
      case event_kind::prior_template_argument_substitution:
        return event_details<event_kind::prior_template_argument_substitution>{
            type, point_of_event, source_location, timestamp};
        break;
      case event_kind::default_template_argument_checking:
        return event_details<event_kind::default_template_argument_checking>{
            type, point_of_event, source_location, timestamp};
        break;
      case event_kind::exception_spec_instantiation:
        return event_details<event_kind::exception_spec_instantiation>{
            type, point_of_event, source_location, timestamp};
        break;
      case event_kind::declaring_special_member:
        return event_details<event_kind::declaring_special_member>{
            type, point_of_event, source_location, timestamp};
        break;
      case event_kind::defining_synthesized_function:
        return event_details<event_kind::defining_synthesized_function>{
            type, point_of_event, source_location, timestamp};
        break;
      case event_kind::memoization:
        return event_details<event_kind::memoization>{
            type, point_of_event, source_location, timestamp};
        break;
      default:
        assert(!"Invalid event_kind");
        break;
      }
    }

    event_kind kind_of(const event_data& data)
    {
      return visit([](const auto& details) { return kind_of(details); }, data);
    }

    relative_depth relative_depth_of(const event_data& data)
    {
      return relative_depth_of(kind_of(data));
    }

    bool is_remove_ptr(const event_data& data)
    {
      return visit(
          [](const auto& details) { return is_remove_ptr(details); }, data);
    }

    boost::optional<file_location> point_of_event(const event_data& data)
    {
      return mpark::visit(
          [](const auto& details) -> boost::optional<file_location> {
            using metashell::data::impl::point_of_event;
            return point_of_event(details);
          },
          data);
    }

    boost::optional<file_location> source_location(const event_data& data)
    {
      return mpark::visit(
          [](const auto& details) -> boost::optional<file_location> {
            using metashell::data::impl::source_location;
            return source_location(details);
          },
          data);
    }

    boost::optional<double> timestamp(const event_data& data)
    {
      return mpark::visit(
          [](const auto& details) { return timestamp(details); }, data);
    }

    boost::optional<data::type> type_of(const event_data& data)
    {
      return mpark::visit(
          [](const auto& details) { return type_of(details); }, data);
    }

    void set_type(event_data& data, type t)
    {
      mpark::visit(
          [&t](auto& details) { return set_type(details, std::move(t)); },
          data);
    }

    bool from_line(const event_data& event, const file_location& line)
    {
      const boost::optional<file_location> poe = point_of_event(event);
      return poe && poe->name == line.name && poe->row == line.row;
    }
  }
}
