#include "stdafx.h"

#include "Player.h"

Player::Player()
	: m_Id(-1),m_ConnectId(0),m_roomId(-1),m_PlayerState(PLAYERSTATE_NORAML),
	m_heartJitter(0),m_roomIndex(-1),m_level(0),m_Money(0),m_experience(0),
	m_totalbureau(0),m_successbureau(0),m_failbureau(0),m_successrate(0),m_runawayrate(0),
	m_PlayerType(PLAYERTYPE_NORMAL),m_isLookOn(false)
{

}

Player::Player(int id,int conid)
	: m_Id(id),m_ConnectId(conid),m_roomId(-1),m_PlayerState(PLAYERSTATE_NORAML),
	m_heartJitter(0),m_roomIndex(-1),m_level(0),m_Money(0),m_experience(0),
	m_totalbureau(0),m_successbureau(0),m_failbureau(0),m_successrate(0),m_runawayrate(0),
	m_PlayerType(PLAYERTYPE_NORMAL),m_isLookOn(false)
{

}

Player::~Player()
{

}