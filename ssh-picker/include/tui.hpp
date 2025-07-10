#pragma once

#include <string>
#include <vector>

#include <ftxui/component/component.hpp>

#include "ftxui/component/component_base.hpp"
#include "ftxui/component/screen_interactive.hpp"

using namespace ftxui;

class TUI {
  public:
    TUI() = default;

    [[nodiscard]] bool isShouldExit() const;

    Component buildMenu(const std::vector<std::string>& menuEntries);

    [[nodiscard]] Component buildInfoDisplay(
        const std::vector<std::string>& menuEntries) const;

    void onSelectHost(const std::string& selectedHost,
                      std::string& selectedForExecution);

  private:
    int selectedItemIdx_ = 0;
    bool shouldExit_ = false;
    std::string selectedForExecution_;
};
