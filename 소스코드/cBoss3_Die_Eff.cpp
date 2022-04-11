#include "DXUT.h"
#include "cBoss3_Die_Eff.h"
#include "GSystem.h"
#include "cBoss3_Die_Eff.h"

extern GSystem* Active_GSystem;

extern SoundCLIP_Component* Explosion_Sound;

cBoss3_Die_Eff::cBoss3_Die_Eff()
{

}

cBoss3_Die_Eff::~cBoss3_Die_Eff()
{

}

void cBoss3_Die_Eff::NEW()
{

}

void cBoss3_Die_Eff::Awake()
{

}

void cBoss3_Die_Eff::Start()
{
	Explosion_Sound->Play_Sound(false);
}

void cBoss3_Die_Eff::Notice(Notice_Item* notice)
{
	if (notice->Notice_Command == GNOTICE::ANI_END)
	{
		gameObject->Destroy = true;
	}
}

void cBoss3_Die_Eff::Update()
{

}

void cBoss3_Die_Eff::Late_Update()
{

}

void cBoss3_Die_Eff::Final_Update()
{

}

void cBoss3_Die_Eff::Render()
{

}

void cBoss3_Die_Eff::Reload()
{

}

void cBoss3_Die_Eff::Change()
{

}

void cBoss3_Die_Eff::Release()
{
	delete this;
}
