//
// Created by Matteo Franchini on 06/04/23.
//

#include "selection_sort.h"

/// Funzioni per ordinare gli elementi in base alla priorità
bool compareByPriority(Processo a, Processo b) {
    return a.priorita < b.priorita;
}

/// Algoritmo selection sort che opera in base alla priorità secondo la funzione "compareByPriority"
void selectionSortByPriority(Processo *arr, int size) {
    int i, j, min_idx;
    for (i = 0; i < size - 1; i ++) {
        min_idx = i;
        for (j = i + 1; j < size; j++) {
            if (compareByPriority(arr[j], arr[min_idx])) {
                min_idx = j;
            }
        }
        swap(arr[min_idx], arr[i]);
    }
}

/// Funzione per confrontare i processi in base alla durata
bool compareByTime(Processo a, Processo b) {
    return a.durata < b.durata;
}

/// Algoritmo selection sort che ordina in base alla durata secondo la funzione "compareByTime"
void selectionSortByTime(Processo *arr, int size) {
    int i, j, min_idx;
    for (i = 0; i < size - 1; i ++) {
        min_idx = i;
        for (j = i + 1; j < size; j++) {
            if (compareByTime(arr[j], arr[min_idx])) {
                min_idx = j;
            }
        }
        swap(arr[min_idx], arr[i]);
    }
}