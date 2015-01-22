#ifndef METASHELL_DEFAULT_ENVIRONMENT_DETECTOR_HPP
#define METASHELL_DEFAULT_ENVIRONMENT_DETECTOR_HPP

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

#include <metashell/logger.hpp>
#include <metashell/iface/environment_detector.hpp>
#include <metashell/iface/libclang.hpp>

namespace metashell
{
  class default_environment_detector : public iface::environment_detector
  {
  public:
    default_environment_detector(
      const std::string& argv0_,
      logger* logger_,
      iface::libclang& libclang_
    );

    virtual std::string search_clang_binary() override;
    virtual bool file_exists(const std::string& path_) override;

    virtual bool on_windows() override;
    virtual bool on_osx() override;

    virtual void append_to_path(const std::string& path_) override;

    virtual std::vector<std::string> default_clang_sysinclude(
      const std::string& clang_path_
    ) override;
    virtual std::vector<std::string> extra_sysinclude() override;

    virtual std::string path_of_executable() override;

    virtual bool clang_binary_works_with_libclang(
      const config& clang_path_
    ) override;
  private:
    std::string _argv0;
    logger* _logger;
    iface::libclang* _libclang;
  };
}

#endif


