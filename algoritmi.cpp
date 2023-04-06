//
// Created by Matteo Franchini on 04/04/23.
//

#include <iostream>
#include <algorithm>
#include "algoritmi.h"

using namespace std;

const int CONST = 100;

float avg (int *durata, int size);
bool compareByPriority(Processo a, Processo b);
void selectionSortByPriority(Processo *arr, int size);
void selectionSortByTime(Processo *arr, int size);

// Definizione dell'algoritmo FCFS

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

// Definizione dell'algoritmo Priorità

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

// Definizione dell'algoritmo SJF

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

// Definizione dell'algoritmo RR
void algoritmo_RR (Processo *p, int num_processi, int quanto) {
    int n = CONST;
    int *array_durata = new int [n];
    for (int i = 0; i < num_processi; i++) {
        if (p[i].durata <= quanto) {
            cout << "->" << p[i].nome;
        }
        else {}
    }
    delete [] array_durata;
}

// Funzione di calcolo del tempo medio

float avg (int *durata, int size) {
    int sum_int = 0; int sum = 0;
    for (int j = 0; j < size-1; j++) {
        sum_int += durata[j];
        sum += sum_int;
    }
    return sum/size;
}