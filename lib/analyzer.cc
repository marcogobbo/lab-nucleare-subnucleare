#include "analyzer.h"

// Metodo della classe Analyzer per il caricamento dei file
bool Analyzer::loadData(string fileName, vector<double>& data, double& min, double& max) {
    // Creo l'oggetto fileData
    fstream fileData;

    // Apro il file con il nome passato come parametro e lo apro in sola lettura
    fileData.open(fileName.c_str(), ios::in);

    // Controllo che sia andato tutto correttamente
    if (fileData.good() == false) {
        return false;
    }

    // Creo una variabile per trasferire i valori e una variabile per vedere se è il primo ciclo per assegnare max e min
    double value;
    bool first = true;

    // Inserisco i dati nel vettore che mi è stato passato data
    while(true) {
        // Se il file è finito interrompo il ciclo
        if (fileData.eof() == true) break;

        // Inserisco il primo dato nella variabile temporanea value
        fileData >> value;

        //cout << value << endl;

        // Inserisco i valori nel vettore data
        data.push_back(value);

        // Faccio un controllo per assegnare i primi valori di max e min
        if (first == true) {
            min = value;
            max = value;

            first = false;
        }

        // Se non è il primo ciclo controllo ogni volta se c'è un nuovo max o nuovo min
        else {
            if (value < min) {
                min = value;
            }
            if (value > max) {
                max = value;
            }
        }
    }
    
    // Chiudo il file
    fileData.close();

    return true;
}