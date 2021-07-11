#include "Tamagotchi.h"

Tamagotchi::Tamagotchi()
{
	_health = 10;
	_hungry = 0;
	_tiredness = 0;
	
	_last_action = NONE;
	_action_counter = 0;

	_isAlive = true;
	_isRead = true;
}

void Tamagotchi::Feed()
{
	_action_counter++;

	if (_last_action == FEED && _action_counter > 2)
	{
		_health--;
		SetMsg("I am overeating! STOP!");
	}
	else if (_last_action != FEED)
	{
		_action_counter = 1;
		SetMsg("Mmm, it is so tasty : nom-nom!");
	}

	_hungry--;

	_last_action = FEED;
	UpdateAfterAction();
}

void Tamagotchi::Play()
{
	_action_counter++;

	if (_last_action == PLAY && _action_counter > 1)
	{
		_health--;
		SetMsg("I am bad, because I am really tired. Stop playing with me, please!");
	}
	else if (_last_action != PLAY)
	{
		_action_counter = 1;
		SetMsg("Yoohuu! Cool game :)");
	}

	_tiredness++;
	_hungry++;

	_last_action = PLAY;
	UpdateAfterAction();
}

void Tamagotchi::Sleep()
{
	if (_tiredness != 0)
	{
		_tiredness = 0;
		_health++;
		_hungry++;

		SetMsg("Thanks for the sleep. I'm probably cute when I sleep ^_^");

		_last_action = SLEEP;
		UpdateAfterAction();
	}
	else
		SetMsg("I don't want to sleep!");
}

string Tamagotchi::GetMsg()
{
	if (!_isRead)
	{
		_isRead = true;
		return _msg;
	}
	return string();
}

void Tamagotchi::SetMsg(string text_msg)
{
	_msg = text_msg;
	_isRead = false;
}

void Tamagotchi::UpdateAfterAction()
{
	if (_hungry < 0)
		_hungry = 0;
	if (_hungry > 10)
		_hungry = 10;
	if (_health > 10)
		_health = 10;

	if (_tiredness > 10)
	{
		_tiredness = 10;
		_health--;
	}

	// завершение игры, наступление смерти:
	if (_health <= 0)
	{
		_health = 0;
		_isAlive = false;

		SetMsg("You are a bad owner! I am dead...");
	}
}
