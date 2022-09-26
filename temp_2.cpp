#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <string.h>
// #include <>

using namespace std;

enum gate_type{
    AND,
    OR,
    NOT,
    NAND,
    XOR,
    XNOR,
    NOR
        
}gate_type;



class Node {

    public: 

        Node(int data=0, string name=""){        
            this->data=data;
            this->name=name;
        }
        void set_name(string name){//virtual
            this->name = name;
        }
        void set_data(int data){
            this->data =data ;
        }
        bool get_data(void){        
            return this->data;
        }
        string get_name(void){          
            return this->name;
        }
        static bool AND_(Node* A,Node* B){//pure virtual?
            
            return A->data & B->data; 
            
        }
        static bool OR(Node* A,Node* B){//pure virtual?

            return A->data | B->data; 

        }
        static bool XOR(Node* A,Node* B){//pure virtual?

            return A->data ^ B->data;        

        }
    private: 
        string name;
        bool data;//bool

    protected:  

    // public://protected
        // Node(){        
        //     this->data=0;
        //     this->name={""};
        // }

        
    
};
class Gate  /*protected Node*/
{
    public:



        virtual bool simulate_gate(void) = 0;
        static Gate* Create(enum gate_type type);


        

  
    protected:

        Gate(Node* input_1 = nullptr,Node* output=nullptr,Node* input_2=nullptr){
            
            this->input_1 = input_1;
            this->input_2 = input_2;
            this->output=output;
        }


        Node* input_1;
        Node* input_2;
        Node* output;

        
    protected: 
    
       /*return node values*/
        Node* get_input_1(void){
        
            return (this->input_1);
        }
        
        Node*  get_input_2(void){

            return (this->input_2);

            // return this->input_2->get_data();
        }
        void set_output(Node* output){
            // this->gate_function();
            this->output=output;

        }


        void set_input_1(Node* input){
            this->input_1 = input;
        }
        void set_input_2(Node* input){

            this->input_2 = input;
        
        }

};

class AND: public Gate{

    public:
    
    AND(Node* input_1 = nullptr,Node* output=nullptr,Node* input_2=nullptr)
    {
        this->input_1=input_1;
        this->input_2=input_2;
        this->output=output;    
    }
    

    bool simulate_gate(void) override{
        
        return Node::AND_(input_1,input_2);

    }
};
class NAND: public Gate{

    bool simulate_gate(void) override{
        
        return !(Node::AND_(input_1,input_2));

    }
};
class OR: public Gate{

    // OR(): Gate()
    // {}

    bool simulate_gate(void) override{
        
        return (Node::OR(input_1,input_2));

    }
};

class NOR: public Gate{

    bool simulate_gate(void) override{
        
        return !(Node::OR(input_1,input_2));

    }
};
class XOR: public Gate{

    bool simulate_gate(void) override{
        
        return (Node::XOR(input_1,input_2));

    }
};
class XNOR: public Gate{

    bool simulate_gate(void) override{
        
        return !(Node::XOR(input_1,input_2));

    }
};
class NOT: public Gate{

    bool simulate_gate(void) override{
        
        return !(input_1);

    }
};

Gate* Gate::Create(enum gate_type type) {

    if (type == AND)
        return new class AND();

    else if (type == OR)
        return new class OR();
    else if (type == XOR)
        return new class XOR();
    else return NULL;



}

class Simulator /*private Gate*///singelton
{

    private:
        vector<Gate*> gates;
        vector<Node*> nodes;
       
        void postNode(Node* node){
            nodes.push_back(node);
        }
       
        void postGate(Gate* gate){
            gates.push_back(gate);
        }
       
        Node& FindNode(string node_name){

            for(auto const& node : nodes){
                
                if(node_name == node->get_name()){

                    return  *node;//TODO: check that


                }

            }
            /*
            for(auto node in nodes)
            if node->name == name 
            return node;
            */

        }
        void startSimulate(void){

            for(auto const& gate : gates){

                gate->simulate_gate();

            }
            /*
            for gate in gates 
            gate->gate_function();
            */

        }


};

class GateGeneratortor: private Simulator{
    private:

        enum gate_type type;

    public: 
        void parseinput(void){

        }
    
        Gate& createGate(enum gate_type gate){//factory mehtod.. 

            return *(Gate::Create(type));

        }
    
        Node& createNode(void){

            return (*(new Node()));
        
        }
    

};

int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */   
    Simulator simulator();

    // parseinput()
    // simulate()
    return 0;
}
