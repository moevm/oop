#pragma once
#include <iostream>
#include "Unit.h"
enum landscape { Mountain = 1, Lake = 2, Forest = 3, Sunflower = 5};


//������� � ������ ������: ���� - ����, ����� - �����, ���� - ����, ������ � ���� - ����
//����� � �����: 
//������ � �����: 
//��������: ���� �����������, ������� �������� ������, ��� ���, �����, ����

//�����		����	����	�����	����
//+:		����	�����	�����	�����
//0:		����	�����	�����	�����
//-:		����	�����	�����	�����
class biome {
protected:
	char icon;
	int color;
	int background;

public:
	biome();
	int get_color();
	int get_background();
	char get_icon();
	int get_effect(unit* uni);
};

class sunflower:public biome {
public:
	sunflower();
};

class lake :public biome {
public:
	lake();
};

class forest :public biome {
public:
	forest();
};

class mountain :public biome {
public:
	mountain();
};