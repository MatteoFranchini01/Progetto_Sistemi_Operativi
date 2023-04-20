//
// Created by Matteo Franchini on 04/04/23.
//

#include <iostream>
#include <algorithm>
#include <queue>
#include "algoritmi.h"
#include "selection_sort.h"

using namespace std;

const int CONST = 100;

float avg (int *durata, int size);
queue<Processo> from_array_to_queue(Processo *p, int num_processi);
float avg_RR (Processo *durata, int size, int num_processi);


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