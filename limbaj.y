%{
#include <iostream>
#include <vector>
#include <string>
#include <cstring>
#include "IdList.h"
extern FILE* yyin;
extern char* yytext;
extern int yylineno;
extern int yylex();
void yyerror(const char * s);
class IdList ids;
class FunctionList fcs;
%}
%union {
     char* string;
     class ParamList* ptrParamList;
     class ASTNode* ast_p; 
}
%token  BGIN END BGIN_G BGIN_C BGIN_F ASSIGN TYPEOF EVAL Data Methods
%token<string> ID NR ARRAY CHAR BOOL CONST OP_AR OP_B TYPE CLASA IF FOR WHILE
%type<ast_p> e j exprs
%type<string> IDS nrs
%start progr
%%
progr: classes global functions block {printf("Programul e corect!\n");}
     | classes functions block {printf("Programul e corect!\n");}
     | classes global block {printf("Programul e corect!\n");}
     | classes block {printf("Programul e corect!\n");}
     | global functions block {printf("Programul e corect!\n");}
     | functions block {printf("Programul e corect!\n");}
     | global block {printf("Programul e corect!\n");}
     | global {printf("Programul e corect!\n");}
     ;

classes : BGIN_C clasa;

clasa: cls ';'
       | clasa cls ';'
       ;

cls:       CLASA ID { if(!ids.existsClass($2))
                                                  {ids.addClass($2);} 
                                                  else {yyerror("Clasa declarata de doua ori\n");exit(EXIT_FAILURE);}}
          |CLASA ID { if(!ids.existsClass($2))
                                             { ids.addClass($2); ids.tipul=string($2); ids.tipul_f=string($2);}
                                                  else {yyerror("Clasa declarata de doua ori\n");exit(EXIT_FAILURE);}
                                             } '{' continut_clasa '}'
          ;
functions: BGIN_F {ids.tipul="global"; ids.tipul_f="global";} function;

function: functii | function functii;

functii:  functie '(' list_param ')' ';'          
          | functie '(' ')' ';'
	     | functie '(' ')' '{' '}'
          | functie '(' ')' '{' declarations_f '}'';'
          | functie '(' list_param ')' '{' declarations_f '}'';'
          | functie '(' list_param ')' '{' '}'';'
          | ID '('')'';'{ if(strcmp($1, ids.tipul_f.c_str())!=0) {yyerror("Constructorul nu poate fi creat.\n");exit(EXIT_FAILURE);}}
	  ;
functie: TYPE ID {if(!fcs.existsFunction($2)){ fcs.addFunction($1,$2);  ids.tipul=string($2); fcs.SetDecl($2,ids.tipul_f);} else {yyerror("Functia declarata de doua ori\n");exit(EXIT_FAILURE);}}
;

global: BGIN_G {ids.tipul="global";} declarations;
continut_clasa: Data declarations_c Methods function | Data declarations_c | Methods function ;
declarations :  decl ';'          
	      |  declarations decl ';'   
	      ;

declarations_c :  decl_c ';'    
	      |  declarations_c decl_c ';' 
	      ;

declarations_f :  decl_f ';'     
	      |  declarations_f decl_f ';' 
	      ;
decl_f:     TYPE ID   {if(!ids.existsVar($2)) ids.addVar($1,$2);
                         else {yyerror("Variabila declarata de doua ori\n");exit(EXIT_FAILURE);}
                    }
          | CONST TYPE ID{   if(!ids.existsVar($3)) {ids.addVar($1,$2);ids.AlocConst($1);}
                         else {yyerror("Variabila declarata de doua ori\n");exit(EXIT_FAILURE);}
                         }
          |TYPE ID ',' ID {   if(!ids.existsVar($2)) ids.addVar($1,$2); 
                              else {yyerror("Variabila declarata de doua ori\n");exit(EXIT_FAILURE);}
                              if(!ids.existsVar($4))ids.addVar($1,$4);
                              else {yyerror("Variabila declarata de doua ori\n");exit(EXIT_FAILURE);}
                         }
          |CONST TYPE ID ',' ID {   
                              if(!ids.existsVar($3)){ids.addVar($2,$3); ids.AlocConst($3);} 
                              else {yyerror("Variabila declarata de doua ori\n");exit(EXIT_FAILURE);}
                              if(!ids.existsVar($5)){ids.addVar($2,$5); ids.AlocConst($5);} 
                              else {yyerror("Variabila declarata de doua ori\n");exit(EXIT_FAILURE);}
                         }
          | TYPE ID ARRAY { if(!ids.existsVar($2, $3)) ids.addVar($1,$2, $3); 
                     else {yyerror("Variabila declarata de doua ori\n");exit(EXIT_FAILURE);}}
          | CONST TYPE ID ARRAY { if(!ids.existsVar($3, $4)) {ids.addVar($2,$3, $4); ids.AlocConst($3,$4);}
                         else {yyerror("Variabila declarata de doua ori\n");exit(EXIT_FAILURE);}
                    }
           ;

decl_c:    decl
           ;

decl:     TYPE ID   {if(!ids.existsVar($2)) 
                         {ids.addVar($1,$2);} 
                         else {yyerror("Variabila declarata de doua ori\n");exit(EXIT_FAILURE);}
                    }
          | CONST TYPE ID{   if(!ids.existsVar($3)) 
                         {ids.addVar($1,$2); ids.AlocConst($1);} 
                         else {yyerror("Variabila declarata de doua ori\n");exit(EXIT_FAILURE);}
                         }
          |TYPE ID ',' ID {   if(!ids.existsVar($2)){ids.addVar($1,$2);} 
                              else {yyerror("Variabila declarata de doua ori\n");exit(EXIT_FAILURE);}
                              if(!ids.existsVar($4)){ids.addVar($1,$4);} 
                              else {yyerror("Variabila declarata de doua ori\n");exit(EXIT_FAILURE);}
                         }
          |CONST TYPE ID ',' ID {   
                              if(!ids.existsVar($3)){ids.addVar($2,$3); ids.AlocConst($3);} 
                              else {yyerror("Variabila declarata de doua ori\n");exit(EXIT_FAILURE);}
                              if(!ids.existsVar($5)){ids.addVar($2,$5); ids.AlocConst($5);} 
                              else {yyerror("Variabila declarata de doua ori\n");exit(EXIT_FAILURE);}
                         }
          | TYPE ID ARRAY { if(!ids.existsVar($2, $3)) {
                          ids.addVar($1,$2, $3);
                     } else {yyerror("Variabila declarata de doua ori\n");exit(EXIT_FAILURE);}
                    }
          | CONST TYPE ID ARRAY { if(!ids.existsVar($3, $4)) 
                         {
                          ids.addVar($2,$3, $4); ids.AlocConst($3,$4);
                     } else {yyerror("Variabila declarata de doua ori\n");exit(EXIT_FAILURE);}
                    }
	  | ID ID {if(ids.existsClass($1)) {
			if(!ids.existsVar($2))
			{
				ids.addVar($1,$2);
			} else { yyerror("Variabila declarata de doua ori\n");exit(EXIT_FAILURE); }
			}else { yyerror("Nu exista clasa\n");exit(EXIT_FAILURE); }
			}
           ;

list_param : param
            | list_param ','  param 
            ;
            
param : TYPE ID { if(!fcs.existsVar($2)) fcs.addVar($1,$2); else {yyerror("Variabila declarata de doua ori\n");exit(EXIT_FAILURE);}}
     | TYPE ID ARRAY { if(!fcs.existsVar($2,$3)) fcs.addVar($1,$2,$3); else {yyerror("Variabila declarata de doua ori\n");exit(EXIT_FAILURE);}}
      ; 
      
block : BGIN list END  
     ;  

list :  statement ';' 
     | list statement ';'
     ;

statement: ID ASSIGN e {
                              if(ids.existsVar($1) && (ids.VerConst($1)!=1)) 
                              { if($3->type=="int" || $3->type =="float")
                              {if(ids.assignNumber($1, $3->value.c_str())) {yyerror("error type of left side not the same with the type of the right side\n"); exit(EXIT_FAILURE);
                              }
                              else if(ids.VerConst($1)==-1) ids.AlocConst($1);} 
                              else if($3->type=="bool") {if(ids.assignBool($1, $3->value.c_str())==1){yyerror("error type of left side not the same with the type of the right side\n"); exit(EXIT_FAILURE);}}
                              else if($3->type=="char" || $3->type =="string") {if(ids.assignStringAr($1, $3->value.c_str())==1){yyerror("error type of left side not the same with the type of the right side\n"); exit(EXIT_FAILURE);}}}
                              else {yyerror("Variabila nu exista/nu poate fi modificata\n"); exit(EXIT_FAILURE);}
				     }

          |ID ARRAY ASSIGN e{
                              if(ids.existsVar($1, $2) && ids.VerConst($1,$2)!=1) 
                              { 
                                   if($4->type=="int" || $4->type =="float")
                                   {if(ids.assignNumber($1, $2, $4->value.c_str())) {yyerror("left side not the same with the type of the right side\n"); exit(EXIT_FAILURE);}} 

                                   else if($4->type=="string" || $4->type =="char")
                                   {if(ids.assignStringAr($1, $2, $4->value.c_str())) {yyerror("left side not the same with the type of the right side\n"); exit(EXIT_FAILURE);}} 

                                   else if($4->type=="bool")
                                   {
                                        if(ids.assignBool($1, $2, $4->value.c_str())) {yyerror("left side not the same with the type of the right side\n"); exit(EXIT_FAILURE);}
                                   } 
                                   if(ids.VerConst($1, $2)==-1) ids.AlocConst($1,$2);
                              }   
                              else {yyerror("Variabila nu exista/nu poate fi modificata\n"); exit(EXIT_FAILURE);}
				     }
          | operatii
          | EVAL '(' e ')' {cout<<"Eval: "<<$3->value<<endl;}
          | TYPEOF '(' e ')' {cout<<"TypeOf: "<<$3->type<<endl;}
          | IF '(' e ')' {if($3->value!="true") cout<<"Regula din if nu este indeplinita."<<endl; else cout<<"Regula din if este indeplinita."<<endl;} '{' list '}'
          | WHILE '(' e ')' {if($3->value!="true") cout<<"Regula din while nu este indeplinita."<<endl; else cout<<"Regula din while este indeplinita."<<endl;} '{' list '}'
          | FOR '('statement ';' e ';' statement')' '{' list '}'
	  | ID '(' nrs ')'{if(fcs.existsFunction($1)) { if(strcmp($3,fcs.GetAllTypes($1))!=0) {yyerror("Illegal call parameters\n");exit(EXIT_FAILURE);} } else {yyerror("Functia nu exista\n");exit(EXIT_FAILURE);} }
          |ID'.'ID ASSIGN e {if(ids.existsClass(ids.Declarare($1))){yyerror("Clasa nu exista\n"); exit(EXIT_FAILURE);}
                              if(strcmp(ids.Declarare($3),ids.TypeOf($1))!=0) {yyerror("Variabila nu face parte din clasa\n"); exit(EXIT_FAILURE);}                        
                              if(ids.existsVar($3) && (ids.VerConst($3)!=1)) 
                              { if($5->type=="int" || $5->type =="float")
                              {if(ids.assignNumber($3, $5->value.c_str())) {yyerror("error type of left side not the same with the type of the right side\n"); exit(EXIT_FAILURE);}
                              else if(ids.VerConst($3)==-1) ids.AlocConst($3);} 
                              else if($5->type=="bool") {if(ids.assignBool($3, $5->value.c_str())==1){yyerror("Tipul nu este bun\n"); exit(EXIT_FAILURE);}}
                              else if($5->type=="char" || $5->type =="string") {if(ids.assignStringAr($3, $5->value.c_str())==1){yyerror("Tipul nu este bun\n"); exit(EXIT_FAILURE);}}}
                              else {yyerror("Variabila nu exista/nu poate fi modificata\n"); exit(EXIT_FAILURE);}
				     }
          |ID'.'ID ARRAY ASSIGN e{
                              if(ids.existsClass(ids.Declarare($1))){yyerror("Clasa nu exista\n"); exit(EXIT_FAILURE);}
                              if(strcmp(ids.Declarare($3, $4),ids.TypeOf($1))!=0) {yyerror("Variabila nu face parte din clasa\n"); exit(EXIT_FAILURE);}  
                              if(ids.existsVar($3, $4) && ids.VerConst($3,$4)!=1) 
                              { 
                                   if($6->type=="int" || $6->type =="float")
                                   {if(ids.assignNumber($3, $4, $6->value.c_str())) {yyerror("left side not the same with the type of the right side\n"); exit(EXIT_FAILURE);}} 

                                   else if($6->type=="string" || $6->type =="char")
                                   {if(ids.assignStringAr($3, $4, $6->value.c_str())) {yyerror("left side not the same with the type of the right side\n"); exit(EXIT_FAILURE);}} 

                                   else if($6->type=="bool")
                                   {
                                        if(ids.assignBool($3, $4, $6->value.c_str())) {yyerror("left side not the same with the type of the right side\n"); exit(EXIT_FAILURE);}
                                   } 
                                   if(ids.VerConst($3, $4)==-1) ids.AlocConst($3,$4);
                              }   
                              else {yyerror("Variabila nu exista/nu poate fi modificata\n"); exit(EXIT_FAILURE);}
				     }
         ;

exprs: j
     | exprs ',' j
     ;

nrs: IDS 
   | nrs ',' IDS {strcat($$,$3);}
   ;

IDS: ID {if(ids.existsVar($1)) { if(strcmp(ids.TypeOf($1),"string")==0) {$$=strdup("string");} else if(strcmp(ids.TypeOf($1),"char")==0) {$$=strdup("char");} else {$$=strdup("int");}} else {yyerror("Variabila nu exista\n");exit(EXIT_FAILURE);} }
   | NR {$$=strdup("int");}
   ;

e: e OP_AR j{ if(($1->type=="string"||$1->type=="char")||($3->type=="string"||$3->type=="char")) {yyerror("String/char types cannot be added\n");exit(EXIT_FAILURE);}
		if($1->type=="bool"||$3->type=="bool") {yyerror("Bool type cannot be added\n");exit(EXIT_FAILURE);}
		if($1->type==$3->type) $$= $$->new_ast_root($2, $1, $3); 
               else {yyerror("type error, all operands on the right side should have the same type\n"); exit(EXIT_FAILURE);}}
  |e OP_B j{ if(($1->type=="string"||$1->type=="char")||($3->type=="string"||$3->type=="char")) {yyerror("String/char types cannot be added\n");exit(EXIT_FAILURE);}
		if($1->type==$3->type) $$= $$->new_ast_root($2, $1, $3); 
               else {yyerror("type error, all operands on the right side should have the same type\n"); exit(EXIT_FAILURE);}}
  | j { $$=$$->new_ast_node($1);}
  ;

j    :ID{ if(ids.existsVar($1)) { $$= $$->new_ast_node(ids.TypeOf($1), ids.Valoare($1));} else { yyerror("Variabila nu exista\n"); exit(EXIT_FAILURE);}}
     | ID ARRAY{if(ids.existsVar($1, $2)) { $$= $$->new_ast_node(ids.TypeOf($1,$2), ids.Valoare($1,$2));}else { yyerror("Variabila nu exista\n"); exit(EXIT_FAILURE);}}
     | NR {if(strchr($1, '.')==NULL) $$= $$->new_ast_node("int", $1); else $$= $$->new_ast_node("float", $1);}
     | CHAR {string i= string($1).substr(1,strlen($1)-2); if(strlen($1)>1) $$= $$->new_ast_node("string", i.c_str()); else $$= $$->new_ast_node("char", i.c_str());}
     | BOOL{ $$= $$->new_ast_node("bool", $1);}
     | '!' BOOL { $$= $$->new_ast_node("bool", $2); $$= $$->new_ast_node(string("!").c_str(), $$); }
     | '!' ID { if(ids.existsVar($2)){ $$= $$->new_ast_node(ids.TypeOf($2), ids.Valoare($2)); $$= $$->new_ast_node(string("!").c_str(), $$);} else { yyerror("Variabila nu exista\n"); exit(EXIT_FAILURE);}}
     | ID '(' ')' { if(fcs.existsFunction($1)) { $$= $$->new_ast_node(fcs.TypeOf($1),"0");} else { yyerror("Functia nu exista\n"); exit(EXIT_FAILURE);}}
     | ID '(' exprs ')' { if(fcs.existsFunction($1)) { $$= $$->new_ast_node(fcs.TypeOf($1),"0");} else { yyerror("Functia nu exista\n"); exit(EXIT_FAILURE);}}
     ;

operatii: ID OP_B ID {
                         if(ids.existsVar($1) && ids.existsVar($3)) 
                         {
                              if(ids.verECID_ID($2,$1,$3)==-1) {yyerror("Variabila nu respecta tipul\n"); exit(EXIT_FAILURE);}
                              else if(ids.verECID_ID($2,$1,$3)==1) cout<<"Ecuatia: "<<$1<<$2<<$3<<" este falsa."<< endl;
                              else cout<<"Ecuatia: "<<$1<<$2<<$3<<" este adevarata."<< endl;
                         }
                         else {yyerror("Variabila nu exista"); exit(EXIT_FAILURE);}
                    }
          |ID OP_B ID ARRAY{
                         if(ids.existsVar($1) && ids.existsVar($3,$4)) 
                         {
                              ids.addVar(ids.TypeOf($3,$4), "TEMP"); 
                              if(ids.assignNumber("TEMP", ids.Valoare($3,$4))) {yyerror("Variabila nu respecta tipul\n"); exit(EXIT_FAILURE);}
                              if(ids.verECID_ID($2,$1,"TEMP")==-1) {yyerror("Variabila nu respecta tipul\n"); exit(EXIT_FAILURE);}
                              else if(ids.verECID_ID($2,$1,"TEMP")==1) cout<<"Ecuatia: "<<$1<<$2<<$3<<$4<<" este falsa."<< endl;
                              else cout<<"Ecuatia: "<<$1<<$2<<$3<<$4<<" este adevarata."<< endl;
                              ids.subVar();
                         }
                         else {yyerror("Variabila nu exista\n"); exit(EXIT_FAILURE);}
                    }
          |ID ARRAY OP_B ID {
                         if(ids.existsVar($1,$2) && ids.existsVar($4)) 
                         {
                              ids.addVar(ids.TypeOf($1,$2), "TEMP"); 
                              if(ids.assignNumber("TEMP", ids.Valoare($1,$2))) {yyerror("Variabila nu respecta tipul\n"); exit(EXIT_FAILURE);}                              
                              if(ids.verECID_ID($3,"TEMP",$4)==-1) {yyerror("Variabila nu respecta tipul\n"); exit(EXIT_FAILURE);}
                              else if(ids.verECID_ID($3,"TEMP",$4)==1) cout<<"Ecuatia: "<<$1<<$2<<$3<<$4<<" este falsa."<< endl;
                              else cout<<"Ecuatia: "<<$1<<$2<<$3<<$4<<" este adevarata."<< endl;
                              ids.subVar();
                         }
                         else {yyerror("Variabila nu exista\n"); exit(EXIT_FAILURE);}
                    }
          |ID ARRAY OP_B ID ARRAY {
                         if(ids.existsVar($1,$2) && ids.existsVar($4,$5)) 
                         {
                              ids.addVar(ids.TypeOf($1,$2), "TEMP1"); if(ids.assignNumber("TEMP1", ids.Valoare($1,$2))) {yyerror("Variabila nu respecta tipul\n"); exit(EXIT_FAILURE);} 
                              ids.addVar(ids.TypeOf($4,$5), "TEMP2"); if(ids.assignNumber("TEMP2", ids.Valoare($4,$5))) {yyerror("Variabila nu respecta tipul\n"); exit(EXIT_FAILURE);}
                              if(ids.verECID_ID($3,"TEMP1","TEMP2")==-1) {yyerror("Variabila nu respecta tipul\n"); exit(EXIT_FAILURE);}
                              else if(ids.verECID_ID($3,"TEMP1","TEMP2")==1) cout<<"Ecuatia: "<<$1<<$2<<$3<<$4<<$5<<" este falsa."<< endl;
                              else cout<<"Ecuatia: "<<$1<<$2<<$3<<$4<<$5<<" este adevarata."<< endl;
                              ids.subVar(); ids.subVar();
                         }
                         else {yyerror("Variabila nu exista\n"); exit(EXIT_FAILURE);}
                    }         
          | ID OP_B NR {
                         if(ids.existsVar($1)) 
                         {
                              if(ids.verECID_NR($2,$1,$3)==-1) {yyerror("Variabila nu respecta tipul\n"); exit(EXIT_FAILURE);}
                              else if(ids.verECID_NR($2,$1,$3)==1) cout<<"Ecuatia: "<<$1<<$2<<$3<<" este falsa."<< endl;
                              else cout<<"Ecuatia: "<<$1<<$2<<$3<<" este adevarata."<< endl;
                         }
                         else {yyerror("Variabila nu exista\n"); exit(EXIT_FAILURE);}
                    }
          | ID ARRAY OP_B NR {
                         if(ids.existsVar($1, $2)) 
                         {
                              ids.addVar(ids.TypeOf($1,$2), "TEMP"); 
                              if(ids.assignNumber("TEMP", ids.Valoare($1,$2))) {yyerror("Variabila nu respecta tipul\n"); exit(EXIT_FAILURE);}
                              if(ids.verECID_NR($3,"TEMP",$4)==-1) {yyerror("Variabila nu respecta tipul\n"); exit(EXIT_FAILURE);}
                              else if(ids.verECID_NR($3,"TEMP",$4)==1) cout<<"Ecuatia: "<<$1<<$2<<$3<<$4<<" este falsa."<< endl;
                              else cout<<"Ecuatia: "<<$1<<$2<<$3<<$4<<" este adevarata."<< endl;
                              ids.subVar();
                         }
                         else {yyerror("Variabila nu exista\n"); exit(EXIT_FAILURE);}
                    }
          | NR OP_B ID 
                    {
                         if(ids.existsVar($3)) 
                         {
                              if(ids.verECNR_ID($2,$1,$3)==-1) {yyerror("Variabila nu respecta tipul\n"); exit(EXIT_FAILURE);}
                              else if(ids.verECNR_ID($2,$1,$3)==1) cout<<"Ecuatia: "<<$1<<$2<<$3<<" este falsa."<< endl;
                              else cout<<"Ecuatia: "<<$1<<$2<<$3<<" este adevarata."<< endl;
                         }
                         else {yyerror("Variabila nu exista\n"); exit(EXIT_FAILURE);}
                    }
          | NR OP_B ID ARRAY
                    {
                         if(ids.existsVar($3,$4)) 
                         {
                              ids.addVar(ids.TypeOf($3,$4), "TEMP"); 
                              if(ids.assignNumber("TEMP", ids.Valoare($3,$4))) {yyerror("Variabila nu respecta tipul\n"); exit(EXIT_FAILURE);}
                              if(ids.verECNR_ID($2,$1, "TEMP")==-1) {yyerror("Variabila nu respecta tipul\n"); exit(EXIT_FAILURE);}
                              else if(ids.verECNR_ID($2,$1,"TEMP")==1) cout<<"Ecuatia: "<<$1<<$2<<$3<<$4<<" este falsa."<< endl;
                              else cout<<"Ecuatia: "<<$1<<$2<<$3<<$4<<" este adevarata."<< endl;
                              ids.subVar();
                         }
                         else {yyerror("Variabila nu exista\n"); exit(EXIT_FAILURE);}
                    }
          | NR OP_B NR
                    {
                              if(ids.verECNR_NR($2,$1,$3)==-1) {yyerror("Variabila nu respecta tipul\n"); exit(EXIT_FAILURE);}
                              else if(ids.verECNR_NR($2,$1,$3)==1) cout<<"Ecuatia: "<<$1<<$2<<$3<<" este falsa."<< endl;
                              else cout<<"Ecuatia: "<<$1<<$2<<$3<<" este adevarata."<< endl;
                    }
          | ID OP_B BOOL {
                         if(ids.existsVar($1)) 
                         {
                              if(ids.verECID_B($2,$1,$3)==-1) {yyerror("Variabila nu este bool\n"); exit(EXIT_FAILURE);}
                              else if(ids.verECID_B($2,$1,$3)==1) cout<<"Ecuatia: "<<$1<<$2<<$3<<" este falsa."<< endl;
                              else cout<<"Ecuatia: "<<$1<<$2<<$3<<" este adevarata."<< endl;
                         }
                         else {yyerror("Variabila nu exista\n"); exit(EXIT_FAILURE);}
                    }
          | BOOL OP_B ID {
                         if(ids.existsVar($1)) 
                         {
                              if(ids.verECID_B($2,$3,$1)==-1) {yyerror("Variabila nu este bool\n"); exit(EXIT_FAILURE);}
                              else if(ids.verECID_B($2,$3,$1)==1) cout<<"Ecuatia: "<<$1<<$2<<$3<<" este falsa."<< endl;
                              else cout<<"Ecuatia: "<<$1<<$2<<$3<<" este adevarata."<< endl;
                         }
                         else {yyerror("Variabila nu exista\n"); exit(EXIT_FAILURE);}
                    }
          | ID ARRAY OP_B BOOL {
                         if(ids.existsVar($1, $2)) 
                         {
                              ids.addVar(ids.TypeOf($1,$2), "TEMP"); 
                              if(ids.assignBool("TEMP", ids.Valoare($1,$2))) {yyerror("Variabila nu este de tip Bool.\n"); exit(EXIT_FAILURE);}
                              if(ids.verECID_B($3,"TEMP",$4)==-1) {yyerror("Variabila nu este de tip bool.\n"); exit(EXIT_FAILURE);}
                              else if(ids.verECID_B($3,"TEMP",$4)==1) cout<<"Ecuatia: "<<$1<<$2<<$3<<$4<<" este falsa."<< endl;
                              else cout<<"Ecuatia: "<<$1<<$2<<$3<<$4<<" este adevarata."<< endl;
                              ids.subVar();
                         }
                         else {yyerror("Variabila nu exista\n"); exit(EXIT_FAILURE);}
                    }
          | BOOL OP_B ID ARRAY
                    {
                         if(ids.existsVar($3,$4)) 
                         {
                              ids.addVar(ids.TypeOf($3,$4), "TEMP"); 
                              if(ids.assignBool("TEMP", ids.Valoare($3,$4))) {yyerror("Variabila nu respecta tipul\n"); exit(EXIT_FAILURE);}
                              if(ids.verECID_B($2,"TEMP", $1)==-1) {yyerror("Variabila nu respecta tipul\n"); exit(EXIT_FAILURE);}
                              else if(ids.verECID_B($2,"TEMP", $1)==1) cout<<"Ecuatia: "<<$1<<$2<<$3<<$4<<" este falsa."<< endl;
                              else cout<<"Ecuatia: "<<$1<<$2<<$3<<$4<<" este adevarata."<< endl;
                              ids.subVar();
                         }
                         else {yyerror("Variabila nu exista\n"); exit(EXIT_FAILURE);}
                    }
          | BOOL OP_B BOOL
                    {
                              if(ids.verECB_B($2,$1,$3)==-1) {yyerror("Nu poate fi facuta aceasta operatie pentro bool\n"); exit(EXIT_FAILURE);}
                              else if(ids.verECB_B($2,$1,$3)==1) cout<<"Ecuatia: "<<$1<<$2<<$3<<" este falsa."<< endl;
                              else cout<<"Ecuatia: "<<$1<<$2<<$3<<" este adevarata."<< endl;
                    }
         ;

%%
void yyerror(const char * s){
printf("Eroare: %s la linia:%d\n",s,yylineno);
}

int main(int argc, char** argv){
     yyin=fopen(argv[1],"r");
     yyparse();
     //cout << "Variabile:" <<endl;
     ids.printVars();
     fcs.printVars();
    
} 
