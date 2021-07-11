#ifndef TAMAGOTCHI_H
#define TAMAGOTCHI_H

#include <string>

using std::string;

class Tamagotchi
{
public:
	Tamagotchi(); // конструктор начальных состояний
	
	void Feed();
	void Play();
	void Sleep();
	
	bool IsAlive() { return _isAlive; }// get - ф-ция о состоянии (жив ли)
	
	string GetMsg(); // ф-ция получения msg от питомца
	
	//возвращение значений по состояниям (health, hungry, tiredness):
	int GetHealth() { return _health; }
	int GetHungry() { return _hungry; }
	int GetTiredness() { return _tiredness; }

private:
	int _health,
		_hungry,
		_tiredness;

	int _action_counter; // счётчик повторений действий
	bool _isAlive; // жив ли 

	string _msg; // буфер сообщений от питомца
	bool _isRead; // прочитано ли сообщение из буфера

	enum LAST_ACTION // последнее совершённое действие
	{
		NONE,
		FEED,
		PLAY,
		SLEEP
	} _last_action;

	void SetMsg(string text_msg); // сообщение от питомца
	
	void UpdateAfterAction(); // проверка на границы
};

#endif

