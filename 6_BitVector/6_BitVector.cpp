// 6_BitVector.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//

#include <iostream>
#include "Bitvector.h"
#include <fstream>

Bitvector playerStatus = Bitvector(20);

void parseStatusBits() {
    //interpretar cada bit
    std::cout << "Tiene posion de agua? " << translateBool(playerStatus[0]) << "\n";
    std::cout << "Tiene posion de fuego?" << translateBool(playerStatus[1]) << "\n";
    std::cout << "Tiene posion de aire?" << translateBool(playerStatus[2]) << "\n";
    std::cout << "Tiene posion de curacion?" << translateBool(playerStatus[3]) << "\n";
    std::cout << "Tiene posion de oscuridad?" << translateBool(playerStatus[4]) << "\n";
}

const char* translateBool(bool b) {
    b ? "SI" : "NO";
}

//leer archivo "dejuego"
void readSaveFile() {

    //primero, leer 20 bits de estado
    std::ifstream savefile;
    savefile.open("save/datamine");

    if (savefile.is_open()) {

        //determinar tamaño del archivo
        savefile.seekg(0, savefile.end);
        int filesize = savefile.tellg();
        std::cout << "file size " << filesize << "\n";

        if (filesize > 0) {

            savefile.seekg(0, savefile.beg);

            //buffer de 3 bytes para almacenar temporalmente los 20 bits
            char* buffer = new char [3];
            savefile.read((char*)buffer, 3);

            //imprimir valores en binario (para debug)
            for (int j = 0; j < 3; j++) {

                std::cout << "0b";

                for (int i = 7; i >= 0; i--) {
                    uint32 b = (buffer[i] >> j) & 1;
                    std::cout << (b ? "1" : "0");

                }

                std::cout << std::endl;
            }

            //convertir el buffer a bitvector
            uint32 data = 0;
            data = (uint32)buffer[0] << 24; 
            data |= ((uint32)buffer[1] << 16);
            uint32 b= ((uint32)buffer[2] << 8);
            playerStatus.setbank(data, 0);
            playerStatus.binaryprint();

            //invertir el orden de los bits
            Bitvector temp = Bitvector(playerStatus); 
            temp.binaryprint("temp");
            for (int i = 31; i >= 0; i--) {
                bool b = playerStatus.getval(i);
                std::cout << "val " << (temp.getval(i)!=0 ? "1" : "0") << "\n";
                playerStatus.setval(temp.getval(i), 31 - i);
            }

            playerStatus.binaryprint("playerstatus");

            //interpretar los bits segun el protocolo diseñado
            parseStatusBits();
            savefile.close();

            //interpretar res X
            savefile.seekg(4);
            int* resx = new int;
            *resx = 9999;
            std::cout << "pos = " << savefile.tellg() << "/n";
            savefile.read((char*)resx, 4);

            std::cout << "resx = " << *resx << "/n";
            std::cout << "pos = " << savefile.tellg() << "/n";

            //interpretar res y
            int* resy = new int;
            savefile.read((char*)resy, 4);
            std::cout << "resy = " << *resy << "/n";
        }
    }
    else puts("no datamine :(");
    return;
}

typedef char byte;

int main() {

    //Bitvector *misbits = new Bitvector(65);
    Bitvector misbits(65);

    std::cout << "se pidieron 34 bits, se otorga " << misbits.getsize() << "\n";
    /*
    misbits.binaryprint();
    misbits.setval(1, 0);
    misbits.setval(0, 1);
    misbits.setval(1, 2);
    misbits.setval(1, 3);
    //misbits->binaryprint();
    misbits.setval(1, 15);

    misbits.setval(0, 63);
    misbits.setval(1, 64);
    misbits.binaryprint();

    printf("valor de 63: %x \n", misbits[63]);
    */

    misbits.binaryprint();

    //Guardar a memoria presistente
    std::fstream savefile;
    savefile.open("datastore\\data.bin", std::fstream::out | std::fstream::binary);

    if (savefile.is_open()) {
        savefile.write((const char*)&misbits, 4);
        char* buffer = new char[1];
        *buffer = 0;

        savefile.close();
    }
    else {
        std::cout << "savefile not found\n";
    }

    //prueba de lectura de archivo binario
    readSaveFile();

    system("pause");
    return 0;
}

