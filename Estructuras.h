#pragma once
#include <iostream>
#include <string>
#include <stack>
#include <chrono>
#include <sstream>
#include <fstream>

using namespace std;

typedef struct DNODE* PDNODE;

typedef struct DATA* PDATA;


struct DATA
{
    string sNombre;
    string sApellido;
    string sFNac;
    double sSalario;
};

struct DNODE {
    PDATA sData;
    int sFrec;
    PDNODE sPrev;
    PDNODE sNext;
};

enum class ECampos { nombre, apellido, fnac, salario }; //Para que nuestro codigo sea nemotécnico Los nombres son numeros ordenado, por default empieza en cero


typedef struct TNODE* PTNODE;

struct TNODE
{
    PDATA sData;
    PTNODE sLft;
    PTNODE sRgt;
    int sFrec;
};

enum class Orden
{
    asc,
    desc,
    sinorden
};


enum class tipo_Arbol
{
    Normal, //Acepta meter palabras repetidas y cada nodo tiene frecuencia = 1
    Frecuencia, //Acepta meter palabras repetidas, pero porque aumenta la frecuencia.
    NoRepeticiones //No acepta meter palabras repetidas, por tanto no hay nodos con mismo valor y frecuencia = 1
};



class Arbol
{
protected:
    PTNODE aRoot;
    tipo_Arbol aTipo_Arbol;
    ECampos aType;

public:
    Arbol(ECampos pType, tipo_Arbol pTipo_Arbol = tipo_Arbol::Normal);
    ~Arbol(void);

    void cleanr(PTNODE pSub = NULL);
    void clean();

    void pushr(PDATA pData, PTNODE pSub = NULL); //Recursivo
    void push(PDATA pData); //No recursivo

    void delr(PDATA pData);



    //Entrega un void y recibe un string
    //void runGet(void(*pFunc)(string));

    void reprr(Orden pOrd = Orden::asc, PTNODE pSub = NULL); //Recursivo
    void repr(Orden pOrd = Orden::asc); // No recursivo

    //void read(string pPath);
    void write(string pPath, Orden pOrd = Orden::sinorden);




private:
    int comp(PDATA pA, PDATA pB); //Si el primero es menor al segundo entrego -1, si son iguales entrego 0 y si el primero es mayor al segundo entrego +1
    PTNODE min(PTNODE pSub);
    PTNODE pdelr(PTNODE pSub, PDATA pData);

    PTNODE getNewNode(PDATA pData);

};





class DList
{
protected:
    PDNODE aHead;
    PDNODE aTail;
    PDNODE aCurr;
    bool aFrec;

    Arbol* aINom;
    Arbol* aIApe;
    Arbol* aIFNa;
    Arbol* aISal;



public:
    DList(tipo_Arbol pTipo_Arboles = tipo_Arbol::Normal, bool pFrec = false);
    ~DList(void);

    void clean(void);

    //void push_front(string pNombre);
    void push_back(string pNombre, string pApellido, string pFNac, double pSalario);
    //void push(string pNombre);

    //PDNODE top_front(void);
    //PDNODE top_back(void);
    PDATA get(ECampos pCampo, bool pRev = false);

    void pop_front(bool lDeleteIndexes = false);
    void pop_back(bool lDeleteIndexes = false);
    void del(string pNombre, string pApellido, string pFNac, double pSalario);

    bool isEmpty(void);
    void repr(ECampos pCampo, bool pRev = false);
    void read(string pPath, char pMethod = 'b');
    void write(string pPath, bool pRev = false);

private:
    
    PDNODE find(string pNombre, string pApellido, string pFNac, double pSalario);
    PDNODE search(string pNombre);
    PDNODE getNewNode(string pNombre, string pApellido, string pFNac, double pSalario);
};



