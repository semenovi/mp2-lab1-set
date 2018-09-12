// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tbitfield.cpp - Copyright (c) Гергель В.П. 07.05.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Битовое поле
//
// implementation by madBearing 2018

#include "tbitfield.h"

#ifdef MEM_DEBUG
int TBitField::mem_counter = 0;
#endif
const int BYTE_LENGTH = 8;

TBitField::TBitField(int len)
{
	if (len < 1) throw - 1;
	BitLen = len;
	MemLen = ((BitLen + (sizeof(TELEM) * BYTE_LENGTH) - 1)
		/ (sizeof(TELEM) * BYTE_LENGTH));
	//cout << sizeof(TELEM);
	pMem = new TELEM[MemLen];
#ifdef MEM_DEBUG
	mem_counter++;
	cout << "Bitfield with size " << BitLen
	<< " and count of blocks " << MemLen << " was created" << endl;
#endif
	for (int i = 0; i < MemLen; i++)
	{
		pMem[i] = 0;
	}
}

TBitField::TBitField(const TBitField &bf) // конструктор копирования
{
	//if (&bf == this) throw - 2;
	//delete[] pMem;
	BitLen = bf.BitLen;
	MemLen = bf.MemLen;
	pMem = new TELEM[MemLen];
#ifdef MEM_DEBUG
	mem_counter++;
	cout << "Bitfield with size " << BitLen
		<< " and count of blocks " << MemLen << " was created" << endl;
#endif
	for (int i = 0; i < MemLen; i++)
	{
		pMem[i] = bf.pMem[i];
	}
#ifdef DEBUG
	cout << "Bitfield was copied" << endl;
#endif
}

TBitField::~TBitField()
{
	delete [] pMem;
#ifdef MEM_DEBUG
	mem_counter--;
	cout << "Bitfield with size " << BitLen
		<< " and count of blocks " << MemLen << " was deleted" << endl;
#endif
}

int TBitField::GetMemIndex(const int n) const // индекс Мем для бита n
{
	if (n > BitLen) throw - 3;
	return (n / (int)(sizeof(TELEM) * BYTE_LENGTH));
}

TELEM TBitField::GetMemMask(const int n) const // битовая маска для бита n
{
	if (n > (sizeof(TELEM) * BYTE_LENGTH)) throw - 4;
	TELEM out = 0;
	TELEM in = 1;
	TELEM _n = n;
	out = out | (in << _n);
	return out;
}

// доступ к битам битового поля

int TBitField::GetLength(void) const // получить длину (к-во битов)
{
	return BitLen;
}

void TBitField::SetBit(const int n) // установить бит
{
	if (n > BitLen) throw - 3;
	int index_in_mem = GetMemIndex(n);
	TELEM mask = GetMemMask(n % (sizeof(TELEM) * BYTE_LENGTH));
	pMem[index_in_mem] |= mask;
#ifdef DEBUG
	cout << "Bit " << n << " was setted to 1" << endl;
#endif
	return;
}

void TBitField::ClrBit(const int n) // очистить бит
{
	if (n > BitLen) throw - 3;
	int index_in_mem = GetMemIndex(n);
	TELEM mask = GetMemMask(n % (sizeof(TELEM) * BYTE_LENGTH));
	pMem[index_in_mem] &= ~(mask);
#ifdef DEBUG
	cout << "Bit " << n << " was setted to 0" << endl;
#endif
	return;
}

int TBitField::GetBit(const int n) const // получить значение бита
{
	if (n > BitLen) throw - 3;
	int index_in_mem = GetMemIndex(n);
	TELEM mask = GetMemMask(n % (sizeof(TELEM) * BYTE_LENGTH));
#ifdef DEBUG
		cout << "Was received value of " << n << " bits: " << 1 << endl;
#endif
	return (pMem[index_in_mem] & (mask));
}

// битовые операции

TBitField& TBitField::operator=(const TBitField &bf) // присваивание
{
	if (&bf != this)
	{
		if (BitLen != bf.BitLen)
		{
			delete[] pMem;
#ifdef MEM_DEBUG
			mem_counter--;
			cout << "Bitfield with size " << BitLen
				<< " and count of blocks " << MemLen << " was deleted" << endl;
#endif
			BitLen = bf.BitLen;
			MemLen = bf.MemLen;
			pMem = new TELEM[MemLen];
		}
		for (int i = 0; i < MemLen; i++)
		{
			pMem[i] = bf.pMem[i];
		}
	}
	return *this;
}

int TBitField::operator==(const TBitField &bf) const // сравнение
{
	if (&bf == this)
	{
		return 1;
	}
	else if ((this->BitLen == bf.BitLen)
		&& (this->MemLen == bf.MemLen))
	{
		for (int i = 0; i < this->MemLen; i++)
		{
			if (this->pMem[i] != bf.pMem[i]) return 0;
		}
		return 1;
	}
	return 0;
}

int TBitField::operator!=(const TBitField &bf) const // сравнение
{
	if (*this == bf) return 0;
	return 1;
}

TBitField TBitField::operator|(const TBitField &bf) // операция "или"
{
	return *this;
}

TBitField TBitField::operator&(const TBitField &bf) // операция "и"
{
	return *this;
}

TBitField TBitField::operator~(void) // отрицание
{
	return *this;
}

// ввод/вывод
istream &operator>>(istream &istr, TBitField &bf) // ввод
{
	return istr;
}

ostream &operator<<(ostream &ostr, const TBitField &bf) // вывод
{
	const int BYTE_LENGTH = 8;
	for (int i = 0; i < bf.GetLength(); i++)
	{
		ostr << bf.GetBit(i);
	}
	return ostr;
}
