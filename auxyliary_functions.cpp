//
// Created by Matteo Franchini on 25/04/23.
//
#include <iostream>
#include <unordered_map>
#include "auxyliary_functions.h"


/*!
 * Questa funzione viene chiamata nell'esecuzione dell'algoritmo SRTF
 * e permette di analizzare quali processi vengono chiamati in un particolare istante
 * di tempo e li ordina in base alla durata
 * @param Processo p
 * @param int num_processi
 * @param int time
 * @return list<Processo> processi_in_arrivo
 */

list<Processo> analisi_processi (Processo *p, int num_processi, int time) {
    list<Processo> processi_in_arrivo;
    for (int i = 0; i < num_processi; i++) {
        if (p[i].istante_arrivo == time) {
            processi_in_arrivo.push_back(p[i]);
            processi_in_arrivo.sort(confronto_durata);
        }
    }
    return processi_in_arrivo;
}

/*!
 * Insieme alla funzione "analisi_processi" permette l'ordinamento dei processi in
 * base alla durata
 * @param Processo a
 * @param Processo b
 * @return bool
 */

bool confronto_durata (const Processo& a, const Processo& b) {
    return a.durata < b.durata;
}

/*!
 * Creazione di una funzione che trasforma un array in una coda
 * @param Processo p
 * @param int num_processi
 * @return queue<Processo> coda
 */

queue<Processo> from_array_to_queue(Processo *p, int num_processi) {
    queue<Processo> var;
    for (int i = 0; i < num_processi; i++) {
        if (p[i].nome == "") {
            continue;
        }
        Processo temp;
        temp.nome = p[i].nome;
        temp.durata = p[i].durata;
        temp.priorita = p[i].priorita;
        var.push(temp);
    }
    return var;
}


/*!
 * Funzione di calcolo del tempo medio
 * @param int durata
 * @param int size
 * @return float avg
 */
float avg (int *durata, int size) {
    // Tempo di attesa del singolo processo

    int sum_int = 0;

    // Tempo di attesa complessivo

    int sum = 0;

    for (int j = 0; j < size-1; j++) {
        sum_int += durata[j];
        sum += sum_int;
    }

    /*!
     * Conversione da int a float per garantire che la funzione
     * restituisca anche numeri decimali
     */

    float sum_dec = static_cast<float>(sum);
    float size_dec = static_cast<float>(size);

    return sum_dec/size_dec;
}


/*!
 * Funzione di calcolo del tempo medio per l'algoritmo Round Robin
 * @param Processo durata
 * @param int size
 * @param int num_processi
 * @return float avg
 */

float avg_RR (Processo *durata, int size, int num_processi) {
    bool flag = false;
    int sum = 0;
    for (int i = 0; i < num_processi; i++) {
        for (int j = size; j >= 0; j--) {
            if (durata[i].nome == durata[j].nome) {
                flag = true;
            }
            if (flag && durata[i].nome != durata[j].nome) {
                sum += durata[j].durata;
            }
        }
        flag = false;
    }

    /*!
     * Conversione da int a float per garantire che la funzione
     * restituisca anche numeri decimali
     */

    float sum_dec = static_cast<float>(sum);
    float processi_dec = static_cast<float>(num_processi);

    return sum_dec/processi_dec;
}

/*!
 * Funzione che permette di resettare l'array dei processi
 * @param Processo arr
 * @param Processo arr_copia
 * @param int num_processi
 */

void reset_array (Processo *arr, Processo *arr_copia, int num_processi) {
    for (int i = 0; i < num_processi; i++) {
        arr_copia[i] = arr[i];
    }
}

void avg_SRTF (list<Processo_log> &log, Processo *p, int num_processi) {
    list<Processo_log>::iterator temp;
    list<Processo_log>::iterator it = log.begin();

    unordered_map<string, int> map;

    for (int i = 0; i < num_processi; i++) {
        string temp1 = p[i].nome;
        map[temp1] = 0;
    }

    while (it != log.end()) {
       cout << "NOME: " << it->nome << " TEMPO " << it->time << endl;


       // ragionare su come funzionano questi indici e cercare di invertire primo con secondo in modo
       // che l'ordine sia rispettato, una volta fatto quello dovrebbe funzionare


       temp = it++;
       if (temp->nome != it->nome) {
           cout << "NOME PRIMO " << it->nome << " TEMPO PRIMO " << it->time << endl;
           cout << "NOME SECONDO " << temp->nome << " TEMPO SECONDO " << temp->time << endl;
           int in_esecuzione = 60-it->time;
           cout << "IN ESECUZIONE " << in_esecuzione << endl;
           map[it->nome] = map[it->nome] + in_esecuzione;
       }
       it--;

       //cout << "MAP: " << map[it->nome] << endl;
       it++;
    }

    for (auto i = map.begin(); i != map.end(); i++) {
        cout << "NOME: " << i->first << " TEMPO: " << i->second << endl;
    }
}

