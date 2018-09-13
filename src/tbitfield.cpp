// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tbitfield.cpp - Copyright (c) Гергель В.П. 07.05.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Битовое поле
//
// implementation by madBearing 2018

#include "tbitfield.h"

const int BYTE_LENGTH = 8;

TBitField::TBitField(int len)
{
	if (len < 1) throw - 1;
	BitLen = len;
	MemLen = ((BitLen + (sizeof(TELEM) * BYTE_LENGTH) - 1)
		/ (sizeof(TELEM) * BYTE_LENGTH));
	this->pMem = new TELEM[MemLen];
	for (int i = 0; i < MemLen; i++)
		pMem[i] = 0;
}

TBitField::TBitField(const TBitField &bf) // конструктор копирования
{
	BitLen = bf.BitLen;
	MemLen = bf.MemLen;
	this->pMem = new TELEM[MemLen];
	for (int i = 0; i < MemLen; i++)
		pMem[i] = bf.pMem[i];
}

TBitField::~TBitField()
{
	delete[] this->pMem;
}

int TBitField::GetMemIndex(const int n) const // индекс Мем для бита n
{
	if (n > BitLen || n < 0) throw - 3;
	return (n / (int)(sizeof(TELEM) * BYTE_LENGTH));
}

TELEM TBitField::GetMemMask(const int n) const // битовая маска для бита n
{
	if (n > (sizeof(TELEM) * BYTE_LENGTH) || n < 0) throw - 4;
	return (TELEM)0 | ((TELEM)1 << n);
}

// доступ к битам битового поля

int TBitField::GetLength(void) const // получить длину (к-во битов)
{
	return BitLen;
}

void TBitField::SetBit(const int n) // установить бит
{
	if (n > BitLen || n < 0) throw - 3;
	TELEM mask = GetMemMask(n % (sizeof(TELEM) * BYTE_LENGTH));
	pMem[GetMemIndex(n)] |= mask;
	return;
}

void TBitField::ClrBit(const int n) // очистить бит
{
	if (n > BitLen || n < 0) throw - 3;
	TELEM mask = GetMemMask(n % (sizeof(TELEM) * BYTE_LENGTH));
	pMem[GetMemIndex(n)] &= ~(mask);
	return;
}

int TBitField::GetBit(const int n) const // получить значение бита
{
	if (n > BitLen || n < 0) throw - 3;
	TELEM mask = GetMemMask(n % (sizeof(TELEM) * BYTE_LENGTH));
	return ((pMem[GetMemIndex(n)] & (mask)) > 0);
}

// битовые операции

TBitField& TBitField::operator=(const TBitField &bf) // присваивание
{
	if (&bf != this)
	{
		// если длины не совпадают, пересоздаем pMem
		if (BitLen != bf.BitLen)
		{
			BitLen = bf.BitLen;
			MemLen = bf.MemLen;
			delete[] this->pMem;
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
		return 1;
	if (BitLen == bf.BitLen)
	{
		for (int i = 0; i < MemLen; i++)
			if (pMem[i] != bf.pMem[i])
				return 0;
		return 1;
	}
	return 0;
}

int TBitField::operator!=(const TBitField &bf) const // сравнение
{
	if (*this == bf)
		return 0;
	return 1;
}

TBitField TBitField::operator|(const TBitField &bf) // операция "или"
{
	int length = (BitLen > bf.BitLen) ? BitLen : bf.BitLen;
	TBitField out(length);
	for (int i = 0; i < length; i++)
		if (GetBit(i) == 1 || bf.GetBit(i) == 1)
			out.SetBit(i);
	return out;
}

TBitField TBitField::operator&(const TBitField &bf) // операция "и"
{
	int length = (BitLen > bf.BitLen) ? BitLen : bf.BitLen;
	TBitField out(length);
	for (int i = 0; i < length; i++)
		if (GetBit(i) == 1 && bf.GetBit(i) == 1)
			out.SetBit(i);
		else
			out.ClrBit(i);
	for (int i = length; i < BitLen; i++)
		ClrBit(i);
	return out;
}

TBitField TBitField::operator~(void) // отрицание
{
	TBitField out(BitLen);
	for (int i = 0; i < BitLen; i++)
		if (GetBit(i))
			out.ClrBit(i);
		else
			out.SetBit(i);
	return out;
}

// ввод/вывод
istream &operator>>(istream &istr, TBitField &bf) // ввод
{
	int input = 0;
	cin >> input;
	bf.SetBit(input);
	return istr;
}

ostream &operator<<(ostream &ostr, const TBitField &bf) // вывод
{
	for (int i = 0; i < bf.GetLength(); i++)
	{
		if (bf.GetBit(i)) ostr << i <<" ";
	}
	ostr << "\n";
	return ostr;
}
