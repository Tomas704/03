#include "interpreter.hpp"
#include "turtle.hpp"
#include "turtle_gui.hpp"

#include <libfriimgui/window.hpp>

#include <imgui/imgui.h>

#include <string>

#include "heap_monitor.hpp"

int main(int argc, char *argv[])
{
    namespace tp = turtlepreter;

    (void)argc;
    (void)argv;

    const std::string cTurtleImg = ".\\turtlepreter\\resources\\turtle.png";
    const int cWidth = 1280;
    const int cHeight = 720;
    const int cCenterX = cWidth / 2;
    const int cCenterY = cHeight / 2;

    // Create window, make OpenGL available.
    friimgui::Window *window = friimgui::Window::initializeWindow(cWidth, cHeight);

    // Create the turtle.
    tp::Turtle turtle(cTurtleImg, cCenterX, cCenterY);

    turtle.jump(cCenterX + 50, cCenterY - 50);
    turtle.rotate(3.14159f / 2.0f);
    turtle.jump(cCenterX - 50, cCenterY + 50);
    turtle.reset();

    tp::Node *otec = new tp::Node();

    tp::ICommand *jump1 = new tp::CommandJump(cCenterX + 100.0f, cCenterY + 100.0f);
    tp::ICommand *jump2 = new tp::CommandJump(cCenterX - 50.0f, cCenterY + 50.0f);

    tp::Node *syn1 = new tp::Node(jump1);
    tp::Node *syn2 = new tp::Node(jump2);

    otec->addSubnode(syn1);
    otec->addSubnode(syn2);

    // Interpret the tree from the root.
    tp::Interpreter interpreter(otec);

    // Create GUI.
    tp::TurtleGUI turtleGUI(&turtle, &interpreter);

    // Render GUI.
    window->setGUI(&turtleGUI);
    window->run();
    friimgui::Window::releaseWindow();

    delete otec;
}
