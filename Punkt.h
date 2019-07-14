#ifndef PUNKT
#define PUNKT
#include <iostream>

class Punkt {
public:
	int X;
	int Y;
	Punkt(int x = 1, int y = 1);
	bool operator==(const Punkt& PointToCompare);
	bool operator!=(const Punkt& PointToCompare);
	bool operator<(const Punkt& PointToCompare);
	bool operator>(const Punkt& PointToCompare);
    Punkt operator+(const Punkt& PointToCompare);
	Punkt operator-(const Punkt& PointToCompare);
	Punkt& operator+=(const Punkt& PointToCompare);
	Punkt& operator-=(const Punkt& PointToCompare);
	Punkt operator*(int ScaleFactor);
	Punkt operator/(int ScaleFactor);
	Punkt& operator*=(int ScaleFactor);
	Punkt& operator/=(int ScaleFactor);
};

Punkt::Punkt(int x, int y) {
	X = x;
	Y = y;
}

bool Punkt::operator==(const Punkt& PointToCompare) {
	if (X == PointToCompare.X && Y == PointToCompare.Y) {
		return true;
	}
	else return false;
}
bool Punkt::operator!=(const Punkt& PointToCompare) {
	if (X != PointToCompare.X || Y != PointToCompare.Y){
		return true;
		}
	else return false;
}
bool Punkt::operator<(const Punkt& PointToCompare) {
	if (X < PointToCompare.X && Y < PointToCompare.Y) {
		return true;
	}
	else return false;
}
bool Punkt::operator>(const Punkt& PointToCompare) {
	if (X > PointToCompare.X && Y > PointToCompare.Y) {
		return true;
	}
	else return false;
}

Punkt Punkt::operator+(const Punkt& PointToCompare) {
	Punkt * temp = new Punkt;
	temp->X = X + PointToCompare.X;
	temp->Y = Y + PointToCompare.Y;
	return *temp;
}
Punkt Punkt::operator-(const Punkt& PointToCompare){
	Punkt * temp = new Punkt;
	temp->X = X - PointToCompare.X;
	temp->Y = Y - PointToCompare.Y;
	return *temp;
}
Punkt& Punkt::operator+=(const Punkt& PointToCompare) {
	X = X + PointToCompare.X;
	Y = Y + PointToCompare.Y;
	return (*this);
}
Punkt& Punkt::operator-=(const Punkt& PointToCompare) {
	X = X - PointToCompare.X;
	Y = Y - PointToCompare.Y;
	return (*this);
}
Punkt Punkt::operator*(int ScaleFactor) {
	Punkt * temp = new Punkt;
	temp->X = X * ScaleFactor;
	temp->Y = Y * ScaleFactor;
	return *temp;
}
Punkt Punkt::operator/(int ScaleFactor) {
	Punkt * temp =  new Punkt;
	temp->X = X / ScaleFactor;
	temp->Y = Y / ScaleFactor;
	return *temp;
}
Punkt& Punkt::operator*=(int ScaleFactor) {
	X = X * ScaleFactor;
	Y = Y * ScaleFactor;
	return *this;
}
Punkt& Punkt::operator/=(int ScaleFactor) {
	X = X / ScaleFactor;
	Y = Y / ScaleFactor;
	return *this;
}

#endif