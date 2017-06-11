/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include <stdio.h>
#include <math.h>


/* 
 * File:   main.cpp
 * Author: Leonardo M. Silva
 * Código 1097148
 * 
 * Created on 23 de Outubro de 2016, 22:50
 */

#define NUM_REGRAS 9    //número de regras do sistema
#define NUM_INPUTS 2    //número de inputs do sistema
#define NUM_MF_INPUTS 3 //número de funções de pertinência de cada input
#define NUM_MF_OUTPUT 5 //número de funções de pertinencia do output


//define a estrutura de uma função de pertinência triangular
//pontos A, B e C
typedef struct mf_s{
    
    char* nome; 
    double pontoA;
    double pontoB;
    double pontoC;
    
    double pertinencia = 0;
};

//define estrutura de uma regra
//se a_t e b_t, então c_t
typedef struct rule_s{
    
    mf_s* a_t;
    mf_s* b_t;
    mf_s* c_t;
};

//define estrutura de um input
//possui um nome e uma lista de funções de pertinência
typedef struct input_s{
    
    char* nome;
    mf_s mfs_input[NUM_MF_INPUTS];
};

//define estrutura de um input
//possui um nome e uma lista de funções de pertinência
typedef struct output_s{
    
    char* nome;
    mf_s mfs_output[NUM_MF_OUTPUT];
};


input_s inputs[NUM_INPUTS];     //lista de inputs do sistema
output_s output;                //lista de outputs do sistema
rule_s listaRegras[NUM_REGRAS]; //lista de regras do sistema

//função para inicializar funções de pertinência
void criarMFs();     

//função para inicializar regras
void criarRegras();

//função de fuzzificação, avaliando a pertinência de cada função, dado um input
void fuzzificar(double a, double b);

//função que avalia as regras e calcula a pertinência do output para cada regra
void avaliar_regras();

//função para calcular a agregação de regras, considerando o MAX
double agregar_regras(mf_s* mf, double c);

//função para defuzzificar
void defuzzificar();

double min(double a, double b);
double max(double a, double b);
double triangular(double input, mf_s mf);
double centroide();


int main(int argc, char** argv) {

   double input1, input2;
   double output;
   
   criarMFs();
   
   criarRegras();
   
   fuzzificar(10, 30);
   
   avaliar_regras();
   
   defuzzificar();
   
   return 0;
}

void criarMFs(){
    
    inputs[0].nome = "GrauSujeira";
    inputs[1].nome = "Manchas";
    output.nome = "TempoLavagem";
    
    inputs[0].mfs_input[0].nome = "PS";
    inputs[0].mfs_input[0].pontoA = 0;
    inputs[0].mfs_input[0].pontoB = 0;
    inputs[0].mfs_input[0].pontoC = 50;
    
    inputs[0].mfs_input[1].nome = "MS";
    inputs[0].mfs_input[1].pontoA = 0;
    inputs[0].mfs_input[1].pontoB = 50;
    inputs[0].mfs_input[1].pontoC = 100;
    
    inputs[0].mfs_input[2].nome = "GS";
    inputs[0].mfs_input[2].pontoA = 50;
    inputs[0].mfs_input[2].pontoB = 100;
    inputs[0].mfs_input[2].pontoC = 100;
    
    inputs[1].mfs_input[0].nome = "SM";
    inputs[1].mfs_input[0].pontoA = 0;
    inputs[1].mfs_input[0].pontoB = 0;
    inputs[1].mfs_input[0].pontoC = 50;
    
    inputs[1].mfs_input[1].nome = "MM";
    inputs[1].mfs_input[1].pontoA = 0;
    inputs[1].mfs_input[1].pontoB = 50;
    inputs[1].mfs_input[1].pontoC = 100;
    
    inputs[1].mfs_input[2].nome = "GM";
    inputs[1].mfs_input[2].pontoA = 50;
    inputs[1].mfs_input[2].pontoB = 100;
    inputs[1].mfs_input[2].pontoC = 100;
    
    output.mfs_output[0].nome = "MC";
    output.mfs_output[0].pontoA = 0;
    output.mfs_output[0].pontoB = 0;
    output.mfs_output[0].pontoC = 10;
    
    output.mfs_output[1].nome = "C";
    output.mfs_output[1].pontoA = 0;
    output.mfs_output[1].pontoB = 10;
    output.mfs_output[1].pontoC = 25;
    
    output.mfs_output[2].nome = "M";
    output.mfs_output[2].pontoA = 10;
    output.mfs_output[2].pontoB = 25;
    output.mfs_output[2].pontoC = 40;
    
    output.mfs_output[3].nome = "L";
    output.mfs_output[3].pontoA = 25;
    output.mfs_output[3].pontoB = 40;
    output.mfs_output[3].pontoC = 60;
    
    output.mfs_output[4].nome = "ML";
    output.mfs_output[4].pontoA = 40;
    output.mfs_output[4].pontoB = 60;
    output.mfs_output[4].pontoC = 60;
    
       
}

void criarRegras(){
    
    listaRegras[0].a_t = &inputs[0].mfs_input[0];
    listaRegras[0].b_t = &inputs[1].mfs_input[0];
    listaRegras[0].c_t = &output.mfs_output[0];
    
    listaRegras[1].a_t = &inputs[0].mfs_input[0];
    listaRegras[1].b_t = &inputs[1].mfs_input[1];
    listaRegras[1].c_t = &output.mfs_output[2];
    
    listaRegras[2].a_t = &inputs[0].mfs_input[0];
    listaRegras[2].b_t = &inputs[1].mfs_input[2];
    listaRegras[2].c_t = &output.mfs_output[3];
    
    listaRegras[3].a_t = &inputs[0].mfs_input[1];
    listaRegras[3].b_t = &inputs[1].mfs_input[0];
    listaRegras[3].c_t = &output.mfs_output[1];
    
    listaRegras[4].a_t = &inputs[0].mfs_input[1];
    listaRegras[4].b_t = &inputs[1].mfs_input[1];
    listaRegras[4].c_t = &output.mfs_output[2];
    
    listaRegras[5].a_t = &inputs[0].mfs_input[1];
    listaRegras[5].b_t = &inputs[1].mfs_input[2];
    listaRegras[5].c_t = &output.mfs_output[3];
    
    listaRegras[6].a_t = &inputs[0].mfs_input[2];
    listaRegras[6].b_t = &inputs[1].mfs_input[0];
    listaRegras[6].c_t = &output.mfs_output[2];
    
    listaRegras[7].a_t = &inputs[0].mfs_input[2];
    listaRegras[7].b_t = &inputs[1].mfs_input[1];
    listaRegras[7].c_t = &output.mfs_output[3];
    
    listaRegras[8].a_t = &inputs[0].mfs_input[2];
    listaRegras[8].b_t = &inputs[1].mfs_input[2];
    listaRegras[8].c_t = &output.mfs_output[4];
 
}

void fuzzificar(double input1, double input2){
    
    for(int j = 0; j<NUM_MF_INPUTS; j++){
            
        inputs[0].mfs_input[j].pertinencia = 
                triangular(input1, inputs[0].mfs_input[j]);

    }
    
    for(int j = 0; j<NUM_MF_INPUTS; j++){
            
        inputs[1].mfs_input[j].pertinencia = 
                triangular(input2, inputs[1].mfs_input[j]);

    }
      
}

double triangular(double input, mf_s mf){
    
    double a = mf.pontoA;
    double b = mf.pontoB;
    double c = mf.pontoC;
    
    double resultado;
    
    if(input <= a){
        resultado = 0;
    }
    if((input > a) && (input <= b)){
        
        resultado = (input-a)/(b-a);
    }
    if((input > b) && (input <= c)){
        
        resultado = (c - input)/(c - b);
    }
    if(input > c){
        resultado = 0;
    }
    
    return resultado;
    
}

void avaliar_regras(){
    
    double a;
    double b;
    double c;
    
    for(int i = 0; i<NUM_REGRAS; i++){
        
        a = listaRegras[i].a_t->pertinencia;
        b = listaRegras[i].b_t->pertinencia;
       
        //agregação de antecedentes
        c = min(a,b); //nivel de ativação da regra
        
        //falta implementar semantica da regra
        //f(c, c_t);
        
        listaRegras[i].c_t->pertinencia = agregar_regras(listaRegras[i].c_t, c);
        
    }
    
}

double agregar_regras(mf_s* mf, double c){
    
    double pertinencia_atual = mf->pertinencia;
    double pertinencia_nova = c;
    double resultado;
    
    resultado = max(pertinencia_atual, pertinencia_nova);
    
    return resultado;
}


void defuzzificar(){
    
    double resultado, acc;
    
    
    
}

double min(double a, double b){
    
    if(a<b){
        return a;
    }
    else{
        return b;
    }
}

double max(double a, double b){
    
    if(a<b){
        return b;
    }
    else{
        return a;
    }
}

double centroide(){
    
    
}

