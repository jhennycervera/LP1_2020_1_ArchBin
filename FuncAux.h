/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   FuncAux.h
 * Author: jhenn
 *
 * Created on 16 de septiembre de 2021, 12:20 PM
 */

#ifndef FUNCAUX_H
#define FUNCAUX_H

#include "FuncAux.h"
#include <iostream>        
#include <iomanip>
#include <fstream>
using namespace std;
#define MAX 200

void abrirarchivo(fstream &, const char *,int );

void muestraAlumBin();

void generarBinAlumnos();
void muestraConsolidado() ;

void generarConsolidado();
void actualizarConsolidado();
void actualizaArch(int , int , double );
void generarRep();

int obtenerCodigoCarne(int );
void imprimirLinea(fstream &, char , int ) ;


#endif /* FUNCAUX_H */
