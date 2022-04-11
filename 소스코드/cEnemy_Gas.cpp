#include "DXUT.h"
#include "cEnemy_Gas.h"
#include "GSystem.h"

extern GSystem* Active_GSystem;
extern bool Hit_Check;

extern SoundCLIP_Component* Shoot_Sound;

cEnemy_Gas::cEnemy_Gas()
{

}

cEnemy_Gas::~cEnemy_Gas()
{

}

bool cEnemy_Gas::Col_Check(GVec2<float> min, GVec2<float> max, AREA area)
{
	for (int i = min.y; i < max.y; i++)
	{
		for (int j = min.x; j < max.x; j++)
		{
			if (ingame_memmap->GetGap<char>(j, i) == (char)area)
			{
				return true;
			}
		}
	}

	return false;
}

void cEnemy_Gas::NEW()
{
	ingame_gameobject = Active_GSystem->Find(L"Ingame");

	ingame_memmap = ingame_gameobject->Get_Component<MeMMap_Component>(L"Ingame_MeMMap");

	
	gameObject->Set_Center(true);
	gameObject->Render_Stack = 6;
	BulletPos = { 0, 0, 0 };
}

void cEnemy_Gas::Awake()
{

}

void cEnemy_Gas::Start()
{
	Shoot_Sound->Play_Sound(false);
}

void cEnemy_Gas::Notice(Notice_Item* notice)
{
	if(notice->Notice_Command == GNOTICE::TRS_END)
	{
		gameObject->Destroy = true;
	}
}

void cEnemy_Gas::Update()
{
	if (Col_Check(GVec2<float>((BulletPos.x - 200), BulletPos.y - 200), GVec2<float>(BulletPos.x + 200, BulletPos.y + 200), AREA::ACTION))
	{
		Hit_Check = true;
	}


	gameObject->transform.Set_LocalPosition(BulletPos.x + PG_LEFT, BulletPos.y + PG_TOP, 0);
}

void cEnemy_Gas::BulletSet(GVec3<float> _pos)
{
	BulletPos = _pos;
}

void cEnemy_Gas::Late_Update()
{

}

void cEnemy_Gas::Final_Update()
{

}

void cEnemy_Gas::Render()
{

}

void cEnemy_Gas::Reload()
{

}

void cEnemy_Gas::Change()
{

}

void cEnemy_Gas::Release()
{
	delete this;
}
