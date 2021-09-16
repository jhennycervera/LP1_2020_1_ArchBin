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
    abrirarchivo(archBin, "Alumnos.bin", 4); //leer archivo

    char tipo, nombre[MAX], especialidad[MAX], facultad[4];
    int codigo, carne;

    int numReg, tamArch, tamReg = sizeof (int)*2 + sizeof (char)*(5 + MAX + MAX);
    archBin.seekg(0, ios::end);
    tamArch = archBin.tellg();
    archBin.seekg(0, ios::beg);

    numReg = tamArch / tamReg;

    for (int i = 0; i < numReg; i++) {
        archBin.read(reinterpret_cast<char*> (&codigo), sizeof (int));
        archBin.read(reinterpret_cast<char*> (nombre), sizeof (char)*MAX);
        archBin.read(reinterpret_cast<char*> (&tipo), sizeof (char));
        archBin.read(reinterpret_cast<char*> (&carne), sizeof (int));
        archBin.read(reinterpret_cast<char*> (facultad), sizeof (char)*4);
        archBin.read(reinterpret_cast<char*> (especialidad), sizeof (char)*MAX);
        //solo imprimo codigo y facultad
        cout << left << setw(20) << codigo << setw(50) << nombre << facultad << endl;
    }

    cout << endl;
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

        cout << left << setw(20) << codigo << setw(50) << nombre << facultad << endl;
    }
    cout << endl;
    archAlum.close();
    archBin.close();
    muestraAlumBin();
}

void muestraConsolidado() {

    fstream archCons;
    abrirarchivo(archCons, "Consolidado.bin", 4); //leer

    int codigo, sumaNota, cantMater, estado;
    char nombre[MAX], facultad[4];
    double credCur, credApr;

    int numReg, tamArch, tamReg = sizeof (int)*4 + sizeof (char)*(4 + MAX) + sizeof (double)*2;
    archCons.seekg(0, ios::end);
    tamArch = archCons.tellg();
    archCons.seekg(0, ios::beg);

    numReg = tamArch / tamReg;

    cout << endl;

    for (int i = 0; i < numReg; i++) {
        archCons.read(reinterpret_cast<char*> (&codigo), sizeof (int));
        archCons.read(reinterpret_cast<char*> (nombre), sizeof (char)*MAX);
        archCons.read(reinterpret_cast<char*> (&credCur), sizeof (double));
        archCons.read(reinterpret_cast<char*> (&credApr), sizeof (double));
        archCons.read(reinterpret_cast<char*> (&sumaNota), sizeof (int));
        archCons.read(reinterpret_cast<char*> (&cantMater), sizeof (int));
        archCons.read(reinterpret_cast<char*> (facultad), sizeof (char)*4);
        archCons.read(reinterpret_cast<char*> (&estado), sizeof (int));

        cout << left << setw(20) << codigo << setw(50) << nombre << estado << endl;
    }
}

void generarConsolidado() {

    fstream archAlum, archCons;
    abrirarchivo(archAlum, "Alumnos.bin", 4); //leemos binario
    abrirarchivo(archCons, "Consolidado.bin", 3);

    char tipo, nombre[MAX], especialidad[MAX], facultad[4];
    int codigo, carne, sumaNota = 0, cantMater = 0, estado = 0;
    double credCur = 0, credApr = 0;

    int numReg, tamArch, tamReg = sizeof (int)*2 + sizeof (char)*(MAX + MAX + 5);
    archAlum.seekg(0, ios::end);
    tamArch = archAlum.tellg();

    numReg = tamArch / tamReg;

    for (int i = 0; i < numReg; i++) {

        archAlum.seekg(i*tamReg, ios::beg);

        archAlum.read(reinterpret_cast<char*> (&codigo), sizeof (int));
        archAlum.read(reinterpret_cast<char*> (nombre), sizeof (char)*MAX);
        archAlum.read(reinterpret_cast<char*> (&tipo), sizeof (char));
        archAlum.read(reinterpret_cast<char*> (&carne), sizeof (int));
        archAlum.read(reinterpret_cast<char*> (facultad), sizeof (char)*4);
        archAlum.read(reinterpret_cast<char*> (especialidad), sizeof (char)*MAX);



        archCons.write(reinterpret_cast<const char*> (&codigo), sizeof (int));
        archCons.write(reinterpret_cast<const char*> (nombre), sizeof (char)*MAX);
        archCons.write(reinterpret_cast<const char*> (&credCur), sizeof (double));
        archCons.write(reinterpret_cast<const char*> (&credApr), sizeof (double));
        archCons.write(reinterpret_cast<const char*> (&sumaNota), sizeof (int));
        archCons.write(reinterpret_cast<const char*> (&cantMater), sizeof (int));
        archCons.write(reinterpret_cast<const char*> (facultad), sizeof (char)*4);
        archCons.write(reinterpret_cast<const char*> (&estado), sizeof (int));

        cout << left << setw(20) << codigo << setw(50) << nombre << facultad << endl;

    }
    archCons.close(); //PONER ESTO SINO NO IMPRIME EL ULTIMO DATO
    muestraConsolidado();
}

void actualizaArch(int codAl, int nota, double cred) {
    fstream archBinCon;
    abrirarchivo(archBinCon, "Consolidado.bin", 4);

    int codigo, sumaNota, cantMater, estado;
    char nombre[MAX], facultad[4];
    double credCur, credApr;

    int numReg, tamArch, tamReg = sizeof (int)*4 + sizeof (char)*(4 + MAX) + sizeof (double)*2;
    archBinCon.seekg(0, ios::end);
    tamArch = archBinCon.tellg();
    archBinCon.seekg(0, ios::beg);

    numReg = tamArch / tamReg;

    for (int i = 0; i < numReg; i++) {
        archBinCon.read(reinterpret_cast<char*> (&codigo), sizeof (int));
        archBinCon.read(reinterpret_cast<char*> (nombre), sizeof (char)*MAX);
        archBinCon.read(reinterpret_cast<char*> (&credCur), sizeof (double));
        archBinCon.read(reinterpret_cast<char*> (&credApr), sizeof (double));
        archBinCon.read(reinterpret_cast<char*> (&sumaNota), sizeof (int));
        archBinCon.read(reinterpret_cast<char*> (&cantMater), sizeof (int));
        archBinCon.read(reinterpret_cast<char*> (facultad), sizeof (char)*4);
        archBinCon.read(reinterpret_cast<char*> (&estado), sizeof (int));

        if (codAl == codigo) {
            //actualizar linea
            archBinCon.seekg(i * tamReg + sizeof (int) + sizeof (char)*MAX, ios::beg); //pos en donde escribo
            credCur += cred;

            if (nota > 10) {
                credApr += cred;
            }
            sumaNota += nota;
            cantMater++;
            if (credApr >= 45) {
                estado = 1;
            }
            archBinCon.write(reinterpret_cast<const char*> (&credCur), sizeof (double));
            archBinCon.write(reinterpret_cast<const char*> (&credApr), sizeof (double));
            archBinCon.write(reinterpret_cast<const char*> (&sumaNota), sizeof (int));
            archBinCon.write(reinterpret_cast<const char*> (&cantMater), sizeof (int));
            archBinCon.write(reinterpret_cast<const char*> (facultad), sizeof (char)*4);
            archBinCon.write(reinterpret_cast<const char*> (&estado), sizeof (int));
            break;
        }

    }

}

void actualizarConsolidado() {
    fstream archCur;
    abrirarchivo(archCur, "Cursos.txt", 1);

    int codAl, nota;
    char aux[7];
    double cred;

    while (1) {
        archCur>>codAl;
        if (archCur.eof()) break;
        archCur >> aux >> nota >> aux>>cred;

        actualizaArch(codAl, nota, cred);
    }

    muestraConsolidado();
}

int obtenerCodigoCarne(int codigoA) {
    fstream archBin;
    abrirarchivo(archBin, "Alumnos.bin", 4); //leer archivo

    char tipo, nombre[MAX], especialidad[MAX], facultad[4];
    int codigo, carne;

    int numReg, tamArch, tamReg = sizeof (int)*2 + sizeof (char)*(5 + MAX + MAX);
    archBin.seekg(0, ios::end);
    tamArch = archBin.tellg();
    archBin.seekg(0, ios::beg);

    numReg = tamArch / tamReg;

    for (int i = 0; i < numReg; i++) {
        archBin.read(reinterpret_cast<char*> (&codigo), sizeof (int));
        archBin.read(reinterpret_cast<char*> (nombre), sizeof (char)*MAX);
        archBin.read(reinterpret_cast<char*> (&tipo), sizeof (char));
        archBin.read(reinterpret_cast<char*> (&carne), sizeof (int));
        archBin.read(reinterpret_cast<char*> (facultad), sizeof (char)*4);
        archBin.read(reinterpret_cast<char*> (especialidad), sizeof (char)*MAX);

        if (codigoA == codigo) return carne;

    }

    return -1;
}

void imprimirLinea(fstream &Rep, char c, int cant) {
    Rep.fill(c);
    Rep << setw(cant) << c << endl;
    Rep.fill(' ');
}

void generarRep() {
    fstream archCons, archRep;
    abrirarchivo(archCons, "Consolidado.bin", 4); //leer
    abrirarchivo(archRep, "reporte.txt", 2);

    int codigo, sumaNota, cantMater, estado, cantReg=0, cantInt=0,cantEgr=0, cantExtrEgr=0;
    char nombre[MAX], facultad[4];
    double credCur, credApr;

    int numReg, tamArch, tamReg = sizeof (int)*4 + sizeof (char)*(4 + MAX) + sizeof (double)*2;
    archCons.seekg(0, ios::end);
    tamArch = archCons.tellg();
    archCons.seekg(0, ios::beg);

    numReg = tamArch / tamReg;

    //cabecera arch
    archRep << "CONSOLIDADO DE NOTAS DE LOS ALUMNOS" << endl;
    imprimirLinea(archRep, '=', MAX);
    archRep << left << setw(20) << "CODIGO" << setw(50) << "NOMBRE" << setw(20) << "CARNÉ" << setw(20) << "CRED. CURSADOS"
            << setw(20) << "CRED.APROBADOS" << setw(20) << "PROMEDIO" << "ESTADO"<<endl;
    imprimirLinea(archRep, '=', MAX);
    archRep.precision(2);
    archRep << fixed;

    for (int i = 0; i < numReg; i++) {
        archCons.read(reinterpret_cast<char*> (&codigo), sizeof (int));
        archCons.read(reinterpret_cast<char*> (nombre), sizeof (char)*MAX);
        archCons.read(reinterpret_cast<char*> (&credCur), sizeof (double));
        archCons.read(reinterpret_cast<char*> (&credApr), sizeof (double));
        archCons.read(reinterpret_cast<char*> (&sumaNota), sizeof (int));
        archCons.read(reinterpret_cast<char*> (&cantMater), sizeof (int));
        archCons.read(reinterpret_cast<char*> (facultad), sizeof (char)*4);
        archCons.read(reinterpret_cast<char*> (&estado), sizeof (int));

        int carne = obtenerCodigoCarne(codigo); //devuelve -1 si no encuentra

        archRep << setw(20) << codigo << setw(50) << nombre<<right;
        if (carne != 0){
            archRep  << setw(6) << carne << setw(20);
            cantInt++;
            if(estado == 1) cantExtrEgr++;
            
        }
        else {
            archRep << setw(6) << ' ' << setw(20);
            cantReg++;
        }

        archRep << credCur << setw(20) << credApr << setw(20) << sumaNota / (double) cantMater << left << setw(10) << ' ';

        if (estado == 1) {
            archRep << "EGRESADO" << endl;
            cantEgr++;
            
        } else {
            archRep << "NO EGRESADO" << endl;
        }

    }
    //liena
    imprimirLinea(archRep, '=', MAX);

    archRep << "RESUMEN:" << endl;
    archRep << "TOTAL DE ALUMNOS REGULARES: " << cantReg<<endl;
    archRep << "TOTAL DE ALUMNOS DE INTERCAMBIO: " <<cantInt<< endl << endl;

    archRep << "EGRESADOS: " <<cantEgr<< endl;
    archRep << "ALUMNOS DE INTERCAMBIO SI CARNÉ: " <<cantExtrEgr<< endl;
    imprimirLinea(archRep, '=', MAX);

}