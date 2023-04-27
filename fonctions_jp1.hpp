#ifndef FONCTIONS_JP1_HPP_INCLUDED
#define FONCTIONS_JP1_HPP_INCLUDED


#include <iostream>
#include <cmath>
#include <fstream>
#include <zlib.h>
#include <vector>
#include <curl/curl.h>
#include <stdio.h>
#include <string> 
#include "zconf.h"  
#include <algorithm>
#include <filesystem>
#include <iterator>
using namespace std;


//Fonction retournant true si tous les elements d'un vecteur sont du meme signe 
bool memesigne (std::vector<int8_t> vect )
{bool same_sign;
return same_sign = std::all_of(vect.begin(), vect.end(), [](int i){ return i >= 0; })  || std::all_of(vect.begin(), vect.end(), [](int i){ return i <= 0; });
}


// Fonction qui compresse un vecteur de booléens
vector<int> compressBoolVector(const vector<bool>& boolVector) {
    vector<int> compressedVector;
    bool lastValue = boolVector[0];
    int count = 1;
    for (int i = 1; i < boolVector.size(); i++) {
        if (boolVector[i] == lastValue) {
            count++;
        } else {
            compressedVector.push_back(lastValue ? count : -count);
            lastValue = boolVector[i];
            count = 1;
        }
    }
    compressedVector.push_back(lastValue ? count : -count);
    return compressedVector;
}


// fonction jp qui cumule les valeurs pour compresser
vector<int> compressBoolVector2(const vector<bool>& boolVector) {
    vector<int> compressedVector;
   
    compressedVector.push_back( boolVector[0]);
    for (int i = 0; i < boolVector.size(); i++) {
        if (boolVector[i+1] != boolVector[i]) { compressedVector.push_back(i);}
    }
    compressedVector.push_back( boolVector.size());
    return compressedVector;
}

// Fonction qui décompresse un vecteur de booléens à partir d'un vecteur compressé
vector<bool> decompressBoolVector(const vector<int>& compressedVector) {
    vector<bool> boolVector;
    for (int i = 0; i < compressedVector.size(); i++) {
        int count = abs(compressedVector[i]);
        bool value = compressedVector[i] > 0;
        for (int j = 0; j < count; j++) {
            boolVector.push_back(value);
        }
    }
    return boolVector;
}











// Fonction qui écrit un vecteur de nombres entiers dans un fichier binaire
void writeIntVectorToFile(const vector<int>& intVector, const string& filename) {
    ofstream outFile(filename, ios::binary);
    if (outFile) {
        outFile.write(reinterpret_cast<const char*>(intVector.data()), intVector.size() * sizeof(int));
        outFile.close();
    } else {
        cerr << "Unable to open file: " << filename << endl;
    }
}


// Fonction qui lit un vecteur de nombres entiers à partir d'un fichier binaire
vector<int> readIntVectorFromFile(const string& filename) {
    vector<int> intVector;
    ifstream inFile(filename, ios::binary);
    if (inFile) {
        inFile.seekg(0, ios::end);
        int fileSize = inFile.tellg();
        inFile.seekg(0, ios::beg);
        intVector.resize(fileSize / sizeof(int));
        inFile.read(reinterpret_cast<char*>(intVector.data()), fileSize);
        inFile.close();
    } else {
        cerr << "Unable to open file: " << filename << endl;
    }
    return intVector;
}


const int ROWS = 360;
const int COLS = 180;
// Fonction qui écrit une  matrice de nombres entiers dans un fichier binaire
void save_matrix(int matrix[ROWS][COLS], string filename) {
    ofstream file(filename);
    if (file.is_open()) {
        for (int i = 0; i < ROWS; i++) {
            for (int j = 0; j < COLS; j++) {
                file << matrix[i][j] << " ";
            }
            file << endl;
        }
        file.close();
    }
    else {
        cout << "Unable to open file " << filename << endl;
    }
}


//la meme fonction qui lit le fichier
void load_matrix(int matrix[ROWS][COLS], string filename) {
    ifstream file(filename);

    if (file.is_open()) {
        for (int i = 0; i < ROWS; i++) {
            for (int j = 0; j < COLS; j++) {
                file >> matrix[i][j];
            }
        }
        file.close();
    }
    else {
        cout << "Unable to open file " << filename << endl;
    }
}

template<typename T>
std::size_t rangValeurSuperieure(const std::vector<T>& vect, const T& valeur) {
    auto it = std::upper_bound(vect.begin(), vect.end(), valeur);
    return std::distance(vect.begin(), it);
}

template<typename T>
std::size_t rangValeurInferieure(const std::vector<T>& vect, const T& valeur) {
    auto it = std::lower_bound(vect.begin(), vect.end(), valeur);
    return std::distance(vect.begin(), it);
}


//retourne lenom du fichier complet correspondant a une lat et une lon donnée
std::string filenamecarto (double lat,double lon)
{
    int lonint=floor(lon);
    int latint=ceil(lat);

    std::string stlon=std::to_string(lonint);
    std::string stlat=std::to_string(latint);
    std::string path="/home/jp/carto/"+stlat+"/";

    return path+"1_"+stlon+"_"+stlat+".deg";

}

std::string filenamecarto ( int lat, int lon)
{
   
    std::string stlon=std::to_string(lon);
    std::string stlat=std::to_string(lat);
    std::string path="/home/jp/carto/"+stlat+"/";

    return path+"1_"+stlon+"_"+stlat+".deg";

}


#endif // FONCTIONS_JP1_HPP_INCLUDED