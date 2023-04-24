//
// Created by Matteo Franchini on 03/04/23.
//

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <queue>
#include "algoritmi.h"

using namespace std;

const int CONST = 100;

int main(int argc, char *argv[]) {

    /// @brief Controllo del numero di argomenti passati da riga di comando
    if (argc != 2) {
        cout << "Errore: inserire il nome del file di input" << endl;
        return 1;
    }

    /// @brief Se il numero di argomenti è corretto, si procede con l'esecuzione del programma
    else {

    /// @brief Inizializzazione delle variabili
    string nome; int durata; int priorita; int istante_arrivo;
    string str1; string str2; string str3; string str4; string str5;
    int num_processi;
    int quanto;
    int counter = -1;
    int scelta_algoritmo = 0;


    /// @brief Creazione di un array di tipo Processo con allocazione dinamica
    int n = CONST;
    Processo* arr = new Processo[n];

    /// @brief Lettura da file
    ifstream myfile (argv[1]);

    if (myfile.is_open()) {
        while (getline(myfile, str5, ' ')) {
            if (counter == -1) {
                getline(myfile, nome, ' ');
                getline(myfile, str3, ' ');
                istringstream tk3 (str3);
                tk3 >> num_processi;
                getline(myfile, str4);
                istringstream tk4 (str4);
                tk4 >> quanto;
                counter++;
            }
            else {
                istringstream tk5(str5);
                tk5 >> istante_arrivo;
                getline(myfile, nome, ' ');
                getline(myfile, str1, ' ');
                istringstream tk1(str1);
                tk1 >> durata;
                getline(myfile, str2);
                istringstream tk2(str2);
                tk2 >> priorita;
                arr[counter].nome = nome;
                arr[counter].istante_arrivo = istante_arrivo;
                arr[counter].durata = durata;
                arr[counter].priorita = priorita;
                counter++;
            }
        }
        myfile.close();
    } else cout << "Impossibile aprire il file";

    /// @brief Scelta dell'algoritmo
    cout << "Selezionare l'algoritmo che si intende utilizzare" << endl;
    cout << "Premere 1 per FCFS" << endl;
    cout << "Premere 2 per BJP" << endl;
    cout << "Premere 3 per Priorità" << endl;
    cout << "Premere 4 per RR" << endl;
    cout << "Premere 5 per tutti gli algoritmi" << endl;
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
            cout << "Hai scelto l'algoritmo RR" << endl;
            algoritmo_RR(arr, num_processi, quanto);
            break;

        case 5:
            cout << "Hai scelto tutti gli algoritmi" << endl;
            algoritmo_FCFS(arr, num_processi);
            algoritmo_BJP(arr, num_processi);
            algoritmo_priorita(arr, num_processi);
            algoritmo_RR(arr, num_processi, quanto);
            break;
    }


    /// @brief Cancellazione dell'array con allocazione dinamica
    delete[] arr;

    return 0;
    }
}