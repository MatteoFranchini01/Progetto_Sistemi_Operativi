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

/*!
 * Struct creata per salvare il nome e il tempo di esecuzione del processo
 * durante l'esecuzione dell'algoritmo SRTF.
 * Verrà usata nel calcolo del tempo medio di esecuzione
 */

struct Processo_log {
    string nome;
    int time;
};

#endif //PROGETTO_SISTEMI_OPERATIVI_STRUCT_H
