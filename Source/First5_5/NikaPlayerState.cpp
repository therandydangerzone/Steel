// Fill out your copyright notice in the Description page of Project Settings.


#include "NikaPlayerState.h"

ANikaPlayerState::ANikaPlayerState()
{

	Kills;

}

float ANikaPlayerState::GetKills() const
{
	return Kills;
}

void ANikaPlayerState::AddKills(float Delta)
{

	if (!ensure(Delta > 0.0f))
	{
		return;
	}

	Kills += Delta;

	OnKillsChanged.Broadcast(this, Kills, Delta);

}

float ANikaPlayerState::KillCounter(float Delta)
{
	

	
	Kills += Delta;

	OnKillsChanged.Broadcast(this, Kills, Delta);

	return Kills;
}

bool ANikaPlayerState::RemoveKills(float Delta)
{
	return false;
}
