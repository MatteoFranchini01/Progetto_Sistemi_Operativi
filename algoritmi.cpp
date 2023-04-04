//
// Created by Matteo Franchini on 04/04/23.
//

#include <iostream>
#include <algorithm>
#include "algoritmi.h"

using namespace std;

const int CONST = 100;

int avg (int *durata, int size);
bool compareByPriority(Processo a, Processo b);
void selectionSortByPriority(Processo *arr, int size);

// Definizione dell'algoritmo FCFS

void algoritmo_FCFS (Processo *p) {
    int size = 0;
    int n = CONST;
    int *array_durata = new int[n];
    cout << "FCFS ";
    int array_lenth = sizeof(p);

    /* Nel ciclio for è stato inserito un controllo perché,
     * essendo l'array allocato dinamicamente, si va a popolare
     * di più valori di quelli richiesti e siccome, nel modello creato
     * nessun elemento ha priorità 0, usiamo questo valore come valore
     * di controllo
     */

    for (int i = 0; i < array_lenth; i++) {
        if (p[i].priorita != 0) {
            cout << "->" << p[i].nome;
            array_durata[i] = p[i].durata;
            size++;
        }
    }
    ;
    cout << endl << "TEMPO MEDIO " << avg(array_durata, size) << endl;
    delete [] array_durata;
}

// Definizione dell'algoritmo Priorità

void algoritmo_priorita (Processo *p) {
    cout << "qUI";
    int array_lenth = sizeof(p);
    selectionSortByPriority(p, array_lenth);
    for (int i = 0; i < array_lenth; i++) {
        cout << "->" << p[i].nome;
    }
}

int avg (int *durata, int size) {
    int sum_int = 0; int sum = 0;
    for (int j = 0; j < size-1; j++) {
        sum_int += durata[j];
        sum += sum_int;
    }
    return sum/size;
}

/*
 * Due funzioni per ordinare gli elementi in base
 * alla priorità
 */

bool compareByPriority(Processo a, Processo b) {
    return a.priorita < b.priorita;
}

void selectionSortByPriority(Processo *arr, int size) {
    int i, j, min_idx;
    for (i = 0; i < size - 1; i ++) {
        min_idx = i;
        for (j = i + 1; j < size; j++) {
            if (compareByPriority(arr[j], arr[min_idx])) {
                min_idx = j;
            }
        }
    }
    swap(arr[min_idx], arr[i]);
}