//
// Created by Matteo Franchini on 04/04/23.
//

#include <iostream>
#include <algorithm>
#include <queue>
#include <list>
#include "algoritmi.h"
#include "selection_sort.h"

using namespace std;

const int CONST = 100;

float avg (int *durata, int size);
queue<Processo> from_array_to_queue(Processo *p, int num_processi);
float avg_RR (Processo *durata, int size, int num_processi);
void algoritmo_SRTF (Processo *p, int num_processi);
void stampa_coda (queue<Processo> coda);
list<Processo> analisi_processi (Processo *p, int num_processi, int time);
bool confronto_durata (const Processo& a, const Processo& b);

/// @brief Definizione dell'algoritmo FCFS
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

/// @brief Definizione dell'algoritmo Priorità
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

/// @brief Definizione dell'algoritmo BJF
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


/// @brief Definizione dell'algoritmo RR
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

void algoritmo_SRTF (Processo *p, int num_processi) {
    int counter = 0; int time = -1; Processo temp;
    list<Processo> lista;
    list<Processo> processi_analizzati;
    bool flag = false;
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
        cout << "TIME " << time << endl;
        cout << "Primo processo della lista " << lista.front().nome << " DURATA " << lista.front().durata << endl;

        /*!
         * Quando la durata di un processo arriva a 0 lo andiamo
         * a togliere dalla lista
         */

        if (lista.front().durata == 0) {
            cout << "FINE PROCESSO " << lista.front().nome << endl;
            lista.pop_front();
            cout << "NUOVO FRONT " << lista.front().nome << endl;
        }

        /// L'algoritmo termina quando la lista è vuota

        if (lista.empty()) { flag = true; }
    }
}

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

bool confronto_durata (const Processo& a, const Processo& b) {
    return a.durata < b.durata;
}


/// @brief Creazione di una funzione che trasforma un array in una coda
queue<Processo> from_array_to_queue(Processo *p, int num_processi) {
    queue<Processo> var;
    for (int i = 0; i < num_processi; i++) {
        Processo temp;
        temp.nome = p[i].nome;
        temp.durata = p[i].durata;
        temp.priorita = p[i].priorita;
        var.push(temp);
    }
    return var;
}


/// @brief Funzione di calcolo del tempo medio
float avg (int *durata, int size) {
    // Tempo di attesa del singolo processo

    int sum_int = 0;

    // Tempo di attesa complessivo

    int sum = 0;

    for (int j = 0; j < size-1; j++) {
        sum_int += durata[j];
        sum += sum_int;
    }
    return sum/size;
}

/// @brief Funzione di calcolo del tempo medio per l'algoritmo Round Robin
float avg_RR (Processo *durata, int size, int num_processi) {
    bool flag = false;
    int sum = 0;
    for (int i = 0; i < num_processi; i++) {
        for (int j = size; j >= 0; j--) {
            if (durata[i].nome == durata[j].nome) {
                flag = true;
            }
            if (flag == true && durata[i].nome != durata[j].nome) {
                sum += durata[j].durata;
            }
        }
        flag = false;
    }
    return sum/num_processi;
}

/// @brief funzione per stampare le code semplicemente, si noti che la coda viene passata non come puntatore
void stampa_coda (queue<Processo> coda) {
    while (not coda.empty()) {
        cout << coda.front().nome << endl;
        coda.pop();
    }
}