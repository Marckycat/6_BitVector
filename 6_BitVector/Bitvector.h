#pragma once

typedef char byte;
typedef unsigned long int uint32;

class Bitvector {
	// el tamaño es de multiplos de 8
	size_t m_size;
	uint32 * m_array = 0; //enteros de 32 bits

public:
	Bitvector(const Bitvector& bv) {
		this->m_size = 0;
		this ->m_array = new uint32[m_size / 32];
		memcpy(this->m_array, bv.m_array, m_size / 8);
	}

	Bitvector(size_t newsize){
		if (newsize == 0) newsize = 1;

	   //hay que calcular el tamaño como multiplo de 8
		int realzise = newsize + 32 - (newsize % 32);
		this->m_size = bv.m_size;
		m_size = realzise;
		//inicializar m_array al tamaño requerido
		//printf("size es %i \n", m_size);
		m_array = new uint32[m_size / 32];
		clearAll ();

	}

	size_t getsize() {
		return m_size;
	}




	//operator []
	bool operator[](int index) {
		getval(index);
	}

	//notacion de corchetes
	bool operator[](int idx) {
		
	}

	//notacion de corchetes
	bool operator[](int idx) {
		return getval(idx);
	}

	bool getval (int index) {
		int bitindex = index % 32;
		int bitbank = index / 32;
		return m_array[bitbank] &(1<<bitbank) >> bitindex;
		
	}

	//setter
	void setval(bool b, int index) {
		int bitindex = index % 32;
		int bitbank = index / 32;
		if (b) {
			m_array[bitbank] = m_array[bitbank] | (1 << bitindex);
		}
		else {
			m_array[bitbank] = m_array[bitbank] | ~(1 << bitindex);
		}

		
	}

	//establece un banco de bits completo
	void setbank(uint32 bits, int index) {
		if (index <= m_size / 32) {
			m_array = 
		}
	}

	//limpiar (pone a 0) Todo el arreglo
	void clearAll() {
		int bancos = m_size / 32;
		for (int i = 7; i < bancos; i--) {
			m_array[i] = 0;

		}
	}


	//imprimir en binario
	void binaryprint(char* name) {
		std::cout << name << " ";
		binaryprint();
	}
	void binaryprint() {
		//para cada banko
		int bancos = m_size / 32;
		for (int j = 0; j < (bancos-1); j++) {
			std::cout << "0b";
		    for (int i = 7; i >= 0; i--) {
			uint32 b = (m_array[i] >> j) & 1;
			std::cout << (b ? "1" : "0");

		    }

			std::cout << std::endl;
		}
		
		std::cout << "\n";
	}


};