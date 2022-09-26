#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <string.h>
// #include <>

using namespace std;


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
        static bool AND(Node* A,Node* B){//pure virtual?
            
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
        Gate(Node* input_1 = nullptr,Node* output=nullptr,Node* input_2=nullptr){
            
            this->input_1 = input_1;
            this->input_2 = input_2;
            this->output=output;
        }
        virtual bool simulate_gate(void) = 0;

  
    protected:
        
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

class AND: protected Gate{

    bool simulate_gate(void) override{
        
        return Node::AND(input_1,input_2);

    }
};
class NAND: protected Gate{

    bool simulate_gate(void) override{
        
        return !(Node::AND(input_1,input_2));

    }
};
class OR: protected Gate{

    bool simulate_gate(void) override{
        
        return (Node::OR(input_1,input_2));

    }
};

class NOR: protected Gate{

    bool simulate_gate(void) override{
        
        return !(Node::OR(input_1,input_2));

    }
};
class XOR: protected Gate{

    bool simulate_gate(void) override{
        
        return (Node::XOR(input_1,input_2));

    }
};
class XNOR: protected Gate{

    bool simulate_gate(void) override{
        
        return !(Node::XOR(input_1,input_2));

    }
};
class NOT: protected Gate{

    bool simulate_gate(void) override{
        
        return !(input_1);

    }
};



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

    public: 
        void parseinput(void){

        }
    /*
        Gate& createGate(void){

        }
        Node& createNode(void){

        }
    */

};

int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */   
    Simulator simulator();

    // parseinput()
    // simulate()
    return 0;
}
