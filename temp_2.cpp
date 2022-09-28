#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <string>
#include <assert.h>

using namespace std;

enum gate_type
{
    AND,
    OR,
    NOT,
    NAND,
    XOR,
    XNOR,
    NOR

} gate_type;

class Node
{

public:
    Node(bool data = 0, char name = '0')
    {
        this->data = data;
        this->name = name;
    }
    Node(char name = '0')
    {
        this->data = 0;
        this->name = name;
    }
    void set_name(char name)
    { 
        this->name = name;
    }
    void set_data(bool data)
    {
        this->data = data;
    }
    bool get_data(void)
    {
        return this->data;
    }
    char get_name(void)
    {
        return this->name;
    }
    static bool AND_(Node *A, Node *B)
    { 

        return A->data & B->data;
    }
    static bool OR(Node *A, Node *B)
    { 

        return A->data | B->data;
    }
    static bool XOR(Node *A, Node *B)
    { 

        return A->data ^ B->data;
    }
    friend ostream &operator<<(ostream &out, const Node &node);

private:
    char name;
    bool data; 

};

ostream &operator<<(ostream &out, const Node &node)
{
    out << node.name << ": " << node.data;
    return out;
}

class Gate 
{
protected:
    Gate(Node *input_1 = nullptr, Node *output = nullptr, Node *input_2 = nullptr)
    {

        this->input_1 = input_1;
        this->input_2 = input_2;
        this->output = output;
    }

    Node *input_1;
    Node *input_2;
    Node *output;

public:
    virtual bool simulate_gate(void) = 0;
    static Gate *Create(enum gate_type type);


    Node *get_input_1(void)
    {

        return (this->input_1);
    }

    Node *get_input_2(void)
    {

        return (this->input_2);

    }
    void set_output(Node *output)
    {
        this->output = output;
    }

    void set_input_1(Node *input)
    {
        this->input_1 = input;
    }
    void set_input_2(Node *input)
    {

        this->input_2 = input;
    }
};

class AND : public Gate
{

public:
    AND(Node *input_1 = nullptr, Node *output = nullptr, Node *input_2 = nullptr) // TODO: delete
    {
        this->input_1 = input_1;
        this->input_2 = input_2;
        this->output = output;
    }

    bool simulate_gate(void) override
    {

        this->output->set_data(Node::AND_(input_1, input_2));
        return this->output->get_data();
    }
};
class NAND : public Gate
{

    bool simulate_gate(void) override
    {

        this->output->set_data(!(Node::AND_(input_1, input_2)));
        return this->output->get_data();
    }
};
class OR : public Gate
{

    bool simulate_gate(void) override
    {

        this->output->set_data(Node::OR(input_1, input_2));
        return this->output->get_data();
    }
};

class NOR : public Gate
{

    bool simulate_gate(void) override
    {

        this->output->set_data(!(Node::OR(input_1, input_2)));
        return this->output->get_data();
    }
};
class XOR : public Gate
{

    bool simulate_gate(void) override
    {

        this->output->set_data(Node::XOR(input_1, input_2));
        return this->output->get_data();
    }
};
class XNOR : public Gate
{

    bool simulate_gate(void) override
    {

        this->output->set_data(!(Node::XOR(input_1, input_2)));

        return this->output->get_data();
    }
};
class NOT : public Gate
{

    bool simulate_gate(void) override
    {

        this->output->set_data(!(input_1->get_data()));
        return this->output->get_data();
    }
};

Gate *Gate::Create(enum gate_type type)
{

    switch (type)
    {

    case AND:
        return new class AND();
        break;

    case NAND:
        return new class NAND();
        break;

    case OR:
        return new class OR();
        break;

    case NOR:
        return new class NOR();
        break;

    case XOR:
        return new class XOR();
        break;

    case XNOR:
        return new class XNOR();
        break;

    case NOT:
        return new class NOT();
        break;

    default:
        assert(false);
        break;
    }
    
}

class Simulator 
{

private:
    static vector<Gate *> gates;
    static vector<Node *> nodes;

public:
    static void postNode(Node *node)
    {
        nodes.push_back(node);
    }

    static void postGate(Gate *gate)
    {
        gates.push_back(gate);
    }

    static void print_all_nodes(void)
    {
        for (auto const &node : nodes)
            cout << *node << endl;
    }
    static Node *FindNode(char node_name)
    {

        for (auto const &node : nodes)
        {

            if (node_name == node->get_name())
            {

                return node; 
            }
        }

        return nullptr;
    }
    static void startSimulate(void)
    {

        for (auto const &gate : gates)
        {

            gate->simulate_gate();
        }

    }
};

vector<Node *> Simulator::nodes;
vector<Gate *> Simulator::gates;

class GateGeneratortor : private Simulator
{


public:
    void parseinput(void)
    {
        static string stdin_string;
        while (getline(cin, stdin_string))
        {

            string delimiter = " ";

            string command = stdin_string.substr(0, stdin_string.find(delimiter));
            string command_data = stdin_string.substr(stdin_string.find(delimiter) + 1);

            if (command == "AND")
            {

                gate_parse(AND, command_data);

            }
            else if (command == "NAND")
            {
                gate_parse(NAND, command_data);

            }
            else if (command == "OR")
            {
                gate_parse(OR, command_data);

            }
            else if (command == "NOR")
            {
                gate_parse(NOR, command_data);

            }
            else if (command == "XOR")
            {
                gate_parse(XOR, command_data);

            }
            else if (command == "XNOR")
            {
                gate_parse(XNOR, command_data);

            }
            else if (command == "NOT")
            {
                gate_parse(NOT, command_data);

            }
            else if (command == "SET")
            {

                Node *node_ptr = createNode(command_data[0]);
                if (command_data[2] == '0')
                    node_ptr->set_data(false);
                else
                    node_ptr->set_data(true);

            }
            else if (command == "SIM")
            {
                Simulator::startSimulate();


            }
            else if (command == "OUT")
            {

                if (command_data.length() == 1)
                { 
                    Node *node_ptr = createNode(command_data[0]);
                    cout << *node_ptr << endl;
                }
                else
                {

                    Simulator::print_all_nodes();
                }
            }
        }
    }

private:

    enum gate_type type;
    Gate *createGate(enum gate_type type)
    {

        return (Gate::Create(type));
    }

    Node *createNode(char name)
    {

        if (Simulator::FindNode(name))
        {
            return Simulator::FindNode(name);
        }
        else
        {

            Node *new_node = new Node(name);
            Simulator::postNode(new_node);
            return (new_node);
        }
    }


    void gate_parse(enum gate_type type, string command_data)
    {
        Gate *gate_ptr = createGate(type);

        /*
        check if nodes exsist, if nodes exsist return address else create, use simulator functions               //TODO

        */
        Node *node_i1 = createNode(command_data[0]);

        if (type == NOT)
        {

            Node *node_o = createNode(command_data[2]);
            gate_ptr->set_output(node_o);
        }
        else
        {
            Node *node_i2 = createNode(command_data[2]);
            Node *node_o = createNode(command_data[4]);
            gate_ptr->set_output(node_o);
            gate_ptr->set_input_2(node_i2);
        }
        gate_ptr->set_input_1(node_i1);
        Simulator::postGate(gate_ptr);
    }
};

int main()
{
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */
    Simulator simulator();
    GateGeneratortor gen;
    gen.parseinput();
    return 0;
}