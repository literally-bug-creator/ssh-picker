#include "tui.hpp"

#include <string>
#include <vector>

#include "ftxui/component/component.hpp"
#include "ftxui/component/component_base.hpp"
#include "ftxui/component/component_options.hpp"
#include "ftxui/component/screen_interactive.hpp"
#include "ftxui/dom/elements.hpp"

using namespace ftxui;

bool TUI::isShouldExit() const {
    return shouldExit_;
}

void TUI::onSelectHost(const std::string& selectedHost,
                       std::string& selectedForExecution) {
    shouldExit_ = true;
    selectedForExecution = selectedHost;
}

Component TUI::buildMenu(const std::vector<std::string>& menuEntries) {
    auto menuOption = MenuOption();
    auto menu = Menu(&menuEntries, &selectedItemIdx_, menuOption);

    return CatchEvent(menu, [&](const Event& event) {
        if (event == Event::Return) {
            onSelectHost(menuEntries[selectedItemIdx_], selectedForExecution_);
            return true;
        }
        return false;
    });
}

Component TUI::buildInfoDisplay(
    const std::vector<std::string>& menuEntries) const {
    return Renderer([&] {
        return vbox({
            text("Selected: " + menuEntries[selectedItemIdx_]),
            separator(),
            text("Index: " + std::to_string(selectedItemIdx_)),
            separator(),
            text("Total items: " + std::to_string(menuEntries.size())),
        });
    });
}
