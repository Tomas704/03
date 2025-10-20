#include "interpreter.hpp"
#include <stdexcept>

#include "heap_monitor.hpp"

namespace turtlepreter
{

    Node::Node() : m_parent(nullptr), m_command(nullptr)
    {
    }

    Node::Node(ICommand *command) : m_parent(nullptr), m_command(command)
    {
    }

    Node::~Node()
    {
        for (Node *subnode : m_subnodes)
        {
            delete subnode;
        }
        delete m_command;
    }

    std::string Node::toString() const
    {
        if (m_command == nullptr)
        {
            return "No command";
        }
        return m_command->toString();
    }

    void Node::addSubnode(Node *subnode)
    {
        if (subnode != nullptr)
        {
            m_subnodes.push_back(subnode);
            subnode->m_parent = this;
        }
    }

    Node *Node::getParent() const
    {
        return m_parent;
    }

    const std::vector<Node *> &Node::getSubnodes() const
    {
        return m_subnodes;
    }

    ICommand *Node::getCommand() const
    {
        return m_command;
    }

    // ==================================================

    // TODO CommandMove definitions

    CommandMove::CommandMove(float d) : m_d(d)
    {
        //
    }

    void CommandMove::execute(Turtle &turtle)
    {
        turtle.move(m_d); //
    }

    std::string CommandMove::toString()
    {
        //
        return "Move(" + std::to_string(m_d) + ")";
    }

    // ==================================================

    // TODO CommandJump definitions

    CommandJump::CommandJump(float x, float y) : m_x(x), m_y(y)
    {
        //
    }

    void CommandJump::execute(Turtle &turtle)
    {
        turtle.jump(m_x, m_y); //
    }

    std::string CommandJump::toString()
    {
        //
        return "Jump(" + std::to_string(m_x) + ", " + std::to_string(m_y) + ")";
    }

    // ==================================================

    // TODO CommandRotate definitions

    CommandRotate::CommandRotate(float angleRad) : m_angleRad(angleRad)
    {
        //
    }

    void CommandRotate::execute(Turtle &turtle)
    {
        turtle.rotate(m_angleRad); //
    }

    std::string CommandRotate::toString()
    {
        //
        return "Rotate(" + std::to_string(m_angleRad) + ")";
    }

    // ==================================================

    Interpreter::Interpreter(Node *root) : m_root(root)
    {
    }

    void Interpreter::interpretAll(Turtle &turtle)
    {
        this->interpterSubtreeNodes(m_root, turtle);
    }

    Node *Interpreter::getRoot() const
    {
        return m_root;
    }

    void Interpreter::interpterSubtreeNodes(Node *node, Turtle &turtle)
    {
        (void)node;
        (void)turtle;
        throw std::logic_error("Not implemented yet!");
    }

} // namespace turtlepreter
