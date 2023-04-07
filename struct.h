//
// Created by Matteo Franchini on 07/04/23.
//

#ifndef PROGETTO_SISTEMI_OPERATIVI_STRUCT_H
#define PROGETTO_SISTEMI_OPERATIVI_STRUCT_H

#include <string>

using namespace std;

struct Processo{
    string nome;
    int durata;
    int priorita;
};

/*
 * struct Processo_RR {
    string nome;
    int max_index;
    int min_index;
};
*/
#endif //PROGETTO_SISTEMI_OPERATIVI_STRUCT_H
