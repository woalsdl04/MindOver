#include "DXUT.h"
#include "cBoss12_Die_Eff.h"
#include "GSystem.h"

extern GSystem* Active_GSystem;

extern SoundCLIP_Component* Explosion_Sound;

cBoss12_Die_Eff::cBoss12_Die_Eff()
{

}

cBoss12_Die_Eff::~cBoss12_Die_Eff()
{

}

void cBoss12_Die_Eff::NEW()
{

}

void cBoss12_Die_Eff::Awake()
{

}

void cBoss12_Die_Eff::Start()
{
	Explosion_Sound->Play_Sound(false);
}

void cBoss12_Die_Eff::Notice(Notice_Item* notice)
{
	if (notice->Notice_Command == GNOTICE::ANI_END)
	{
		gameObject->Destroy = true;
	}
}

void cBoss12_Die_Eff::Update()
{

}

void cBoss12_Die_Eff::Late_Update()
{

}

void cBoss12_Die_Eff::Final_Update()
{

}

void cBoss12_Die_Eff::Render()
{

}

void cBoss12_Die_Eff::Reload()
{

}

void cBoss12_Die_Eff::Change()
{

}

void cBoss12_Die_Eff::Release()
{
	delete this;
}
