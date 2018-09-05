// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tbitfield.cpp - Copyright (c) Гергель В.П. 07.05.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Битовое поле
//
// implementation by madBearing 2018

#include "tbitfield.h"

TBitField::TBitField(int len)
{
	if (len < 1) throw - 1;
	const int BYTE_LENGTH = 8;
	this->BitLen = len;
	this->MemLen = (this->BitLen + sizeof(TELEM) * BYTE_LENGTH - 1)
		/ (sizeof(TELEM) * BYTE_LENGTH);
	this->pMem = new TELEM[MemLen];
}

TBitField::TBitField(const TBitField &bf) // конструктор копирования
{
	if (&bf == this) throw - 2;
	delete[] this->pMem;
	this->BitLen = bf.BitLen;
	this->MemLen = bf.MemLen;
	this->pMem = new TELEM[MemLen];
	for (int i = 0; i < this->MemLen; i++)
	{
		this->pMem[i] = bf.pMem[i];
	}
}

TBitField::~TBitField()
{
	if (pMem != nullptr)
	{
		delete[] pMem;
	}
}

int TBitField::GetMemIndex(const int n) const // индекс Мем для бита n
{
	if (n > this->BitLen) throw - 3;
	return n / sizeof(TELEM);
}

TELEM TBitField::GetMemMask(const int n) const // битовая маска для бита n
{
	if (n > sizeof(TELEM)) throw - 4;
	const TELEM zero = 0;
	return zero | (1 << n);
}

// доступ к битам битового поля

int TBitField::GetLength(void) const // получить длину (к-во битов)
{
	return this->BitLen;
}

void TBitField::SetBit(const int n) // установить бит
{
	if (n > this->BitLen) throw - 3;
	this->pMem[this->GetMemIndex(n)] |= 1 << (n % sizeof(TELEM));
	return;
}

void TBitField::ClrBit(const int n) // очистить бит
{
	if (n > this->BitLen) throw - 3;
	this->pMem[this->GetMemIndex(n)] &= ~(1<<(n % sizeof(TELEM)));
	return;
}

int TBitField::GetBit(const int n) const // получить значение бита
{
	if (n > this->BitLen) throw - 3;
	if ((pMem[this->GetMemIndex(n)] & (1 << (n % sizeof(TELEM)))) != 0)
	{
		return 1;
	}
	else
	{
		return 0;
	}
	return -1;
}

// битовые операции

TBitField& TBitField::operator=(const TBitField &bf) // присваивание
{
	if (&bf == this) throw - 2;
	delete[] this->pMem;
	this->BitLen = bf.BitLen;
	this->MemLen = bf.MemLen;
	this->pMem = new TELEM[MemLen];
	for (int i = 0; i < this->MemLen; i++)
	{
		this->pMem[i] = bf.pMem[i];
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
	if (this == &bf) return 0;
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
/*
istream &operator>>(istream &istr, TBitField &bf) // ввод
{
}

ostream &operator<<(ostream &ostr, const TBitField &bf) // вывод
{
}
*/