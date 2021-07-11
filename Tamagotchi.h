#ifndef TAMAGOTCHI_H
#define TAMAGOTCHI_H

#include <string>

using std::string;

class Tamagotchi
{
public:
	Tamagotchi(); // ����������� ��������� ���������
	
	void Feed();
	void Play();
	void Sleep();
	
	bool IsAlive() { return _isAlive; }// get - �-��� � ��������� (��� ��)
	
	string GetMsg(); // �-��� ��������� msg �� �������
	
	//����������� �������� �� ���������� (health, hungry, tiredness):
	int GetHealth() { return _health; }
	int GetHungry() { return _hungry; }
	int GetTiredness() { return _tiredness; }

private:
	int _health,
		_hungry,
		_tiredness;

	int _action_counter; // ������� ���������� ��������
	bool _isAlive; // ��� �� 

	string _msg; // ����� ��������� �� �������
	bool _isRead; // ��������� �� ��������� �� ������

	enum LAST_ACTION // ��������� ����������� ��������
	{
		NONE,
		FEED,
		PLAY,
		SLEEP
	} _last_action;

	void SetMsg(string text_msg); // ��������� �� �������
	
	void UpdateAfterAction(); // �������� �� �������
};

#endif

