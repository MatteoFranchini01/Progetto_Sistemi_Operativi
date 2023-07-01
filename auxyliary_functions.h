//
// Created by Matteo Franchini on 25/04/23.
//

#ifndef PROGETTO_SISTEMI_OPERATIVI_AUXYLIARY_FUNCTIONS_H
#define PROGETTO_SISTEMI_OPERATIVI_AUXYLIARY_FUNCTIONS_H

#include "struct.h"
#include <list>
#include <queue>

list<Processo> analisi_processi (Processo *p, int num_processi, int time);
bool confronto_durata (const Processo& a, const Processo& b);
queue<Processo> from_array_to_queue(Processo *p, int num_processi);
float avg (int *durata, int size);
float avg_RR (Processo *durata, int size, int num_processi);
void reset_array (Processo *arr, Processo *arr_copia, int num_processi);
void print_SRTF (list<Processo_log> &log);
int calcolo_TE_con_processi_multipli (Processo_log *arr, int count);
bool confronto_processi (const Processo_log& a, const Processo_log& b);
float avg_SRTF (list<Processo_log> &log, int num_processi);

#endif //PROGETTO_SISTEMI_OPERATIVI_AUXYLIARY_FUNCTIONS_H
