//
// Created by Matteo Franchini on 25/04/23.
//
#include <iostream>
#include <map>
#include "auxyliary_functions.h"

const int CONST_NUM = 100000;

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

/*!
 * Funzione che permette di stampare i risultati dell'algoritmo SRTF
 * @param log
 * @param p
 * @param num_processi
 */

void print_SRTF (list<Processo_log> &log) {
    list<Processo_log>::iterator it = log.end();
    list<Processo_log>::iterator temp = prev(it);
    list<Processo_log> cambio_processo;

    while (it != log.begin()) {
        if (temp->nome != it->nome) {
            cout << "->" << temp->nome;
        }
        --it;
        --temp;
    }
}

/*!
 * Funzione che permette di ordinare una lista di processi in base al nome
 * @param log
 * @param p
 * @param num_processi
 * @return bool
 */

bool confronto_processi (const Processo_log& a, const Processo_log& b) {
    return a.nome < b.nome;
}

/*!
 * Questa funzione permette il calcolo del tempo di attesa per l'algoritmo SRTF in presenza di più di un processo
 * ripetuto
 * @param arr
 * @param count
 * @return int sum
 */

int calcolo_TE_con_processi_multipli (Processo_log *arr, int count) {
    int sum = 0;

    /*!
     * Come prima cosa andiamo a prendere il tempo del processo che sarà in posizione count-2
     * in quanto l'ultimo processo, in posizione count-1, non ci interessa perché stiamo
     * calcolando il tempo di attesa e non quello di esecuzione, però non basta calcolare il tempo
     * di esecuzione prendendo questo tempo, ma sarà necessario andare a sottrarre a questo tempo
     * quello delle precedenti esecuzioni del processo
     */

    sum = arr[count -2].time;

    /*!
     * Una volta individuato qual è il processo che ha tempo di attesa più lungo per andare a togliere
     * il tempo delle precedenti esecuzioni non facciamo altro che andare a sottrarre il tempo che
     * abbiamo nelle posizioni dispari, questo perché ogni processo ha un valore iniziale e uno finale (il valore
     * iniziale sarà in posizione dispari mentre quello finale in posizione pari), ma per quanto detto
     * prima a noi interessa il valore iniziale e quindi prendiamo solo quelli in posizione dispari
     */

    for (int i = count - 3; i >= 0; i--) {
        if (count % 2 != 0) {
            sum = sum - arr[i].time;
        }
    }
    return sum;
};

/*!
 * Questa funzione permette il calcolo del tempo di attesa per l'algoritmo SRTF
 * @param log
 * @param num_processi
 * @return float avg
 */

float avg_SRTF (list<Processo_log> &log, int num_processi) {
    list<Processo_log>::iterator it = log.end();
    list<Processo_log>::iterator temp = prev(it);
    list<Processo_log> cambio_processo;

    while (it != log.begin()) {
        if (temp->nome != it->nome) {
            if (it->nome != "") {
                Processo_log temp_proc_prec;
                temp_proc_prec.nome = it->nome;
                temp_proc_prec.time = it->time;
                cambio_processo.push_back(temp_proc_prec);
            }

            Processo_log temp_proc_succ;
            temp_proc_succ.nome = temp->nome;
            temp_proc_succ.time = temp->time;
            cambio_processo.push_back(temp_proc_succ);

        }
        --it;
        --temp;

        if (it == log.begin()) {
            Processo_log temp_proc_prec;
            temp_proc_prec.nome = it->nome;
            temp_proc_prec.time = it->time;
            cambio_processo.push_back(temp_proc_prec);
        }
    }

    cambio_processo.sort(confronto_processi);

    it = cambio_processo.begin();
    map<string, int> counter;

    while (it != cambio_processo.end()) {
        temp = cambio_processo.begin();
        while (temp != cambio_processo.end()) {
            if (it->nome == temp->nome && it->time == temp->time) {
                counter[it->nome]++;
            }
            ++temp;
        }
        ++it;
    }

    it = cambio_processo.begin();
    temp = next(it);

    Processo_log *arr_ausiliario = new Processo_log[CONST_NUM];
    float sum = 0;

    int count = 1;
    bool flag = false;

    while (it != cambio_processo.end()) {
        if (it->nome == temp->nome) {
            if (counter[it->nome] == 2) {
                if (it->time < temp->time) { sum += it->time; }
                else if (it->time > temp->time) { sum += temp->time; }
            }

            else if (counter[it->nome] > 2) {
                arr_ausiliario[count] = *it;
                count++;
                if (count+1 == counter[it->nome]) { flag = true; }
            }

            if (flag) {
                sum += calcolo_TE_con_processi_multipli(arr_ausiliario, counter[it->nome]);
                flag = false;
            }
        }
        ++it;
        ++temp;
    }
    delete[] arr_ausiliario;

    float size_dec = static_cast<float>(num_processi);

    return sum/size_dec;
}

/*!
 * Calcolo del tempo medio per l'algoritmo RR con priorità
 * @param arr
 * @param num_processi
 * @param size
 * @return float avg
 */

float avg_RR_priorita (Processo_log *arr, int num_processi, int size) {
    float sum = 0;

    /// Creazione di un dizionario per salvare i processi che sono stati eseguiti per ultiimi

    map<string, int> map_max;

    /*!
     * Creazione di un dizionario per salvare i tempi di esecuzione dei processi eseguiti
     * prima dell'ultimo, questo valore andrà sottratto a quello massimo in modo da calcolare il tempo
     * medio
     */

    map<string, int> map_sum;

    /// Popolazione dei dizionari

    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            if (arr[i].nome == arr[j].nome && arr[i].time <= arr[j].time) {
                map_max[arr[j].nome] = arr[j].time;
            }
        }
    }

    for (int i = 1; i < size+1; i++) {
        if (arr[i-1].time < map_max[arr[i-1].nome]) {
            map_sum[arr[i-1].nome] += arr[i].time - arr[i-1].time - 1;
        }
    }

    for (int i = 0; i < num_processi; i++) {
        sum += map_max[arr[i].nome] - map_sum[arr[i].nome];
    }

    float size_dec = static_cast<float>(num_processi);
    return sum/size_dec;
}