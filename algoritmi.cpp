//
// Created by Matteo Franchini on 04/04/23.
//

#include <iostream>
#include <algorithm>
#include <queue>
#include <list>
#include "algoritmi.h"
#include "struct.h"


using namespace std;

const int CONST = 100;


/*!
 * Definizione dell'algoritmo FCFS
 * @param Processo p
 * @param int num_processi
 */
void algoritmo_FCFS (Processo *p, int num_processi) {
    int n = CONST;
    int *array_durata = new int[n];
    cout << "FCFS ";
    for (int i = 0; i < num_processi; i++) {
        cout << "->" << p[i].nome;
        array_durata[i] = p[i].durata;
    }
    cout << endl << "TEMPO MEDIO " << avg(array_durata, num_processi) << endl;
    delete [] array_durata;
}


/*!
 * Definizione dell'algoritmo "Priorità"
 * @param Processo p
 * @param int num_processi
 */
void algoritmo_priorita (Processo *p, int num_processi) {
    int n = CONST;
    int *array_durata = new int [n];
    selectionSortByPriority(p, num_processi);
    cout << "PRIORITÀ ";
    for (int i = 0; i < num_processi; i++) {
        cout << "->" << p[i].nome;
        array_durata[i] = p[i].durata;
    }
    cout << endl << "TEMPO MEDIO " << avg(array_durata, num_processi) << endl;
    delete [] array_durata;
}


/*!
 * Definizione dell'algoritmo BJF
 * @param Processo p
 * @param int num_processi
 */
void algoritmo_BJP (Processo *p, int num_processi) {
    int n = CONST;
    int *array_durata = new int [n];
    selectionSortByTime(p, num_processi);
    cout << "BJP ";
    for (int i = 0; i < num_processi; i++) {
        cout << "->" << p[i].nome;
        array_durata[i] = p[i].durata;
    }
    cout << endl << "TEMPO MEDIO " << avg(array_durata, num_processi) << endl;
    delete [] array_durata;
}


/*!
 * Definizione dell'algoritmo RR
 * @param Processo p
 * @param int num_processi
 * @param int quanto
 */

void algoritmo_RR (Processo *p, int num_processi, int quanto) {
    int array_counter = 0;
    int n = CONST;
    cout << "RR ";
    Processo *array_durata = new Processo [n];
    queue<Processo> processi = from_array_to_queue(p, num_processi);
    while (not processi.empty()) {
        if (processi.front().durata <= quanto) {
            cout << "->" << processi.front().nome;
            array_durata[array_counter] = processi.front();
            processi.pop();
            array_counter++;
        }
        else if (processi.front().durata >= quanto){
            Processo temp;
            temp.nome = processi.front().nome;
            temp.durata = processi.front().durata - quanto;
            temp.priorita = processi.front().priorita;
            cout << "->" << temp.nome;
            Processo durata;
            durata.nome = processi.front().nome;
            durata.durata = quanto;
            durata.priorita = processi.front().priorita;
            array_durata[array_counter] = durata;
            processi.push(temp);
            processi.pop();
            array_counter++;
        }
    }
    cout << endl << "TEMPO MEDIO " << avg_RR(array_durata, array_counter, num_processi) << endl;
    delete [] array_durata;
}


/*!
 * Definizione dell'algoritmo SRTF
 * @param Processo p
 * @param int num_processi
 */

void algoritmo_SRTF (Processo *p, int num_processi) {
    int counter = 0; int time = -1; Processo temp;
    list<Processo_log> log;
    list<Processo> lista;
    list<Processo> processi_analizzati;
    bool flag = false;
    cout << "SRTF ";
    while (flag == false) {
        time++;

        /*!
         *  in caso ci siano più processi in arrivo nello
         *  stesso istante viene creata una lista di processi
         *  ordinata per durata, quindi il primo elemento della lista
         *  sarà quello con durata minore
         */

        processi_analizzati = analisi_processi(p, num_processi, time);

        /*!
         * Andiamo ad inserire nella lista tutti i processi
         * che entrano in giorco in quell'isante di tempo
         */

        while (not processi_analizzati.empty()) {
            lista.push_front(processi_analizzati.front());
            processi_analizzati.pop_front();
        }

        /*!
         * Una volta che tutti i processi sono stati inseriti andiamo
         * ad ordinare la lista in modo tale da avere come primo
         * elemento quello con durata minore
         */

        lista.sort(confronto_durata);

        /// Ad ogni iterazione viene decrementata la durata del processo "front" della lista

        lista.front().durata--;


        /// Inserimenti del processo all'intenro del log

        Processo_log temp;
        temp.nome = lista.front().nome;
        temp.time = time;
        log.push_front(temp);

        /*!
         * Quando la durata di un processo arriva a 0 lo andiamo
         * a togliere dalla lista
         */

        if (lista.front().durata == 0) {
            lista.pop_front();
        }

        /// L'algoritmo termina quando la lista è vuota

        if (lista.empty()) { flag = true; }
    }

    /// Stampa dei risultati dell'algoritmo

    print_SRTF(log);

    cout << "\nTEMPO MEDIO: " << avg_SRTF(log, num_processi) << endl;
}

/*!
 * Algoritmo Round Robin con priorità
 * @param p
 * @param num_processi
 * @param quanto
 */

void algoritmo_priorita_RR (Processo *p, int num_processi, int quanto) {
    Processo_log* arr_log = new Processo_log[CONST];
    int counter = 0;
    int i = 0;

    /// Ordinamento dei processi per priorità
    selectionSortByPriority(p, num_processi);

    /// Creazione della coda di processi a partire da un array ordinato per priorità
    queue<Processo> coda_processi;
    coda_processi = from_array_to_queue(p, num_processi);

    while(not coda_processi.empty()) {
        if (coda_processi.front().durata <= quanto) {
            Processo_log temp_log;
            arr_log[i].nome = coda_processi.front().nome;;
            arr_log[i].time = counter;

            cout << "->" << coda_processi.front().nome;
            counter = counter + coda_processi.front().durata;

            coda_processi.pop();
        }
        else if (coda_processi.front().durata > quanto) {
            Processo_log temp_log;
            temp_log.nome = coda_processi.front().nome;
            temp_log.time = counter;
            arr_log[i] = temp_log;

            Processo temp;
            temp.nome = coda_processi.front().nome;
            temp.durata = coda_processi.front().durata - quanto;
            temp.priorita = coda_processi.front().priorita;
            temp.istante_arrivo = coda_processi.front().istante_arrivo;
            cout << "->" << temp.nome;

            counter = counter + quanto;

            coda_processi.pop();
            coda_processi.push(temp);
        }
        counter++;
        i++;
    }

    cout << "\nTEMPO MEDIO: " << avg_RR_priorita(arr_log, num_processi, i) << endl;
    delete [] arr_log;
}

