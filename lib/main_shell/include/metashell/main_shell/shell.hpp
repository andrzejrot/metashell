#ifndef METASHELL_MAIN_SHELL_SHELL_HPP
#define METASHELL_MAIN_SHELL_SHELL_HPP

// Metashell - Interactive C++ template metaprogramming shell
// Copyright (C) 2013, Abel Sinkovics (abel@sinkovics.hu)
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

#include <metashell/core/logger.hpp>

#include <metashell/data/config.hpp>

#include <metashell/iface/displayer.hpp>
#include <metashell/iface/engine.hpp>
#include <metashell/iface/environment.hpp>
#include <metashell/iface/history.hpp>
#include <metashell/iface/pragma_handler.hpp>
#include <metashell/iface/shell.hpp>

#include <boost/filesystem/path.hpp>
#include <boost/optional.hpp>

#include <map>
#include <memory>
#include <set>
#include <stack>
#include <string>
#include <vector>

namespace metashell
{
  namespace main_shell
  {
    class shell : public iface::shell
    {
    public:
      shell(const data::config& config_,
            const boost::filesystem::path& internal_dir_,
            const boost::filesystem::path& env_filename_,
            std::function<std::unique_ptr<iface::engine>(const data::config&)>
                engine_builder_,
            std::map<std::vector<std::string>,
                     std::unique_ptr<iface::pragma_handler>> pragma_handlers_ =
                {},
            core::logger* logger_ = nullptr,
            std::unique_ptr<iface::environment> env_ =
                std::unique_ptr<iface::environment>());

      void display_splash(
          iface::displayer& displayer_,
          const std::map<std::string, std::string>& dependency_versions_);
      virtual void line_available(const std::string& s_,
                                  iface::displayer& displayer_,
                                  iface::history& history_) override;
      void line_available(const std::string& s_, iface::displayer& displayer_);
      virtual std::string prompt() const override;

      virtual void cancel_operation() override;

      bool store_in_buffer(const data::cpp_code& s_,
                           iface::displayer& displayer_) override;

      void run_metaprogram(const data::cpp_code& s_,
                           iface::displayer& displayer_) override;

      virtual void code_complete(const std::string& s_,
                                 std::set<std::string>& out_) override;

      const std::map<std::vector<std::string>,
                     std::unique_ptr<iface::pragma_handler>>&
      pragma_handlers() const override;

      virtual bool stopped() const override;
      void stop() override;

      const iface::environment& env() const override;
      iface::environment& env() override;

      void reset_environment() override;
      void push_environment() override;
      void pop_environment() override;
      void
      display_environment_stack_size(iface::displayer& displayer_) override;
      void rebuild_environment() override;

      const data::config& get_config() const override;
      data::config& get_config() override;

      iface::engine& engine() override;

      boost::filesystem::path env_path() const override;

      bool preprocess(iface::displayer& displayer_,
                      const data::cpp_code& exp_,
                      bool process_directives_) override;

      bool enabled(data::shell_flag) const override;
      void enabled(data::shell_flag, bool) override;

    private:
      boost::filesystem::path _internal_dir;
      boost::filesystem::path _env_filename;
      std::string _line_prefix;
      std::unique_ptr<iface::environment> _env;
      data::config _config;
      std::string _prev_line;
      std::map<std::vector<std::string>, std::unique_ptr<iface::pragma_handler>>
          _pragma_handlers;
      bool _stopped;
      std::stack<data::cpp_code> _environment_stack;
      core::logger* _logger;
      std::function<std::unique_ptr<iface::engine>(const data::config&)>
          _engine_builder;
      std::map<std::string, std::unique_ptr<iface::engine>> _engines;
      bool _echo = false;
      bool _show_cpp_errors = true;
      bool _evaluate_metaprograms = true;

      void rebuild_environment(const data::cpp_code& content_);
    };
  }
}

#endif
