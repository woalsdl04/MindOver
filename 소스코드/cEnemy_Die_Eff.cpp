#include "DXUT.h"
#include "cEnemy_Die_Eff.h"
#include "GSystem.h"

extern GSystem* Active_GSystem;
extern SoundCLIP_Component* Shoot_Sound;

cEnemy_Die_Eff::cEnemy_Die_Eff()
{

}

cEnemy_Die_Eff::~cEnemy_Die_Eff()
{

}

void cEnemy_Die_Eff::NEW()
{
	
}

void cEnemy_Die_Eff::Awake()
{

}

void cEnemy_Die_Eff::Start()
{
	Shoot_Sound->Play_Sound(false);
}

void cEnemy_Die_Eff::Notice(Notice_Item* notice)
{
	if (notice->Notice_Command == GNOTICE::ANI_END)
	{
		gameObject->Destroy = true;
	}
}

void cEnemy_Die_Eff::Update()
{

}

void cEnemy_Die_Eff::Late_Update()
{

}

void cEnemy_Die_Eff::Final_Update()
{

}

void cEnemy_Die_Eff::Render()
{

}

void cEnemy_Die_Eff::Reload()
{

}

void cEnemy_Die_Eff::Change()
{

}

void cEnemy_Die_Eff::Release()
{
	delete this;
}
