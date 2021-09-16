/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   FuncAux.cpp
 * Author: jhenn
 * Codigo: 20182841
 * Created on 16 de septiembre de 2021, 12:20 PM
 */

#include "FuncAux.h"
#include <iostream>        
#include <iomanip>
#include <fstream>
using namespace std;
#define MAX 200

void abrirarchivo(fstream &arch, const char *nombre, int tipo) {
    if (tipo == 1) {// lectura texto
        arch.open(nombre, ios::in);
        if (!arch) {
            cout << "Error, al abrir el archivo " << nombre << endl;
            exit(1);
        }
    }
    if (tipo == 2) {// escritura texto
        arch.open(nombre, ios::out);
        if (!arch) {
            cout << "Error, al abrir el archivo " << nombre << endl;
            exit(1);
        }
    }
    if (tipo == 3) {// escritura binario0
        arch.open(nombre, ios::out | ios::binary);
        if (!arch) {
            cout << "Error, al abrir el archivo " << nombre << endl;
            exit(1);
        }
    }
    if (tipo == 4) {// lectura escritura archivo binario
        arch.open(nombre, ios::in | ios::out | ios::binary);
        if (!arch) {
            cout << "Error, al abrir el archivo " << nombre << endl;
            exit(1);
        }
        arch.seekg(0);
    }
}

void muestraAlumBin() {
    fstream archBin;
    abrirarchivo(archBin,"Alumnos.bin",4); //leer archivo

    char tipo, nombre[MAX], especialidad[MAX], facultad[4];
    int codigo, carne;

    int numReg, tamArch, tamReg = sizeof(int)*2 + sizeof(char)*(5 + MAX + MAX);
    archBin.seekg(0, ios::end);
    tamArch = archBin.tellg();
    archBin.seekg(0, ios::beg);

    numReg = tamArch / tamReg;

    for (int i = 0; i < numReg; i++) {
        archBin.read(reinterpret_cast<char*> (&codigo), sizeof(int));
        archBin.read(reinterpret_cast<char*> (nombre), sizeof(char)*MAX);
        archBin.read(reinterpret_cast<char*> (&tipo), sizeof(char));
        archBin.read(reinterpret_cast<char*> (&carne), sizeof(int));
        archBin.read(reinterpret_cast<char*> (facultad), sizeof(char)*4);
        archBin.read(reinterpret_cast<char*> (especialidad), sizeof(char)*MAX);
        //solo imprimo codigo y facultad
        cout << left << setw(20) << codigo << setw(50)<<nombre<<facultad << endl;
    }
    
    cout<<endl;
    archBin.close();
}

void generarBinAlumnos() {

    fstream archAlum, archBin;
    abrirarchivo(archAlum, "Alumnos.txt", 1);
    abrirarchivo(archBin, "Alumnos.bin", 3);


    char tipo, nombre[MAX], especialidad[MAX], facultad[4];
    int codigo, carne;

    while (1) {
        archAlum>>tipo;
        if (archAlum.eof()) break;
        archAlum >> codigo >> nombre>>carne;
        if (archAlum.fail()) {
            archAlum.clear();
            carne = 0;
        }
        archAlum >> especialidad>>facultad;

        archBin.write(reinterpret_cast<const char*> (&codigo), sizeof (int));
        archBin.write(reinterpret_cast<const char*> (nombre), sizeof (char)*MAX);
        archBin.write(reinterpret_cast<const char*> (&tipo), sizeof (char));
        archBin.write(reinterpret_cast<const char*> (&carne), sizeof (int));
        archBin.write(reinterpret_cast<const char*> (facultad), sizeof (char)*4);
        archBin.write(reinterpret_cast<const char*> (especialidad), sizeof (char)*MAX);
        
        cout << left << setw(20) << codigo << setw(50)<<nombre<<facultad << endl;
    }
    cout<<endl;
    muestraAlumBin();
}

void muestraConsolidado() {

    fstream archCons;
    abrirarchivo(archCons,"Consolidado.bin", 4); //leer

    int codigo,sumaNota, cantMater, estado;
    char nombre[MAX], facultad[4];
    double credCur, credApr;
    
    int numReg, tamArch, tamReg = sizeof(int)*4 + sizeof(char)*(4+ MAX) + sizeof(double)*2;
    archCons.seekg(0, ios::end);
    tamArch = archCons.tellg();
    archCons.seekg(0, ios::beg);

    numReg = tamArch/tamReg;
    
    cout<<endl;
    
    for(int i=0; i<numReg; i++){
        archCons.read(reinterpret_cast< char*> (&codigo), sizeof(int));
        archCons.read(reinterpret_cast< char*> (nombre), sizeof(char)*MAX);
        archCons.read(reinterpret_cast< char*> (&credCur), sizeof(double));
        archCons.read(reinterpret_cast< char*> (&credApr), sizeof(double));
        archCons.read(reinterpret_cast< char*> (&sumaNota), sizeof(int));
        archCons.read(reinterpret_cast< char*> (&cantMater), sizeof(int));
        archCons.read(reinterpret_cast< char*> (facultad), sizeof(char)*4);
        archCons.read(reinterpret_cast< char*> (&estado), sizeof(int));
        
        cout<<left<<setw(20)<<codigo<<setw(50)<<nombre<<estado<<endl;
    }

}

void generarConsolidado() {
    fstream archAlum, archCons;
    abrirarchivo(archAlum, "Alumnos.bin", 4); //leemos binario
    abrirarchivo(archCons, "Consolidado.bin", 3);

    char tipo, nombre[MAX], especialidad[MAX], facultad[4];
    int codigo, carne, sumaNota = 0, cantMater = 0, estado = 0;
    double credCur = 0, credApr = 0;

    int numReg, tamArch, tamReg = sizeof(int)*2 + sizeof(char)*(MAX + MAX + 5);
    archAlum.seekg(0, ios::end);
    tamArch = archAlum.tellg();
    
    numReg = tamArch/tamReg;
    
    for (int i = 0; i < numReg; i++) {
        
        archAlum.seekg(i*tamReg, ios::beg);
        
        archAlum.read(reinterpret_cast<char*> (&codigo), sizeof(int));
        archAlum.read(reinterpret_cast<char*> (nombre), sizeof(char)*MAX);
        archAlum.read(reinterpret_cast<char*> (&tipo), sizeof(char));
        archAlum.read(reinterpret_cast<char*> (&carne), sizeof(int));
        archAlum.read(reinterpret_cast<char*> (facultad), sizeof(char)*4);
        archAlum.read(reinterpret_cast<char*> (especialidad), sizeof(char)*MAX);
        
        
   
        archCons.write(reinterpret_cast<const char*>(&codigo), sizeof(int));
        archCons.write(reinterpret_cast<const char*>(nombre), sizeof(char)*MAX);
        archCons.write(reinterpret_cast<const char*>(&credCur), sizeof(double));
        archCons.write(reinterpret_cast<const char*>(&credApr), sizeof(double));
        archCons.write(reinterpret_cast<const char*>(&sumaNota), sizeof(int));
        archCons.write(reinterpret_cast<const char*>(&cantMater), sizeof(int));
        archCons.write(reinterpret_cast<const char*>(facultad), sizeof(char)*4);
        archCons.write(reinterpret_cast<const char*>(&estado), sizeof(int));
        
        cout << left << setw(20) << codigo << setw(50)<<nombre<<facultad << endl;

    }

    muestraConsolidado();

}

