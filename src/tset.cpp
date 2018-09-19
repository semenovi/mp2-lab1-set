// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tset.cpp - Copyright (c) Гергель В.П. 04.10.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Множество - реализация через битовые поля
//
// implementation by madBearing 2018

#include "tset.h"

TSet::TSet(int mp) : BitField(mp)
{
	MaxPower = mp;
}

// конструктор копирования
TSet::TSet(const TSet &s) : BitField(s.MaxPower)
{
	MaxPower = s.MaxPower;
}

// конструктор преобразования типа
TSet::TSet(const TBitField &bf) : BitField(bf.GetLength())
{
	MaxPower = bf.GetLength();
	BitField = bf;
}

TSet::operator TBitField()
{
	TBitField out = BitField;
	return out;
}

int TSet::GetMaxPower(void) const // получить макс. к-во эл-тов
{
	return MaxPower;
}

int TSet::IsMember(const int Elem) const // элемент множества?
{
	if (Elem < 0) throw 0;
	if (Elem < MaxPower)
		return BitField.GetBit(Elem);
	return 0;
}

void TSet::InsElem(const int Elem) // включение элемента множества
{
	if (Elem < 0 || Elem > MaxPower) throw 0;
	BitField.SetBit(Elem);
}

void TSet::DelElem(const int Elem) // исключение элемента множества
{
	if (Elem < 0 || Elem > MaxPower) throw 0;
	BitField.ClrBit(Elem);
}

// теоретико-множественные операции

TSet& TSet::operator=(const TSet &s) // присваивание
{
	if (&s != this)
	{
		MaxPower = s.MaxPower;
		BitField = s.BitField;
	}
	return *this;
}

int TSet::operator==(const TSet &s) const // сравнение
{
	if (&s == this)
		return 1;
	if (MaxPower == s.MaxPower && BitField == s.BitField)
		return 1;
    return 0;
}

int TSet::operator!=(const TSet &s) const // сравнение
{
	if (*this == s)
		return 0;
	return 1;
}

TSet TSet::operator+(const TSet &s) // объединение
{
	int length = (MaxPower > s.MaxPower) ? MaxPower : s.MaxPower;
	TBitField out_bits(length);
	for (int i = 0; i < length; i++)
	{
		if (IsMember(i) || s.IsMember(i))
			out_bits.SetBit(i);
	}
	return TSet(out_bits);
}

TSet TSet::operator+(const int Elem) // объединение с элементом
{
	if (Elem > MaxPower || Elem < 0) throw 0;
	TBitField out_bits(MaxPower);
	for (int i = 0; i < MaxPower; i++)
	{
		if (IsMember(i) || i == Elem)
			out_bits.SetBit(i);
	}
	return TSet(out_bits);
}

TSet TSet::operator-(const int Elem) // разность с элементом
{
	if (Elem > MaxPower || Elem < 0) throw 0;
	TBitField out_bits(MaxPower);
	for (int i = 0; i < MaxPower; i++)
	{
		if (IsMember(i) && i != Elem)
			out_bits.SetBit(i);
	}
	return TSet(out_bits);
}

TSet TSet::operator*(const TSet &s) // пересечение
{
	int length = (MaxPower > s.MaxPower) ? MaxPower : s.MaxPower;
	TBitField out_bits(length);
	for (int i = 0; i < length; i++)
	{
		if (IsMember(i) && s.IsMember(i))
			out_bits.SetBit(i);
	}
	return TSet(out_bits);
}

TSet TSet::operator~(void) // дополнение
{
	TBitField out_bits(BitField);
	out_bits = ~out_bits;
	return TSet(out_bits);
}

// перегрузка ввода/вывода

istream &operator>>(istream &istr, TSet &s) // ввод
{
	cin >> s.BitField;
	return istr;
}

ostream& operator<<(ostream &ostr, const TSet &s) // вывод
{
	cout << s.BitField;
	return ostr;
}