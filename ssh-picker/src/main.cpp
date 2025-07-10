#include <functional>
#include <iostream>
#include <string>
#include <vector>

#include "ftxui/component/component.hpp"
#include "ftxui/component/component_base.hpp"
#include "ftxui/component/screen_interactive.hpp"
#include "tui.hpp"

using namespace ftxui;

int main() {
    std::vector<std::string> menuEntries = {"server", "aboba", "serva4ok",
                                            "hhh"};

    TUI tui = TUI();
    Component menu = tui.buildMenu(menuEntries);
    Component infoDisplay = tui.buildInfoDisplay(menuEntries);

    Component container = Container::Horizontal({
        menu,
        infoDisplay,
    });

    auto screen = ScreenInteractive::TerminalOutput();

    auto renderer = Renderer(container, [&] {
        if (tui.isShouldExit()) {
            screen.ExitLoopClosure()();
        }
        return vbox({
                   hbox({
                       vbox({
                           hcenter(bold(text("Available Hosts"))),
                           separator(),
                           menu->Render(),
                       }),
                       separator(),
                       vbox({
                           hcenter(bold(text("Info"))),
                           separator(),
                           infoDisplay->Render(),
                       }) | flex,
                   }),
               }) |
               border;
    });

    screen.Loop(renderer);

    if (tui.isShouldExit()) {
        std::cout << "Exit" << "\n";
    }
}
