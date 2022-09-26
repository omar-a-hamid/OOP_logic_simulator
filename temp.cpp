#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <string.h>
// #include <>

using namespace std;


typedef enum gate_type{
    AND,
    OR,
    NOT,
    NAND,
    XOR,
    XNOR,
    NOR
        
}gate_type;

class Node {
    private: 
        string name;
        int data;//bool

    protected:  
        bool AND(Node* A,Node* B){//pure virtual?
            
            return this->data = A->data & B->data; 
            
        }
        bool OR(Node* A,Node* B){//pure virtual?

            return this->data = A->data | B->data; 

        }
        bool XOR(Node* A,Node* B){//pure virtual?

            return this->data = A->data ^ B->data;        

        }
    // public://protected
        Node(int data, string name){        
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
        
    
};
class Gate  /*protected Node*/
{
  
    private:
        
        Node* input_1;
        Node* input_2;
        Node* output;
        gate_type type;
        
    protected: 
    /*
        void AND(void){
            
            this->output= this->input_1 & this->input_2;
            
        }
        void OR(void){

            

            this->output=this->input_1 | this->input_2;

            

        }
        void NOT(void){

            

            this->output=!this->input_1;

            

        }
        
        void NAND(void){
            
            this->output=!(this->input_1 & this->input_2);
            
        }
        void NOR(void){
            
            this->output=!(this->input_1 | this->input_2);
            
        }

        void XOR(void){
            
            this->output=this->input_1 ^ this->input_2;
            
        }
        void XNOR(void){

            

            this->output=!(this->input_1 ^ this->input_2);

            

        }
        */
       /*return node values*/
        Node* get_input_1(void){
        
            return (this->input_1);
        }
        
        bool  get_input_2(void){
            return this->input_2->get_data();
        }
        void set_output(Node* output){
            // this->gate_function();
            this->output=output;

        }

        void simulate_gate(void){
            switch (this->type){
            case AND:
                // this->AND();
                break;
            case OR:
                    output->OR(input_1,input_2);
                    break;
            case XOR:
                    output->XOR(input_1,input_2);
                    break;
            case NAND:
                    // output=(int)!(output->AND(input_1,input_2));
                    // return get_output();
                    break;
            
            }
            }
        void set_input_1(Node* input){
            this->input_1 = input;
        }
        void set_input_2(Node* input){

            this->input_2 = input;
        }
};

class AND: 



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
            /*
            for(auto node in nodes)
            if node->name == name 
            return node;
            */

        }
        void startSimulate(void){
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
