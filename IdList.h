#include <iostream>
#include <vector>
#include <string>
#include <string.h>
#include<cstring>

using namespace std;

struct IdInfo 
{
    string type;
    string name;
    string value;
    string decl;
    int constant; 
};

struct ArrayInfo 
{
    string type;
    string name;
    string value;
    string decl;
    int constant;
    int size;
    int index;
};

struct ClassInfo 
{
    string name;
    vector <IdInfo> variabile;
    vector <ArrayInfo> var_arr;
    //vector <FunctionInfo> funct;
};

struct FunctionInfo 
{
    string type;
    string name;
    string decl;
    vector <ArrayInfo> variabile;//variabilele din paranteza
};

class ASTNode
{ public:
    string type;
    string root;
    string value;
    ASTNode* left;
    ASTNode* right;

    string verECB_B(const char *op, const char *nume1, const char *nume2)
    {
        if(strncmp(op, "==", strlen("=="))==0) {if(nume1==nume2) return "true";}
        else if(strncmp(op, "!=", strlen("!="))==0) {if(nume1!=nume2) return "true";}
        else if(strncmp(op, "||", strlen("||"))==0) {if(nume1=="false" && nume2=="false") return "false"; else return "true";}
        else if(strncmp(op, "&&", strlen("&&"))==0) {if(nume1=="true" && nume2=="true") return "true";}
        return "false";
    }

    string verECB_B(const char *op, const char *nume1)
    {
        if(strncmp(op, "!", strlen("!"))==0) {if(nume1=="false") return "true";}
        return "false";
    }

    string calculExpNR_NR(const char* op, const char* type , const char* nume1, const char* nume2)
    {
        float rezultat_f;
        int rezultat_i;
        bool rezultat_b;
        char buf[10];
        char* rezultatString = new char[20];
        if(strncmp(op, "+", strlen("+"))==0) {rezultat_f = stof(nume2) + stof(nume1); rezultat_i = stoi(nume2) + stof(nume1);}
        else if(strncmp(op, "-", strlen("-"))==0) {rezultat_f = stof(nume2) - stof(nume1); rezultat_i = stoi(nume2) - stof(nume1);}
        else if(strncmp(op, "*", strlen("*"))==0) {rezultat_f = stof(nume2) * stof(nume1); rezultat_i = stoi(nume2) * stof(nume1);}
        else if(strncmp(op, "/", strlen("/"))==0) {rezultat_f = stof(nume2) / stof(nume1); rezultat_i = stoi(nume2) / stof(nume1);}
        else if(strncmp(op, "<=", strlen("<="))==0) {if(nume1<=nume2) return "true" ;}
        else if(strncmp(op, ">=", strlen(">="))==0) {if(nume1>=nume2) return "true";}
        else if(strncmp(op, "<", strlen("<"))==0) {if(nume1<nume2) return "true";}
        else if(strncmp(op, ">", strlen(">"))==0) {if(nume1>nume2) return "true";}
        else if(strncmp(op, "==", strlen("=="))==0) {if(nume1==nume2) return "true";}
        else if(strncmp(op, "!=", strlen("!="))==0) {if(nume1!=nume2) return "true";}

        if(string(type)=="float")
        {
            sprintf(rezultatString, "%f", rezultat_f);
        }
        else if(string(type)=="int")
        {
            sprintf(rezultatString, "%d", rezultat_i);
        }
        return rezultatString;
    }
    ASTNode();

    ASTNode(const char* tip, const char * valoare)
    {
        this->type=string(tip);
        this->value=string(valoare);
        this->left=NULL;
        this->right=NULL;
    }

    ASTNode(ASTNode* nod)
    {
        this->type=nod->type;
        this->value=nod->value;
        this->left=nod->left;
        this->right=nod->right;
    }

    ASTNode (const char* op, ASTNode* nod1, ASTNode* nod2)
    {   
        if(nod1->type == nod2->type)
            if(strcmp(op, "==")==0 || strcmp(op, "!=")==0 || strcmp (op, "<")==0 || strcmp (op, "<=")==0 || strcmp (op, ">")==0 || strcmp (op, ">=")==0) this->type="bool";
            else this->type=nod1->type;
        this->left=nod1;
        this->right=nod2;
        this->root=op;
        if(nod1->type=="int" || nod1->type=="float")
            this->value=calculExpNR_NR(op, this->type.c_str(), nod1->value.c_str(), nod2->value.c_str()); 
        else if(nod1->type=="bool")
             this->value=verECB_B(op, nod1->value.c_str(), nod2->value.c_str()); 
    }
    
    ASTNode (const char* op, ASTNode* nod1)
    {  
        this->type=nod1->type;
        this->left=nod1;
        this->root=op;
        if(nod1->type=="bool")
            this->value=verECB_B(op, nod1->value.c_str()); 
    }

    static ASTNode *new_ast_node(const char* tip, const char * valoare)
    {
        ASTNode *node =  new ASTNode(tip, valoare);
        return node;
    }

    static ASTNode *new_ast_root(const char* op, ASTNode* nod1, ASTNode* nod2)
    {
        ASTNode *node =  new ASTNode(op, nod1, nod2);
        return node;
    }

    static ASTNode *new_ast_node(ASTNode* nod1)
    {
        ASTNode *node =  new ASTNode(nod1);
        return node;
    }

    static ASTNode *new_ast_node(const char* op, ASTNode* nod)
    {
        ASTNode *node =  new ASTNode(op, nod);
        return node;
    }

    void assignLeft(ASTNode* nod)
    {
        left=nod;
    }

};

class IdList {
    vector<IdInfo> vars;
    vector<ArrayInfo> array;
    vector<ClassInfo> clasa;
    
    
    public: 
    string tipul, tipul_f;

    ///////////////////////////////ADAUGARE//////////////////////////////////////////////////////////////////////////////////////

    void addVar(const char* type, const char* name ); 
    void addVar(const char *type, const char *name, const char *index);
    void addClass(const char* name);
    void AlocConst(const char* name);
    void AlocConst(const char* name, const char* id);

    ///////////////////////////////VERIFICARE EXISTENTA//////////////////////////////////////////////////////////////////////////////////////

    bool existsClass(const char* name);
    bool existsVar(const char* s);
    bool existsVar(const char *name, const char* id);
    int VerConst(const char* name);
    int VerConst(const char* name, const char* id);

    ///////////////////////////////PT OPERATII BOOL//////////////////////////////////////////////////////////////////////////////////////

    int verECID_ID(const char* op, const char* nume1, const char* nume2);
    int verECID_B(const char* op, const char* nume1, const char* nume2);
    int verECB_B(const char* op, const char* nume1, const char* nume2);
    int verECID_NR(const char* op, const char* nume1, const char* nume2);
    int verECNR_ID(const char* op, const char* nume1, const char* nume2);
    int verECNR_NR(const char* op, const char* nume1, const char* nume2);

    ///////////////////////////////PT ECUATII ARITMETICE//////////////////////////////////////////////////////////////////////////////////////


    int calculExpS_S(const char* op,const char* name, const char* nume1, const char* nume2);
    int calculExpS_S(const char* op,const char* name, const char* id, const char* nume1, const char* nume2);
    int calculExpID_ID(const char* op, const char* name, const char* nume1, const char* nume2);
    int calculExpID_ID(const char *op, const char *name, const char *id, const char *nume1, const char *nume2);
    int calculExpID_NR(const char* op, const char* name, const char* nume1, const char* nume2);
    int calculExpID_NR(const char* op, const char* name, const char* id, const char* nume1, const char* nume2);
    int calculExpNR_NR(const char* op, const char* name, const char* nume1, const char* nume2);
    int calculExpNR_NR(const char* op, const char* name, const char* id, const char* nume1, const char* nume2);
    int calculExpNR_ID(const char* op, const char* name, const char* nume1, const char* nume2);
    int calculExpNR_ID(const char* op, const char* name, const char* id, const char* nume1, const char* nume2);

    ///////////////////////////////ASSIGN//////////////////////////////////////////////////////////////////////////////////////

    int assignNumber(const char* name, const char* valoare);
    int assignNumber(const char *name, const char *id, const char *valoare);
    int assignID(const char * nume1, const char* nume2);
    int assignID(const char* nume1, const char* id, const char* nume2);
    int assignString(const char * name, const char * str);
    int assignString(const char *name, const char *id, const char *str);
    int assignStringAr(const char *name, const char *str);
    int assignStringAr(const char *name, const char *id, const char *str);
    int assignBool(const char* name, const char* statement);
    int assignBool(const char *name, const char *id, const char *statement);

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    const char* TypeOf(const char* name);
    const char* TypeOf(const char *name, const char* id);
    const char* Valoare(const char* name);
    const char* Valoare(const char *name, const char *id);
    const char* Declarare(const char* name);
    const char* Declarare(const char *name, const char *id);
    void subVar();
    int printVars();
    ~IdList();
};

class FunctionList
{
    vector<FunctionInfo> function;
    class IdList ids;
    
    public: 
    string decl;

   ///////////////////////////////ADAUGARE//////////////////////////////////////////////////////////////////////////////////////

    void addFunction(const char* type, const char* name);
    void addVar(const char* type, const char* name ); 
    void addVar(const char *type, const char *name, const char *index);
    void SetDecl(const char* nume, string name);

    ///////////////////////////////VERIFICARE EXISTENTA//////////////////////////////////////////////////////////////////////////////////////

    bool existsFunction(const char* name);
    bool existsVar(const char* name);
    bool existsVar(const char *name, const char* id);
    //int VerConst(const char* name);
    //int VerConst(const char* name, const char* id);

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    const char* TypeOf(const char* name);
    const char* TypeOf(const char *name, const char* id);
    const char* Valoare(const char* name);
    const char* Valoare(const char *name, const char *id);
    const char* GetAllTypes(const char* name);

    //void subVar();
    int printVars();

    ~FunctionList();
};
