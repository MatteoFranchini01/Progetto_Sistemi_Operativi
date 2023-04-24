//
// Created by Matteo Franchini on 07/04/23.
//

#ifndef PROGETTO_SISTEMI_OPERATIVI_STRUCT_H
#define PROGETTO_SISTEMI_OPERATIVI_STRUCT_H

#include <string>


using namespace std;

/// @brief Struct creata per salvare il nome, la durata e la priorità del processo
struct Processo{
    string nome;
    int istante_arrivo;
    int durata;
    int priorita;
};

#endif //PROGETTO_SISTEMI_OPERATIVI_STRUCT_H
