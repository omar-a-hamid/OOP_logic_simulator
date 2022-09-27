#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <string>
#include <assert.h>
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

        Node(bool data=0, char name='0'){        
            this->data=data;
            this->name=name;
        }
        void set_name(char name){//virtual
            this->name = name;
        }
        void set_data(bool data){
            this->data =data ;
        }
        bool get_data(void){        
            return this->data;
        }
        char get_name(void){          
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
    friend ostream& operator<<(ostream& out, const Node& node);

    private: 
        char name;
        bool data;//bool

    protected:  

    // public://protected
        // Node(){        
        //     this->data=0;
        //     this->name={""};
        // }

        
    
};



ostream& operator<<(ostream& out, const Node& node)
{
    out <<  node.name << " " <<node.data;
    return out;
}

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
    

    public:
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
        
        this->output->set_data(Node::AND_(input_1,input_2));
        return this->output->get_data();


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
    else if (type == NOR)
        return new class NOR();
    else if (type == XNOR)
        return new class XNOR();
    else if (type == NOT)
        return new class NOT();
    else if (type == NAND)
        return new class NAND();
    else assert(false);



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
       
        Node* FindNode(char node_name){

            for(auto const& node : nodes){
                
                if(node_name == node->get_name()){

                    return  node;//TODO: check that


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
            static string stdin_string;
            char gate_1,gate_2,gate_3;
            while(cin){

                getline(cin, stdin_string);
                string delimiter = " ";
                
                string command = stdin_string.substr(0, stdin_string.find(delimiter));
                string command_data = stdin_string.substr(stdin_string.find(delimiter)+1 );
                // cout << command<<endl;
                
                if(command=="AND"){
                    /*
                    check for nodes if the dont exsist, create nodes  
                    */
                    
                    Gate* gate_ptr = createGate(AND);
                    Node* node_i1 = createNode();
                    node_i1->set_name(command_data[0]);
                    Node* node_i2 = createNode();
                    node_i2->set_name(command_data[2]);

                    Node* node_o = createNode();
                    node_o->set_name(command_data[4]);


                    gate_ptr->set_input_1(node_i1);
                    gate_ptr->set_input_2(node_i2);
                    gate_ptr->set_output(node_o);




                    cout<<
                    command_data[0]
                    <<endl;
                    cout<<
                    command_data[2]
                    <<endl;
                    cout<<
                    command_data[4]
                    <<endl;
                    // cout<<"and" <<endl;



                }else if(command=="NAND"){
                    // cout<<"nand" <<endl;
                    // while(cin>>gate_1>>gate_2>>gate_3);

                }else if(command=="OR"){
                    // cout<<"or" <<endl;
                    
                }else if(command=="NOR"){
                    // cout<<"nor" <<endl;
                    
                }else if(command=="XOR"){
                    // cout<<"xor" <<endl;
                    
                }else if(command=="XNOR"){
                    // cout<<"xnor" <<endl;
                    
                }else if(command=="NOT"){
                    // cout<<"not" <<endl;
                    
                }else if(command=="SET"){
                    // cout<<"set" <<endl;
                    
                }else if(command=="SIM"){
                    // cout<<"sim" <<endl;
                    

                }else if(command=="GET"){
                    // cout<<"get" <<endl;
                }else if(command=="OUT"){
                    // cout<<"out" <<endl;
                }

            
            }

            

        }
    
        Gate* createGate(enum gate_type type){//factory mehtod.. 

            return (Gate::Create(type));

        }
    
        Node* createNode(void){

            return ((new Node()));
        
        }
    private: 


};

int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */   
    Simulator simulator();
    GateGeneratortor gen;

    gen.parseinput();

    // Node* node_i1 = (gen.createNode());
/*    Node* node_i1= new Node(0,"A");
    Node* node_i2 = (gen.createNode());
    Node* node_o = (gen.createNode());

    Gate* gate = (gen.createGate(AND));

    gate->set_input_1(node_i1);
    gate->set_input_2(node_i2);
    gate->set_output(node_o);


    node_i1->set_data(true);
    node_i2->set_data(true);

    cout <<gate->simulate_gate()<<endl;

    node_i1->set_data(false);
    node_i2->set_data(true);

    cout <<gate->simulate_gate()<<endl;
        
    node_i1->set_data(true);
    node_i2->set_data(false);

    cout <<gate->simulate_gate()<<endl;
    node_i1->set_data(false);
    node_i2->set_data(false);

    cout <<gate->simulate_gate()<<endl;

    node_i1->set_data(true);
    node_i2->set_data(true);

    cout <<gate->simulate_gate()<<endl;

    cout << "fetch data: "<<node_o->get_data() <<endl;
    node_i1->set_data(false);
    node_i2->set_data(true);

    cout <<gate->simulate_gate()<<endl;

    // cout << "fetch data: "<<node_o->get_data() <<endl;
    cout << *node_o<<endl;

*/
    // cout<<node_o->get_data()<<endl;


    // Node* node_ptr;
    // Node node_ptr;

    // node_ptr->set_data(1);

    // cout << node_ptr->get_data()<<endl;


    // gen.createNode();

    // parseinput()
    // simulate()
    return 0;
}
