//     Subclass            Children                                        Description
//     --------            --------                                        -----------
//   ASTNode:                                                              the base class
//     ProgramNode         DeclListNode                                    the whole program
//     DeclListNode        a list of DeclNode                              a list of declarations, e.g. int a; void f(){}
//
//     DeclNode:                                                           a declaration
//       VarDeclNode       TypeNode, IdNode                                a variable declaration, e.g. int a;
//       FnDeclNode        TypeNode, IdNode, FormalsListNode, FnBodyNode   a function definition, e.g. void f(...){...}
//       FormalDeclNode    TypeNode, IdNode                                a funtion parameter declaration, e.g. int a
//
//     FormalsListNode     a list of FormalDeclNode                        a list of function parameters, e.g. (int a, bool b)
//     FnBodyNode          DeclListNode, StmtListNode                      the function body
//     StmtListNode        a list of StmtNode                              a list of statements
//
//     TypeNode:                                                           a type keyword
//       IntNode           -- none --                                      the keyword int
//       BoolNode          -- none --                                      the keyword bool
//       VoidNode          -- none --                                      the keyword void
//
//     StmtNode:                                                           a statement end with semicolon ;
//       AssignStmtNode      AssignNode                                    an assign statement, e.g. a=1;
//       PostIncStmtNode     ExpNode                                       a post increase statement, e.g. a++;
//       PostDecStmtNode     ExpNode                                       a pose decrease statement, e.g. a--;
//
//     ExpNode:                                                            an expression
//       IntLitNode          -- none --                                    an int literal, e.g. 1
//       TrueNode            -- none --                                    the keyword true
//       FalseNode           -- none --                                    the keyword false
//       IdNode              -- none --                                    an identifier, e.g. a, f, main
//       AssignNode          ExpNode, ExpNode                              an assignemnt expression, e.g. a=1 (notice no ";")

#include <iostream>
#include <string>
#include <sstream>

using namespace std;

// constants used
#define MAX_NUM_NODE 100
#define MAX_NUM_CHILD 10
#define SIZE_TAB 4

// forward declaration of classes
class ASTNode;
class ProgramNode;
class DeclListNode;
class DeclNode;
class VarDeclNode;
class FnDeclNode;
class FormalDeclNode;
class FormalsListNode;
class FnBodyNode;
class StmtListNode;
class TypeNode;
class IntNode;
class BoolNode;
class VoidNode;
class StmtNode;
class AssignStmtNode;
class PostIncStmtNode;
class PostDecStmtNode;
class ExpNode;
class IntLitNode;
class TrueNode;
class FalseNode;
class IdNode;
class AssignNode;

// **********************************************************************
// ASTNode class (base class for all other kinds of nodes)
// **********************************************************************

class ASTNode {
   public:
    ASTNode(int n = 0) : num_child(n) {}
    virtual ~ASTNode(){};

    int numChild() {
        return num_child;
    }

    void setChild(int index, ASTNode* ptr) {
        children[index] = ptr;
    }

    void addIndent(int indent) {
        for (int i = 0; i < indent; ++i) {
            cout << " ";
        }
    }

    virtual void unparse(int indent) = 0;

   protected:
    int num_child;
    ASTNode* children[MAX_NUM_CHILD];
};

// **********************************************************************
// ProgramNode,  DeclListNode, FormalsListNode, FnBodyNode, StmtListNode
// **********************************************************************

class ProgramNode : public ASTNode {
   public:
    ProgramNode(int n = 0) : ASTNode(n) {}

    void unparse(int indent) {
        children[0]->unparse(indent);  // unparse DeclListNode
    }
};

class DeclListNode : public ASTNode {
   public:
    DeclListNode(int n = 0) : ASTNode(n) {}

    void unparse(int indent) {
        for (int i = 0; i < num_child; ++i) {
            children[i]->unparse(indent);  // unparse DeclNode
        }
    }
};

class FormalsListNode : public ASTNode {
   public:
    FormalsListNode(int n = 0) : ASTNode(n) {}

    void unparse(int indent) {
        // TODO
        for (int i = 0; i < num_child; i++) {
            children[i]->unparse(indent); // unparse FormalDeclNode
        }
    }
};

class FnBodyNode : public ASTNode {
   public:
    FnBodyNode(int n = 0) : ASTNode(n) {}

    void unparse(int indent) {
        // TODO, think about what indent value to pass to its children!
        // For all its children in this function body, 4 spaces indent needed
        children[0]->unparse(indent + 4); // unparse DeclListNode
        children[1]->unparse(indent + 4); // unparse StmtListNode
    }
};

class StmtListNode : public ASTNode {
   public:
    StmtListNode(int n = 0) : ASTNode(n) {}

    void unparse(int indent) {
        // TODO
        for (int i = 0; i < num_child; i++) {
            children[i]->unparse(indent); // unparse StmtNode
            cout << ";/n";
        }
    }
};

// **********************************************************************
// DeclNode and its subclasses
// **********************************************************************

class DeclNode : public ASTNode {
   public:
    DeclNode(int n = 0) : ASTNode(n) {}

    virtual void unparse(int indent) = 0;
};

class VarDeclNode : public DeclNode {
   public:
    VarDeclNode(int n = 0) : DeclNode(n) {}

    void unparse(int indent) {
        // TODO
        children[0]->unparse(indent); // unparse TypeNode
        children[1]->unparse(indent); // unparse IdNode
    }
};

class FnDeclNode : public DeclNode {
   public:
    FnDeclNode(int n = 0) : DeclNode(n) {}

    void unparse(int indent) {
        addIndent(indent);
        children[0]->unparse(indent);  // unparse TypeNode
        cout << " ";
        children[1]->unparse(indent);  // unparse IdNode
        cout << "(";
        children[2]->unparse(indent);  // unparse FormalsListNode
        cout << ") {" << endl;
        children[3]->unparse(indent);  // unparse FnBodyNode
        addIndent(indent);
        cout << "}" << endl;
    }
};

class FormalDeclNode : public DeclNode {
   public:
    FormalDeclNode(int n = 0) : DeclNode(n) {}

    void unparse(int indent) {
        // TODO
        children[0]->unparse(indent); // unparse TypeNode
        cout << " ";
        children[1]->unparse(indent); // unparse IdNode
    }
};

// **********************************************************************
// TypeNode and its Subclasses
// **********************************************************************

class TypeNode : public ASTNode {
   public:
    TypeNode(int n = 0) : ASTNode(n) {}

    virtual void unparse(int indent) = 0;
};

class IntNode : public TypeNode {
   public:
    IntNode(int n = 0) : TypeNode(n) {}

    void unparse(int indent) {
        // TODO
        addIndent(indent);
        cout << "int";
    }
};

class BoolNode : public TypeNode {
   public:
    BoolNode(int n = 0) : TypeNode(n) {}

    void unparse(int indent) {
        // TODO
        addIndent(indent);
        cout << "bool";
    }
};

class VoidNode : public TypeNode {
   public:
    VoidNode(int n = 0) : TypeNode(n) {}

    void unparse(int indent) {
        // TODO
        addIndent(indent);
        cout << "void";
    }
};

// **********************************************************************
// StmtNode and its subclasses
// **********************************************************************

class StmtNode : public ASTNode {
   public:
    StmtNode(int n = 0) : ASTNode(n) {}

    virtual void unparse(int indent) = 0;
};

class AssignStmtNode : public StmtNode {
   public:
    AssignStmtNode(int n = 0) : StmtNode(n) {}

    void unparse(int indent) {
        // TODO
        children[0]->unparse(indent); // unparse AssignNode
    }
};

class PostIncStmtNode : public StmtNode {
   public:
    PostIncStmtNode(int n = 0) : StmtNode(n) {}

    void unparse(int indent) {
        // TODO
        children[0]->unparse(indent + 4); // unparse the ExpNode
        cout << "++\n";
    }
};

class PostDecStmtNode : public StmtNode {
   public:
    PostDecStmtNode(int n = 0) : StmtNode(n) {}

    void unparse(int indent) {
        // TODO
        children[0]->unparse(indent); // unparse the ExpNode
        cout << "--\n";
    }
};

// **********************************************************************
// ExpNode and its subclasses
// **********************************************************************

class ExpNode : public ASTNode {
   public:
    ExpNode(int n = 0) : ASTNode(n) {}

    virtual void unparse(int indent) = 0;
};

class IntLitNode : public ExpNode {
   public:
    IntLitNode(int n = 0, int val = 0) {
        num_child = n;
        myVal = val;
    }

    void unparse(int indent) {
        // TODO
        addIndent(indent);
        cout << myVal;
    }

   private:
    int myVal;
};

class TrueNode : public ExpNode {
   public:
    TrueNode(int n = 0) : ExpNode(n) {}

    void unparse(int indent) {
        // TODO
        addIndent(indent);
        cout << "true";
    }
};

class FalseNode : public ExpNode {
   public:
    FalseNode(int n = 0) : ExpNode(n) {}

    void unparse(int indent) {
        // TODO
        addIndent(indent);
        cout << "false";
    }
};

class IdNode : public ExpNode {
   public:
    IdNode(int n = 0, string str = "") {
        num_child = n;
        myName = str;
    }

    virtual void unparse(int indent) {
        // TODO
        addIndent(indent);
        cout << myName;
    }

   private:
    string myName;
};

class AssignNode : public ExpNode {
   public:
    AssignNode(int n = 0) : ExpNode(n) {}

    void unparse(int indent) {
        // TODO
        children[0]->unparse(indent); // unparse the first ExpNode
        cout << " = ";
        children[1]->unparse(indent); //unparse the second ExpNode
        cout << "\n";
    }
};


int main() {
    // TODO: read input line by line, allocate new node, store into array
    ASTNode* nodes[MAX_NUM_NODE];

    int node_num = 0;
    cin >> node_num;
    getchar();
// Step 3: Save each line of input as a node into an array

    for (int i = 0; i < node_num; i++) {

        string line, node_type, optional_para;
        getline(cin, line);
        int child_num = 0;
        stringstream ss;
        ss << line;
        ss >> node_type >> child_num;

        if (node_type == "ProgramNode") {nodes[i] = new ProgramNode(child_num);}
        else if (node_type == "DeclListNode") {nodes[i] = new DeclListNode(child_num);}
        else if (node_type == "VarDeclNode") {nodes[i] = new VarDeclNode(child_num);}
        else if (node_type == "FnDeclNode") {nodes[i] = new FnDeclNode(child_num);}
        else if (node_type == "FormalDeclNode") {nodes[i] = new FormalDeclNode(child_num);}
        else if (node_type == "FormalsListNode") {nodes[i] = new FormalsListNode(child_num);}
        else if (node_type == "FnBodyNode") {nodes[i] = new FnBodyNode(child_num);}
        else if (node_type == "StmtListNode") {nodes[i] = new StmtListNode(child_num);}
        else if (node_type == "IntNode") {nodes[i] = new IntNode(child_num);}
        else if (node_type == "BoolNode") {nodes[i] = new BoolNode(child_num);}
        else if (node_type == "VoidNode") {nodes[i] = new VoidNode(child_num);}
        else if (node_type == "AssignStmtNode") {nodes[i] = new AssignStmtNode(child_num);}
        else if (node_type == "PostIncStmtNode") {nodes[i] = new PostIncStmtNode(child_num);}
        else if (node_type == "PostDecStmtNode") {nodes[i] = new PostDecStmtNode(child_num);}
        else if (node_type == "IntLitNode") {
            int val;
            ss >> val;
            nodes[i] = new IntLitNode(child_num, val);
        }
        else if (node_type == "TrueNode") {nodes[i] = new TrueNode(child_num);}
        else if (node_type == "FalseNode") {nodes[i] = new FalseNode(child_num);}
        else if (node_type == "IdNode") {
            string str;
            ss >> str;
            nodes[i] = new IdNode(child_num, str);
        }
        else if (node_type == "AssignNode") {nodes[i] = new AssignNode(child_num);}
    }
    // TODO: traverse array to construct the tree
    // Step 4
    nodes[0]->setChild(0, nodes[1]);
    nodes[1]->setChild(0, nodes[2]);
    int num = 3; // the nodes to be linked (from nodes[3] to nodes[node_num - 1])
    int num_in_layer[2] = {nodes[1]->numChild(), nodes[2]->numChild()};
    while (num < node_num) {
        for (int to_be_link = 0; to_be_link < num_in_layer[2]; to_be_link++) {
            for (int link_to = num_in_layer[1]; link_to > 0; link_to--) {
                for (int link_to_children = 0; link_to_children < nodes[num - link_to]->numChild(); link_to_children++) {
                    nodes[num - link_to]->setChild(link_to_children, nodes[num + to_be_link]);
                }
            }
        }
        num += num_in_layer[2];
    }

    for (int i = 1; i < node_num; i++) {

    }

    for (int i = 0; i < node_num; i++) {

        int child_to_add = nodes[i]->numChild();
        for (int child = 0; child < child_to_add; child++) {
            nodes[i]->setChild(child, nodes[i + child + 1]);
        }

    }

    // call unparse() of root to print whole program
    ASTNode* root = nodes[0];
    root->unparse(0);

    // TODO: delete the allocated nodes
    for (int i = 0; i < node_num; i++) {
        delete nodes[i];
    }
}

