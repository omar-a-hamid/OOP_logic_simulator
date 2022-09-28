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
        Node(char name='0'){        
            this->data=0;
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
    out <<  node.name << ": " <<node.data;
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
    
    AND(Node* input_1 = nullptr,Node* output=nullptr,Node* input_2=nullptr)//TODO: delete
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

        this->output->set_data(!(Node::AND_(input_1,input_2)));
        return this->output->get_data();

    }
};
class OR: public Gate{

    // OR(): Gate()
    // {}

    bool simulate_gate(void) override{
        
        this->output->set_data (Node::OR(input_1,input_2));
        return this->output->get_data();


    }
};

class NOR: public Gate{

    bool simulate_gate(void) override{
        
        this->output->set_data(!(Node::OR(input_1,input_2)));
        return this->output->get_data();

    }
};
class XOR: public Gate{

    bool simulate_gate(void) override{
        
        this->output->set_data (Node::XOR(input_1,input_2));
        return this->output->get_data();
 

    }
};
class XNOR: public Gate{

    bool simulate_gate(void) override{
        
        this->output->set_data (!(Node::XOR(input_1,input_2)));

        return this->output->get_data();


    }
};
class NOT: public Gate{

    bool simulate_gate(void) override{
        
        this->output->set_data (!(input_1));
        return this->output->get_data();


    }
};


Gate* Gate::Create(enum gate_type type) {

    switch(type){

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
    /*


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
    */


}

class Simulator /*private Gate*///singelton
{

    private:
        static vector<Gate*> gates;
        static vector<Node*> nodes;
       

    public:
        static void postNode(Node* node){
            nodes.push_back(node);
        }
       
        static void postGate(Gate* gate){
            gates.push_back(gate);
        }
       
        static void print_all_nodes(void){
            for(auto const& node : nodes)
                cout << *node<<endl;

        }
        static Node* FindNode(char node_name){

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
           return nullptr;

        }
        static void startSimulate(void){

            for(auto const& gate : gates){

                gate->simulate_gate();

            }
            /*
            for gate in gates 
            gate->gate_function();
            */

        }


};

vector<Node*> Simulator::nodes;
vector<Gate*> Simulator::gates;


class GateGeneratortor: private Simulator{
    private:

        enum gate_type type;

    public: 
        void parseinput(void){
            static string stdin_string;
            // char gate_1,gate_2,gate_3;
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
                    gate_parse(AND, command_data);

                    /*
                    Gate* gate_ptr = createGate(AND);
                    Node* node_i1 = createNode();
                    node_i1->set_name(command_data[0]);
                    Node* node_i2 = createNode();
                    node_i2->set_name(command_data[2]);

                    Node* node_o = createNode();
                    node_o->set_name(command_data[4]);


                    gate_ptr->set_input_1(node_i1);
                    gate_ptr->set_input_2(node_i2);
                    gate_ptr->set_output(node_o); */



                    /*
                    cout<<
                    command_data[0]
                    <<endl;
                    cout<<
                    command_data[2]
                    <<endl;
                    cout<<
                    command_data[4]
                    <<endl;
                    */
                    // cout<<"and" <<endl;



                }else if(command=="NAND"){
                    gate_parse(NAND, command_data);

                    // cout<<"nand" <<endl;
                    // while(cin>>gate_1>>gate_2>>gate_3);

                }else if(command=="OR"){
                    gate_parse(OR, command_data);

                    // cout<<"or" <<endl;
                    
                }else if(command=="NOR"){
                    gate_parse(NOR, command_data);

                    // cout<<"nor" <<endl;
                    
                }else if(command=="XOR"){
                    gate_parse(XOR, command_data);

                    // cout<<"xor" <<endl;
                    
                }else if(command=="XNOR"){
                    gate_parse(XNOR, command_data);

                    // cout<<"xnor" <<endl;
                    
                }else if(command=="NOT"){
                    gate_parse(NOT, command_data);

                    // cout<<"not" <<endl;
                    
                }else if(command=="SET"){


                    Node* node_ptr = createNode(command_data[0]);
                    if(command_data[2]=='0')
                        node_ptr->set_data(false);
                    else    
                        node_ptr->set_data(true);
                    // cout<<"set" <<endl;
                    /*search for node, set its logic value*/
                    
                }else if(command=="SIM"){

                    /*startSimulate in simulator class, scans over all gate and  runs them*/
                    Simulator::startSimulate();

                    // cout<<"sim" <<endl;
                    

                }else if(command=="OUT"){
                    // cout<<"out" <<endl;
                    /*search for node and print it, if all, print all... */
                    if(command_data.length()==1){//one char 
                        Node* node_ptr = createNode(command_data[0]);
                        cout<<*node_ptr<<endl;
                    }else{/*if all*/
                        
                        Simulator::print_all_nodes();

                    }

                }

            
            }

            

        }
    private:
        Gate* createGate(enum gate_type type){//factory mehtod.. //TODO: pass args? 

            return (Gate::Create(type));

        }
    
        Node* createNode(char name){      
            
           if(Simulator::FindNode(name)){
                return Simulator::FindNode(name);
           }else{

                Node* new_node = new Node(name);
                Simulator::postNode(new_node);
                return (new_node);
           }
        
        }
    private: 

        void gate_parse(enum gate_type type,string command_data)
        {                    
            Gate* gate_ptr = createGate(type);


            /*
            check if nodes exsist, if nodes exsist return address else create, use simulator functions               //TODO
            
            */
            Node* node_i1 = createNode(command_data[0]);


             

            if (type == NOT){

                Node* node_o = createNode(command_data[2]);
                gate_ptr->set_output(node_o);



            }else{
                Node* node_i2 = createNode(command_data[2]);
                Node* node_o = createNode(command_data[4]);
                gate_ptr->set_output(node_o);
                gate_ptr->set_input_2(node_i2);

            }


            gate_ptr->set_input_1(node_i1);
            Simulator::postGate(gate_ptr);

        
        }



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
