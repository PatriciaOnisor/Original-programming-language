#include "IdList.h"
#include <iostream>
#include <string.h>
#include<cstring>
#include <fstream>
using namespace std;
ofstream output("output.txt");

///////////////////////////////////////////////IDList/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void IdList::addVar(const char* type, const char*name) 
{
    IdInfo var = {string(type), string(name)};
    var.constant=0;
    var.decl=tipul;
    vars.push_back(var);
}

void IdList::addClass(const char *name)
{
    ClassInfo cls = {string(name)};
    clasa.push_back(cls);
}


void IdList::subVar()
{
    vars.pop_back();
}

void IdList::addVar(const char *type, const char *name, const char *index)
{
    string j= string(index).substr(1,strlen(index)-2);
    for(int i=0; i<stoi(j);i++)
    {
        ArrayInfo arr;
        arr.type = string(type);
        arr.name = string(name);
        arr.size = stoi(j);
        arr.index = i;
        arr.constant=0;
        arr.decl=tipul;
        array.push_back(arr);
    }
}

int IdList::VerConst(const char *name)
{
    string strvar = string(name);
     for (const IdInfo& v : vars) 
     {
        if (strvar == v.name) 
        { 
            if(v.constant==-1)
                return -1;
            if(v.constant==1)
                return 1;
        }
    }
    return 0;
}

int IdList::VerConst(const char *name, const char *id)
{
     string strvar = string(name);
     string i=string(id).substr(1,strlen(id)-2);
     for (const ArrayInfo& a : array) 
     {
        if (strvar == a.name && a.index==stoi(i)) 
        { 
            if(a.constant==-1)
                return -1;
            if(a.constant==1)
                return 1;
        }
    }
    return 0;
}

void IdList::AlocConst(const char *name)
{
    string strvar = string(name);
     for (IdInfo& v : vars) {
        if (strvar == v.name && v.constant==-1) 
        { 
            v.constant=1;
        }
        else if (strvar == v.name && v.constant==0) 
        { 
            v.constant=-1;
        }
    }
}

void IdList::AlocConst(const char *name, const char *id)
{
    
    string i=string(id).substr(1,strlen(id)-2);
    string strvar = string(name);
     for (ArrayInfo& a : array) 
     {
        for(int j=0; j<=stoi(i); j++)
        { 
            if (strvar == a.name && a.size==stoi(i) && a.index==j) 
            { 
                if(a.constant==0) a.constant=-1; 
            }
            else if (strvar == a.name && a.index==stoi(i) && a.index==j) 
            { 
                if(a.constant==-1) a.constant=1; 
            }
        }
        
    }
    
}

bool IdList::existsVar(const char *var)
{
    string strvar = string(var);
     for (const IdInfo& v : vars) {
        if (strvar == v.name) { 
            return true;
        }
    }
    return false;
}

bool IdList::existsClass(const char *name)
{
    string strvar = string(name);
    for (const ClassInfo& v : clasa) 
    {
        if (strvar == v.name) 
        { 
            return true;
        }
    }
    return false;
}


bool IdList::existsVar(const char *name, const char* id)
{
    string i= string(id).substr(1,strlen(id)-2);
    string strvar = string(name);
     for (const ArrayInfo& a : array) {
        if (strvar == a.name) 
        {
            if(stoi(i)==a.index) 
            { 
                return true;
            }
        }
        
    }
    return false;
}

int IdList::printVars() 
{
    if (!output.is_open()) 
    {
        cout << "Nu am putut deschide fisierul." << endl;
        return 1; 
    }
    output<<"Variabile: "<<endl<<endl;
    for (const IdInfo& v : vars) 
    {
        if(strcmp(v.decl.c_str(),"global")==0) output<<"Variabila declarata gloabal. ";
        else output<<"Variabila declarata in "<<v.decl<<". ";
        output << "name: " << v.name << ", type: " << v.type<< ", value: "<<v.value << endl<<endl; 
    }
     for (const ArrayInfo& a : array) 
     {
        if(!a.value.empty())
        {
             if(strcmp(a.decl.c_str(),"global")==0) output<<"Variabila declarata gloabal.";
            else output<<"Variabila declarata in "<<a.decl<<".";
            output << "name: " << a.name <<"["<< a.index<< "] "<< ", type: " << a.type<<", value:"<<a.value << endl<<endl;
        }
     }
     //output.close();
     return 0;
}

int IdList::assignNumber(const char *name, const char *valoare)
{
     string strvar = string(name);
     for (IdInfo& v : vars) 
	 {
        if (strvar == v.name)
		{ 
			if(v.type=="int")
			{
                if(strchr(valoare, '.')==NULL)
                {
                    v.value=string(valoare);   
				    return 0; 
                }
			}
            if(v.type=="float")
			{
				v.value=string(valoare);   
				return 0;
			}
        }
    }
	return 1;
}

int IdList::assignNumber(const char *name, const char *id, const char *valoare)
{
    string strvar = string(name);
    const string i=string(id).substr(1,strlen(id)-2);
    
     for (ArrayInfo& a : array) 
	 {
        if (strvar == a.name && stoi(i)==a.index)
		{ 
			if(a.type=="int")
			{
				a.value=string(valoare);   
				return 0;
			}
            if(a.type=="float")
			{
				a.value=string(valoare);   
				return 0;
			}
        }
    }
	return 1;
}

int IdList::assignID(const char *nume1, const char *nume2)
{
    string strvar1 = string(nume1);
    string strvar2 = string(nume2);
    for (IdInfo& v1 : vars) 
    {
       if (strvar1 == v1.name) 
       { 
           for (IdInfo& v2 : vars) 
            {
                if (strvar2 == v2.name) 
                { 
                    if(v1.type == v2.type)
                    {
                        v1.value = v2.value;
                        return 0;
                    }
                }
            }
       }
    }
    
    return 1;
}

int IdList::assignID(const char* nume1, const char* id, const char* nume2)
{
    string strvar1 = string(nume1);
    string strvar2 = string(nume2);
    string i=string(id).substr(1,strlen(id)-2);
    for (ArrayInfo& a1 : array) 
    {
       if (strvar1 == a1.name && stoi(i)==a1.index) 
       { 
           for (IdInfo& v2 : vars) 
            {
                if (strvar2 == v2.name) 
                { 
                    if(a1.type == v2.type)
                    {
                        a1.value = v2.value;
                        
                        return 0;
                    }
                }
            }
       }
    }
    
    return 1;
}

int IdList::assignString(const char *name, const char *str)
{
    string sir=string(str).substr(1,strlen(str)-2);
    string strvar = string(name);
    for (IdInfo& v : vars) 
    {
       if (strvar == v.name) 
       {
           if(v.type=="string")
           {
               v.value=string(str).substr(1,strlen(str)-2);
               return 0;
           }
           else if(v.type=="char")
           {
                if(strlen(sir.c_str())==1)
                {
                    v.value=string(str).substr(1,strlen(str)-2);
                    return 0;
                } 
           }
       }
    }
    return 1;
}

int IdList::assignString(const char *name, const char *id, const char *str)
{
    string strvar = string(name);
    string sir=string(str).substr(1,strlen(str)-2);
    string i= string(id).substr(1,strlen(id)-2);
    for (ArrayInfo& a : array) 
    {
       if (strvar == a.name) 
       {
           if(strcmp(TypeOf(name, id),"string")==0)
           {
                if(a.index==stoi(i))
                {
                    a.value=string(str).substr(1,strlen(str)-2);
                    return 0;
                }
           }
           else if(strcmp(TypeOf(name, id),"char")==0) 
           {
                if(strlen(sir.c_str())==1)
                {   
                    if(a.index==stoi(i))
                    {
                        a.value=string(str).substr(1,strlen(str)-2);
                        return 0;
                    }
                }
           }
       }
    }
    return 1;
}

int IdList::assignStringAr(const char *name, const char *id, const char *str)
{
    string strvar = string(name);
    string i= string(id).substr(1,strlen(id)-2);
    for (ArrayInfo& a : array) 
    {
       if (strvar == a.name) 
       {
           if(strcmp(TypeOf(name, id),"char")==0) 
           {
                if(strlen(str)==1)
                {
                    if(a.index==stoi(i))
                    {
                        a.value=string(str);
                        return 0;
                    }
                }
           }
           else if(strcmp(TypeOf(name, id),"string")==0)
           {
                if(a.index==stoi(i))
                {
                    a.value=string(str);
                    return 0;
                }
           }
       }
    }
    return 1;
}

int IdList::assignStringAr(const char *name, const char * str)
{
    string strvar = string(name);
    for (IdInfo& v : vars) 
    {
       if (strvar == v.name) 
       {
           if(strcmp(TypeOf(name),"char")==0) 
           {
                if(strlen(str)==1)
                {
                    v.value=string(str);
                    return 0; 
                }
           }
           else if(strcmp(TypeOf(name),"string")==0)
            {
                v.value=string(str);
                return 0;

           }
       }
    }
    return 1;
}

int IdList::assignBool(const char *name, const char *statement)
{
    string strvar = string(name);
    for (IdInfo& v : vars) 
    {
       if (strvar == v.name) 
       {
           if(v.type=="bool")
           {
                if(strcmp(statement, "true")==0)
                {
                    v.value="true";
                    return 0;
                }
                else if(strcmp(statement, "false")==0)
                {
                    v.value="false";
                    return 0;
                }
           }
       }
    }
    return 1;
}

int IdList::assignBool(const char *name, const char *id, const char *statement)
{
    string strvar = string(name);
    string i= string(id).substr(1,strlen(id)-2);
    for(ArrayInfo& a : array )
    {
        if(strvar == a.name)
        {
            if(strcmp(TypeOf(name, id),"bool")==0)
            {
                if(a.index==stof(i))
                {
                    if(strcmp(statement, "true")==0)
                    {
                        a.value="true";
                        return 0;
                    }
                    else if(strcmp(statement, "false")==0)
                    {
                        a.value="false";
                        return 0;
                    }
                } 
            }
        }
    }
    return 1;
}

const char* IdList::TypeOf(const char *name)
{
    string strvar = string(name);
     for (IdInfo& v : vars) 
     {
        if (strvar == v.name) 
        {
            return v.type.c_str();
        }
    }
        return "Variabila nu exista";
}

const char *IdList::TypeOf(const char *name, const char *id)
{
    string strvar = string(name);
     for (ArrayInfo& a : array) 
     {
        string i=string(id).substr(1,strlen(id)-2);
        if (strvar == a.name) 
        {
            if(stoi(i)==a.index)
                return a.type.c_str();
        }
    }
        return "Variabila nu exista";
}

const char *IdList::Valoare(const char *name)
{
    string strvar = string(name);
    const char * valoare;
    for(IdInfo& v :  vars)
    {
        if(strvar == v.name)
        {
            valoare=v.value.c_str();
        }
    }
    return valoare;
}

const char *IdList::Valoare(const char *name, const char *id)
{
    string strvar = string(name);
    const char * valoare;
    string i= string(id).substr(1,strlen(id)-2);
    for(ArrayInfo& a : array )
    {
        if(strvar == a.name)
        {
            if(a.index==stof(i))
            {
                valoare=a.value.c_str();
            } 
        }
    }
    return valoare;
}

const char *IdList::Declarare(const char *name)
{
    string strvar = string(name);
    const char * declarare;
    for(IdInfo& a : vars )
    {
        if(strvar == a.name)
        {
            declarare=a.decl.c_str();
        }
    }
    return declarare;
}

const char *IdList::Declarare(const char *name, const char *id)
{
    string strvar = string(name);
    const char * declarare;
    string i= string(id).substr(1,strlen(id)-2);
    for(ArrayInfo& a : array )
    {
        if(strvar == a.name)
        {
            if(a.index==stof(i))
            {
                declarare=a.decl.c_str();
            } 
        }
    }
    return declarare;
}

int IdList::calculExpID_ID(const char *op, const char *name, const char *nume1, const char *nume2)
{
    float rezultat_f;
    int rezultat_i;
    string rezultat_s;
    char buf[10];
    string tip;
    string strvar1 = string(nume1);
    string strvar2 = string(nume2);
    char* rezultatString = new char[20];  // Alocare suficientă pentru a stoca rezultatul (20 de caractere pentru rezultate mai mari)
    for (IdInfo& v1 : vars) 
     {
        if (strvar1 == v1.name) 
        {
            for (IdInfo& v2 : vars) 
            {
                if (strvar2 == v2.name) 
                {
                    if(v1.type == v2.type)
                    {
                        if(v1.type=="int" || v1.type=="float")
                        {
                            if(strncmp(op, "+", strlen("+"))==0) {rezultat_f = stof(v1.value) + stof(v2.value); rezultat_i = stoi(v1.value) + stof(v2.value);}
                            if(strncmp(op, "-", strlen("+"))==0) {rezultat_f = stof(v1.value) - stof(v2.value); rezultat_i = stoi(v1.value) - stof(v2.value);}
                            if(strncmp(op, "*", strlen("+"))==0) {rezultat_f = stof(v1.value) * stof(v2.value); rezultat_i = stoi(v1.value) * stof(v2.value);}
                            if(strncmp(op, "/", strlen("+"))==0) {rezultat_f = stof(v1.value) / stof(v2.value); rezultat_i = stoi(v1.value) / stof(v2.value);}  
                        }
                        else if(v1.type=="string")
                        {
                            if(strncmp(op, "+", strlen("+"))==0) {rezultat_s = v1.value + v2.value;}
                        }
                        else return 1;
                    }
                    tip=v1.type;
                }
            } 
        }
    }
    string strvar = string(name);
    for (IdInfo& v : vars) 
    {
       if (strvar == v.name) 
       {
           if(v.type==tip)
           { 
                if(v.type=="float")
                {
                    sprintf(rezultatString, "%f", rezultat_f);
                    v.value=rezultatString;
                }
                else if(v.type=="int")
                {
                    sprintf(rezultatString, "%d", rezultat_i);
                    v.value=rezultatString;
                }
                else if(v.type=="string")
                {
                    assignStringAr(v.value.c_str(), rezultat_s.c_str());
                }
               return 0;
           }
       }
    }
    return 1;
}

int IdList::calculExpID_ID(const char *op, const char *name, const char *id, const char *nume1, const char *nume2)
{
    float rezultat_f;
    int rezultat_i;
    string i=string(id).substr(1,strlen(id)-2);
    string rezultat_s;
    char buf[10];
    string tip;
    string strvar1 = string(nume1);
    string strvar2 = string(nume2);
    char* rezultatString = new char[20];  // Alocare suficientă pentru a stoca rezultatul (20 de caractere pentru rezultate mai mari)
    for (IdInfo& v1 : vars) 
     {
        if (strvar1 == v1.name) 
        {
            for (IdInfo& v2 : vars) 
            {
                if (strvar2 == v2.name) 
                {
                    if(v1.type == v2.type)
                    {
                        if(v1.type=="int" || v1.type=="float")
                        {
                            if(strncmp(op, "+", strlen("+"))==0) {rezultat_f = stof(v1.value) + stof(v2.value); rezultat_i = stoi(v1.value) + stof(v2.value);}
                            if(strncmp(op, "-", strlen("+"))==0) {rezultat_f = stof(v1.value) - stof(v2.value); rezultat_i = stoi(v1.value) - stof(v2.value);}
                            if(strncmp(op, "*", strlen("+"))==0) {rezultat_f = stof(v1.value) * stof(v2.value); rezultat_i = stoi(v1.value) * stof(v2.value);}
                            if(strncmp(op, "/", strlen("+"))==0) {rezultat_f = stof(v1.value) / stof(v2.value); rezultat_i = stoi(v1.value) / stof(v2.value);}  
                        }
                        else if(v1.type=="string")
                        {
                            //v1.value = v1.value.substr(1, v1.value.length() - 2);
                            //v2.value = v2.value.substr(1, v2.value.length() - 2);
                            if(strncmp(op, "+", strlen("+"))==0) {rezultat_s = v1.value + v2.value;}
                        }
                    }
                    tip=v1.type;
                }
            } 
        }
    }
    string strvar = string(name);
    for (ArrayInfo& a : array) 
    {
       if (strvar == a.name && stoi(i)==a.index) 
       {
           if(a.type==tip)
           {
                if(a.type=="float")
                {
                    sprintf(rezultatString, "%f", rezultat_f);
                    a.value=rezultatString;
                }
                else if(a.type=="int")
                {
                    sprintf(rezultatString, "%d", rezultat_i);
                    a.value=rezultatString;
                }
                else if(a.type=="string")
                {
                    assignStringAr(a.value.c_str(), rezultat_s.c_str());
                }
               return 0;
           }
       }
    }
    return 1;
}

int IdList::calculExpNR_ID(const char *op, const char *name, const char *nume1, const char *nume2)
{
    float rezultat_f;
    int rezultat_i;
    string rezultat_s;
    string tip;
    string buf;
    string strvar1 = string(nume2);
    char* rezultatString = new char[20];  // Alocare suficientă pentru a stoca rezultatul (20 de caractere pentru rezultate mai mari)
    for (IdInfo& v1 : vars) 
     {
        if (strvar1 == v1.name) 
        {
            if(v1.type=="int" || v1.type=="float")
            {
                if(strncmp(op, "+", strlen("+"))==0) {rezultat_f = stof(nume1) + stof(v1.value) ; rezultat_i = stof(nume1) + stoi(v1.value) ;}
                if(strncmp(op, "-", strlen("+"))==0) {rezultat_f = stof(nume1) - stof(v1.value) ; rezultat_i = stof(nume1) - stoi(v1.value) ;}
                if(strncmp(op, "*", strlen("+"))==0) {rezultat_f = stof(nume1) * stof(v1.value) ; rezultat_i = stof(nume1) * stoi(v1.value) ;}
                if(strncmp(op, "/", strlen("+"))==0) {rezultat_f = stof(nume1) / stof(v1.value) ; rezultat_i = stof(nume1) / stoi(v1.value) ;}
            }
             else if(v1.type=="string")
            {
                buf = string(nume1).substr(1, string(nume1).length() - 2);
                if(strncmp(op, "+", strlen("+"))==0) {rezultat_s = buf + v1.value;}
            }

            tip=v1.type;
        }
    }
    string strvar = string(name);
    for (IdInfo& v : vars) 
    {
       if (strvar == v.name) 
       {
           if(v.type==tip)
           {
                if(v.type=="float")
                {
                    sprintf(rezultatString, "%f", rezultat_f);
                    v.value=rezultatString;
                }
                else if(v.type=="int")
                {
                    sprintf(rezultatString, "%d", rezultat_i);
                    v.value=rezultatString;
                }
                  else if(v.type=="string")
                {
                    assignStringAr(v.value.c_str(), rezultat_s.c_str());
                }
               return 0;
           }
       }
    }
    return 1;
}

int IdList::calculExpNR_ID(const char *op, const char *name, const char *id, const char *nume1, const char *nume2)
{
    float rezultat_f;
    int rezultat_i;
    string rezultat_s;
    string i=string(id).substr(1,strlen(id)-2);
    string tip;
    string buf;
    string strvar1 = string(nume2);
    char* rezultatString = new char[20];  // Alocare suficientă pentru a stoca rezultatul (20 de caractere pentru rezultate mai mari)
    for (IdInfo& v1 : vars) 
     {
        if (strvar1 == v1.name) 
        {
            if(v1.type=="int" || v1.type=="float")
             {
                if(strncmp(op, "+", strlen("+"))==0) {rezultat_f = stof(nume1) + stof(v1.value) ; rezultat_i = stof(nume1) + stoi(v1.value) ;}
                if(strncmp(op, "-", strlen("+"))==0) {rezultat_f = stof(nume1) - stof(v1.value) ; rezultat_i = stof(nume1) - stoi(v1.value) ;}
                if(strncmp(op, "*", strlen("+"))==0) {rezultat_f = stof(nume1) * stof(v1.value) ; rezultat_i = stof(nume1) * stoi(v1.value) ;}
                if(strncmp(op, "/", strlen("+"))==0) {rezultat_f = stof(nume1) / stof(v1.value) ; rezultat_i = stof(nume1) / stoi(v1.value) ;}
            }
             else if(v1.type=="string")
            {
                buf = string(nume1).substr(1, string(nume1).length() - 2);
                if(strncmp(op, "+", strlen("+"))==0) {rezultat_s = buf + v1.value;}
            }

            tip=v1.type;
        }
    }
    string strvar = string(name);
    for (ArrayInfo& v : array) 
    {
       if (strvar == v.name && v.index==stoi(i)) 
       {
           if(v.type==tip)
           {
                if(v.type=="float")
                {
                    sprintf(rezultatString, "%f", rezultat_f);
                    v.value=rezultatString;
                }
                else if(v.type=="int")
                {
                    sprintf(rezultatString, "%d", rezultat_i);
                    v.value=rezultatString;
                }
                  else if(v.type=="string")
                {
                    assignStringAr(v.value.c_str(), rezultat_s.c_str());
                }
               return 0;
           }
       }
    }
    return 1;
}

int IdList::calculExpID_NR(const char *op, const char *name, const char *nume1, const char *nume2)
{
    float rezultat_f;
    int rezultat_i;
    string rezultat_s;
    string tip;
    string buf;
    string strvar1 = string(nume1);
    char* rezultatString = new char[20];  // Alocare suficientă pentru a stoca rezultatul (20 de caractere pentru rezultate mai mari)
    for (IdInfo& v1 : vars) 
     {
        if (strvar1 == v1.name) 
        {
            if(v1.type=="int" || v1.type=="float")
            {
                if(strncmp(op, "+", strlen("+"))==0) {rezultat_f = stof(v1.value) + stof(nume2); rezultat_i = stoi(v1.value) + stof(nume2);}
                if(strncmp(op, "-", strlen("+"))==0) {rezultat_f = stof(v1.value) - stof(nume2); rezultat_i = stoi(v1.value) - stof(nume2);}
                if(strncmp(op, "*", strlen("+"))==0) {rezultat_f = stof(v1.value) * stof(nume2); rezultat_i = stoi(v1.value) * stof(nume2);}
                if(strncmp(op, "/", strlen("+"))==0) {rezultat_f = stof(v1.value) / stof(nume2); rezultat_i = stoi(v1.value) / stof(nume2);}
            }
            else if(v1.type=="string")
            {
                buf = string(nume2).substr(1, string(nume2).length() - 2);
                if(strncmp(op, "+", strlen("+"))==0) {rezultat_s = v1.value + buf;}
            }
            tip=v1.type;
        }
    }
    string strvar = string(name);
    for (IdInfo& v : vars) 
    {
       if (strvar == v.name) 
       {
           if(v.type==tip)
           {
                if(v.type=="float ")
                {
                    sprintf(rezultatString, "%f", rezultat_f);
                    v.value=rezultatString;
                }
                else if(v.type=="int")
                {
                    sprintf(rezultatString, "%d", rezultat_i);
                    v.value=rezultatString;
                }
                else if(v.type=="string")
                {
                    assignStringAr(v.value.c_str(), rezultat_s.c_str());
                }
               return 0;
           }
       }
    }
    return 1;
}

int IdList::calculExpID_NR(const char *op, const char *name, const char *id, const char *nume1, const char *nume2)
{
    float rezultat_f;
    int rezultat_i;
    string rezultat_s;
    string tip;
    string buf;
    string i=string(id).substr(1,strlen(id)-2);
    string strvar1 = string(nume1);
    char* rezultatString = new char[20];  // Alocare suficientă pentru a stoca rezultatul (20 de caractere pentru rezultate mai mari)
    for (IdInfo& v1 : vars) 
     {
        if (strvar1 == v1.name) 
        {
            if(v1.type=="int" || v1.type=="float")
            {
                if(strncmp(op, "+", strlen("+"))==0) {rezultat_f = stof(v1.value) + stof(nume2); rezultat_i = stoi(v1.value) + stof(nume2);}
                if(strncmp(op, "-", strlen("+"))==0) {rezultat_f = stof(v1.value) - stof(nume2); rezultat_i = stoi(v1.value) - stof(nume2);}
                if(strncmp(op, "*", strlen("+"))==0) {rezultat_f = stof(v1.value) * stof(nume2); rezultat_i = stoi(v1.value) * stof(nume2);}
                if(strncmp(op, "/", strlen("+"))==0) {rezultat_f = stof(v1.value) / stof(nume2); rezultat_i = stoi(v1.value) / stof(nume2);}
            }
            else if(v1.type=="string")
            {
                buf = string(nume2).substr(1, string(nume2).length() - 2);
                if(strncmp(op, "+", strlen("+"))==0) {rezultat_s = v1.value + buf;}
            }
            tip=v1.type;
        }
    }
    string strvar = string(name);
    for (ArrayInfo& v : array) 
    {
       if (strvar == v.name && stoi(i)==v.index) 
       {
           if(v.type==tip)
           {
                if(v.type=="float ")
                {
                    sprintf(rezultatString, "%f", rezultat_f);
                    v.value=rezultatString;
                }
                else if(v.type=="int")
                {
                    sprintf(rezultatString, "%d", rezultat_i);
                    v.value=rezultatString;
                }
                else if(v.type=="string")
                {
                    assignStringAr(v.value.c_str(), rezultat_s.c_str());
                }
               return 0;
           }
       }
    }
    return 1;
}

int IdList::calculExpNR_NR(const char *op, const char *name, const char *nume1, const char *nume2)
{
    float rezultat_f;
    int rezultat_i;
    char buf[10];
    char* rezultatString = new char[20];  // Alocare suficientă pentru a stoca rezultatul (20 de caractere pentru rezultate mai mari)
    if(strncmp(op, "+", strlen("+"))==0) {rezultat_f = stof(nume2) + stof(nume1); rezultat_i = stoi(nume2) + stof(nume1);}
    if(strncmp(op, "-", strlen("+"))==0) {rezultat_f = stof(nume2) - stof(nume1); rezultat_i = stoi(nume2) - stof(nume1);}
    if(strncmp(op, "*", strlen("+"))==0) {rezultat_f = stof(nume2) * stof(nume1); rezultat_i = stoi(nume2) * stof(nume1);}
    if(strncmp(op, "/", strlen("+"))==0) {rezultat_f = stof(nume2) / stof(nume1); rezultat_i = stoi(nume2) / stof(nume1);}

    string strvar = string(name);
    for (IdInfo& v : vars) 
    {
       if (strvar == v.name) 
       {
                if(v.type=="float")
                {
                    sprintf(rezultatString, "%f", rezultat_f);
                    v.value=rezultatString;
                }
                else if(v.type=="int")
                {
                    sprintf(rezultatString, "%d", rezultat_i);
                    v.value=rezultatString;
                }
               return 0;
       }
    }
    return 1;
}

int IdList::calculExpNR_NR(const char *op, const char *name, const char *id, const char *nume1, const char *nume2)
{
    float rezultat_f;
    int rezultat_i;
    string i=string(id).substr(1,strlen(id)-2);
    char buf[10];
    char* rezultatString = new char[20];  // Alocare suficientă pentru a stoca rezultatul (20 de caractere pentru rezultate mai mari)
    if(strncmp(op, "+", strlen("+"))==0) {rezultat_f = stof(nume2) + stof(nume1); rezultat_i = stoi(nume2) + stof(nume1);}
    if(strncmp(op, "-", strlen("+"))==0) {rezultat_f = stof(nume2) - stof(nume1); rezultat_i = stoi(nume2) - stof(nume1);}
    if(strncmp(op, "*", strlen("+"))==0) {rezultat_f = stof(nume2) * stof(nume1); rezultat_i = stoi(nume2) * stof(nume1);}
    if(strncmp(op, "/", strlen("+"))==0) {rezultat_f = stof(nume2) / stof(nume1); rezultat_i = stoi(nume2) / stof(nume1);}

    string strvar = string(name);
    for (ArrayInfo& v : array) 
    {
       if (strvar == v.name && v.index==stoi(i)) 
       {
                if(v.type=="float")
                {
                    sprintf(rezultatString, "%f", rezultat_f);
                    v.value=rezultatString;
                }
                else if(v.type=="int")
                {
                    sprintf(rezultatString, "%d", rezultat_i);
                    v.value=rezultatString;
                }
               return 0;
       }
    }
    return 1;
}

int IdList::calculExpS_S(const char *op, const char *name, const char *nume1, const char *nume2)
{
    string rezultat_s;
    char* rezultatString = new char[20];  // Alocare suficientă pentru a stoca rezultatul (20 de caractere pentru rezultate mai mari)
    if(strncmp(op, "+", strlen("+"))==0) 
    {
        rezultat_s = string(nume1).substr(1, string(nume1).length() - 2) + string(nume2).substr(1, string(nume2).length() - 2);
    }
    
    string strvar = string(name);
    for (IdInfo& v : vars) 
    {
       if (strvar == v.name) 
       {
                if(v.type=="string"||v.type=="char")
                {
                    v.value=rezultat_s;
                }
               return 0;
       }
    }
    return 1;
}

int IdList::calculExpS_S(const char *op, const char *name, const char *id, const char *nume1, const char *nume2)
{
    string rezultat_s;
    string i=string(id).substr(1,strlen(id)-2);
    char* rezultatString = new char[20];  // Alocare suficientă pentru a stoca rezultatul (20 de caractere pentru rezultate mai mari)
    if(strncmp(op, "+", strlen("+"))==0) 
    {
        rezultat_s = string(nume1).substr(1, string(nume1).length() - 2) + string(nume2).substr(1, string(nume2).length() - 2);
    }
    
    string strvar = string(name);
    for (ArrayInfo& a : array) 
    {
       if (strvar == a.name && stoi(i)==a.index) 
       {
                if(a.type=="string")
                {
                    assignStringAr(a.value.c_str(), rezultat_s.c_str());
                }
               return 0;
       }
    }
    return 1;
}

int IdList::verECID_ID(const char *op, const char *nume1, const char *nume2)
{
    string strvar1 = string(nume1);
    string strvar2 = string(nume2);
    for (IdInfo& v1 : vars) 
     {
        if (strvar1 == v1.name) 
        {
            for (IdInfo& v2 : vars) 
            {
                if (strvar2 == v2.name) 
                {
                    if(v1.type == v2.type)
                    {
                        if(v1.type=="int" || v1.type=="float")
                        {
                            if(strncmp(op, "<=", strlen("<="))==0) {if(stof(v1.value)<=stof(v2.value)) return 0;}
                            else if(strncmp(op, ">=", strlen(">="))==0) {if(stof(v1.value)>=stof(v2.value)) return 0;}
                            else if(strncmp(op, "<", strlen("<"))==0) {if(stof(v1.value)<stof(v2.value)) return 0;}
                            else if(strncmp(op, ">", strlen(">"))==0) {if(stof(v1.value)>stof(v2.value)) return 0;}
                            else if(strncmp(op, "==", strlen("=="))==0) {if(stof(v1.value)==stof(v2.value)) return 0;}
                            else if(strncmp(op, "!=", strlen("!="))==0) {if(stof(v1.value)!=stof(v2.value)) return 0;}
                        }
                        else if(v1.type=="bool")
                        {
                            if(strncmp(op, "==", strlen("=="))==0) {if(v1.value==v2.value) return 0;}
                            else if(strncmp(op, "!=", strlen("!="))==0) {if(v1.value!=v2.value) return 0;}
                            else if(strncmp(op, "||", strlen("||"))==0) {if(v1.value=="false" && v2.value=="false") return 1; else return 0;}
                            else if(strncmp(op, "&&", strlen("&&"))==0) {if(v1.value=="true" && v2.value=="true") return 0; else return 1;}
                        }
                    }
                    else return -1;
                }
            } 
        }
    }
    return 1;
}

int IdList::verECID_B(const char *op, const char *nume1, const char *nume2)
{
    string strvar1 = string(nume1);
    for (IdInfo& v1 : vars) 
     {
        if (strvar1 == v1.name) 
        {
            
            if(v1.type=="bool")
            {
                if(strncmp(op, "==", strlen("=="))==0) {if(v1.value==nume2) return 0;}
                else if(strncmp(op, "!=", strlen("!="))==0) {if(v1.value!=nume2) return 0;}
                else if(strncmp(op, "||", strlen("||"))==0) {if(v1.value=="false" && nume2=="false") return 1; else return 0;}
                else if(strncmp(op, "&&", strlen("&&"))==0) {if(v1.value=="true" && nume2=="true") return 0; else return 1;}
            }
            else return -1;
        }
    }
    return 1;
}

int IdList::verECB_B(const char *op, const char *nume1, const char *nume2)
{
    if(strncmp(op, "==", strlen("=="))==0) {if(nume1==nume2) return 0;}
    else if(strncmp(op, "!=", strlen("!="))==0) {if(nume1!=nume2) return 0;}
    else if(strncmp(op, "||", strlen("||"))==0) {if(nume1=="false" && nume2=="false") return 1; else return 0;}
    else if(strncmp(op, "&&", strlen("&&"))==0) {if(nume1=="true" && nume2=="true") return 0; else return 1;}
    return 1;
}

int IdList::verECID_NR(const char *op, const char *nume1, const char *nume2)
{
    string strvar1 = string(nume1);
    float nr=stof(nume2);
    for (IdInfo& v1 : vars) 
     {
        if (strvar1 == v1.name) 
        {
            if(strncmp(op, "<=", strlen("<="))==0) {if(stof(v1.value)<=nr ) return 0;}
            else if(strncmp(op, ">=", strlen(">="))==0) {if(stof(v1.value)>=nr) return 0;}
            else if(strncmp(op, "<", strlen("<"))==0) {if(stof(v1.value)<nr) return 0;}
            else if(strncmp(op, ">", strlen(">"))==0) {if(stof(v1.value)>nr) return 0;}
            else if(strncmp(op, "==", strlen("=="))==0) {if(stof(v1.value)==nr) return 0;}
            else if(strncmp(op, "!=", strlen("!="))==0) {if(stof(v1.value)!=nr) return 0;}
        }
    }
    return 1;
}

int IdList::verECNR_ID(const char *op, const char *nume1, const char *nume2)
{
    string strvar1 = string(nume2);
    float nr=stof(nume1);
    for (IdInfo& v1 : vars) 
     {
        if (strvar1 == v1.name) 
        {
            if(strncmp(op, "<=", strlen("<="))==0) {if(nr<=stof(v1.value)) return 0;}
            else if(strncmp(op, ">=", strlen(">="))==0) {if(nr>=stof(v1.value)) return 0;}
            else if(strncmp(op, "<", strlen("<"))==0) {if(nr<stof(v1.value)) return 0;}
            else if(strncmp(op, ">", strlen(">"))==0) {if(nr>stof(v1.value)) return 0;}
            else if(strncmp(op, "==", strlen("=="))==0) {if(nr==stof(v1.value)) return 0;}
            else if(strncmp(op, "!=", strlen("!="))==0) {if(nr!=stof(v1.value)) return 0;}
        }
    }
    return 1;
}

int IdList::verECNR_NR(const char *op, const char *nume1, const char *nume2)
{
    float nr1=stof(nume1);
    float nr2=stof(nume2);

    if(strncmp(op, "<=", strlen("<="))==0) {if(nr1<=nr2) return 0;}
    else if(strncmp(op, ">=", strlen(">="))==0) {if(nr1>=nr2) return 0;}
    else if(strncmp(op, "<", strlen("<"))==0) {if(nr1<nr2) return 0;}
    else if(strncmp(op, ">", strlen(">"))==0) {if(nr1>nr2) return 0;}
    else if(strncmp(op, "==", strlen("=="))==0) {if(nr1==nr2) return 0;}
    else if(strncmp(op, "!=", strlen("!="))==0) {if(nr1!=nr2) return 0;}
    
    return 1;
}

IdList::~IdList() 
{
    vars.clear();
    array.clear();
}

///////////////////////////////////////////////FunctionList/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void FunctionList::addFunction(const char *type, const char *name)
{
    FunctionInfo fct;
    fct.name=string(name);
    fct.type=string(type);
    function.push_back(fct);
    decl=string(name);
}

void FunctionList::addVar(const char *type, const char *name)
{
    for(FunctionInfo& fct : function)
        if(fct.name==decl)
        {
            ArrayInfo var = {string(type), string(name)};
            var.constant=0;
            var.decl=decl;
            var.size=-1;
            fct.variabile.push_back(var);
            break;
        }
}

void FunctionList::addVar(const char *type, const char *name, const char *index)
{
    for(FunctionInfo& fct : function)
        if(fct.name==decl)
            {
                string j= string(index).substr(1,strlen(index)-2);
                for(int i=0; i<stoi(j);i++)
                {
                    ArrayInfo arr;
                    arr.type = string(type);
                    arr.name = string(name);
                    arr.size = stoi(j);
                    arr.index = i;
                    arr.constant=0;
                    arr.decl=decl;
                    fct.variabile.push_back(arr);
                }
                function.push_back(fct);
                break;
            }
 
}

bool FunctionList::existsFunction(const char *name)
{
    for(const FunctionInfo& fct : function)
        if(fct.name==string(name))
            {
                return true;
            }
    return false;
}

bool FunctionList::existsVar(const char *name)
{
    for(const FunctionInfo& fct : function)
        if(fct.name==decl)
        {
            for (const ArrayInfo& v : fct.variabile) 
            {
                if (string(name) == v.name) 
                { 
                    return true;
                }
            }
        }
    return false;
}

bool FunctionList::existsVar(const char *name, const char *id)
{
   string i= string(id).substr(1,strlen(id)-2);
    for(const FunctionInfo& fct : function)
        if(fct.name==decl)
        {
            for (const ArrayInfo& a : fct.variabile) 
            {
                if (string(name) == a.name && stoi(i)==a.index) 
                { 
                    return true;
                }
            }
        }
    return false;
}

FunctionList::~FunctionList()
{
    function.clear();
}

int FunctionList::printVars()
{
     if (!output.is_open()) 
    {
        cout << "Nu am putut deschide fisierul." << endl;
        return 1; 
    }
    output<<"Parametri:"<<endl<<endl;
    for(const FunctionInfo& fct: function)
    {
        for(const ArrayInfo& a : fct.variabile)
        {
            output<<"Nume parametru: "<<a.name<<" return type: "<<fct.type<<" type:"<<a.type<<" declarata in "<<a.decl<<endl<<endl;
        }
    }
    output<<"Functii:"<<endl<<endl;
    for(const FunctionInfo& fct: function)
    {
            if(fct.decl=="global") output<<"Functie declarata global. ";
            else output<<"Functie declarata in clasa "<<fct.decl<<". ";
            output<<"Functia: "<<fct.name<<", type: "<<fct.type<<endl<<endl;
    }
     //output.close();
     return 0;
}

const char* FunctionList::TypeOf(const char* name)
{
    for(const FunctionInfo& fct : function)
        if(fct.name==name)
        {
           return fct.type.c_str();
        }
    return "nu exista";
}

const char* FunctionList::GetAllTypes(const char* name) {
	string types;
	for(const FunctionInfo& fct : function) {
		if(fct.name==string(name))
		{
			for(const ArrayInfo& a : fct.variabile) {
				if(a.type==string("float"))
					types = types + string("int");
				else
					types = types + a.type;
			}
		}
	}
	//cout<<"Function types:" << types<<endl;
	return types.c_str();
}

void FunctionList::SetDecl(const char* nume, string name)
{
    for(FunctionInfo& fct : function) {
		if(fct.name==string(nume))
		{
			fct.decl=string(name);
		}
	}
}
