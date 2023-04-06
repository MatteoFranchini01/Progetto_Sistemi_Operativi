//
// Created by Matteo Franchini on 03/04/23.
//

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "algoritmi.h"

using namespace std;

const int CONST = 100;

int main() {
    // Inizializzazione delle variabili

    string nome; int durata; int priorita;
    string str1; string str2; string str3; string str4;
    int num_processi;
    int quanto;
    int counter = -1;
    int scelta_algoritmo = 0;

    /*
     * Creazione di un array di tipo Processo
     * con allocazione dinamica
     */

    int n = CONST;
    Processo* arr = new Processo[n];

    // Lettura da file

    ifstream myfile ("config.txt");

    if (myfile.is_open()) {
        while (getline(myfile, nome, ' ')) {
            if (counter == -1) {
                getline(myfile, str3, ' ');
                istringstream tk3 (str3);
                tk3 >> num_processi;
                getline(myfile, str4);
                istringstream tk4 (str4);
                tk4 >> quanto;
                counter++;
            }
            else {
                getline(myfile, str1, ' ');
                istringstream tk1(str1);
                tk1 >> durata;
                getline(myfile, str2);
                istringstream tk2(str2);
                tk2 >> priorita;
                arr[counter].nome = nome;
                arr[counter].durata = durata;
                arr[counter].priorita = priorita;
                counter++;
            }
        }
        myfile.close();
    } else cout << "Impossibile aprire il file";

    // Scelta dell'algoritmo

    cout << "Selezionare l'algoritmo che si intende utilizzare" << endl;
    cout << "Premere 1 per FCFS" << endl;
    cout << "Premere 2 per BJP" << endl;
    cout << "Premere 3 per Priorità" << endl;
    cout << "Premere 4 per RR" << endl;
    cin >> scelta_algoritmo;

    switch (scelta_algoritmo) {
        case 1:
            cout << "Hai scelto l'algoritmo FCFS" << endl;
            algoritmo_FCFS(arr, num_processi);
            break;

        case 2:
            cout << "Hai scelto l'algoritmo BJP" << endl;
            algoritmo_BJP(arr, num_processi);
            break;

        case 3:
            cout << "Hai scelto l'algoritmo Priorità" << endl;
            algoritmo_priorita(arr, num_processi);
            break;

        case 4:
            cout << "Hai scelto l'algoritmo RR";
            break;
    }


    // Cancellazione dell'array con allocazione dinamica

    delete[] arr;

    return 0;
}