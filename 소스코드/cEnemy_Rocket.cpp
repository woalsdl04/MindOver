#include "DXUT.h"
#include "cEnemy_Rocket.h"
#include "GSystem.h"

extern GSystem* Active_GSystem;
extern bool Hit_Check;

extern GameObject* Eff_Prefab;
extern GameObject* Boss12_Die_Eff_Prefab;
extern SoundCLIP_Component* Shoot_Sound;
cEnemy_Rocket::cEnemy_Rocket()
{

}

cEnemy_Rocket::~cEnemy_Rocket()
{

}

bool cEnemy_Rocket::Col_Check(GVec2<float> min, GVec2<float> max, AREA area)
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

void cEnemy_Rocket::NEW()
{
	ingame_gameobject = Active_GSystem->Find(L"Ingame");

	ingame_memmap = ingame_gameobject->Get_Component<MeMMap_Component>(L"Ingame_MeMMap");

	Player_gameobject = Active_GSystem->Find(L"Player");

	gameObject->Set_Center(true);
	gameObject->Render_Stack = 6;
	gameObject->transform.Set_LocalScale(0.3, 0.3, 0.3);
	Rocket_Boost = 120;
	
	J_time = WorldTime + 3000;
	//BulletSpeed = 200;
}

void cEnemy_Rocket::Awake()
{

}

void cEnemy_Rocket::Start()
{
	WorldTime = 0;
	Shoot_Sound->Play_Sound(false);
}

void cEnemy_Rocket::Notice(Notice_Item* notice)
{


}

void cEnemy_Rocket::Update()
{
	BulletSpeed += Rocket_Boost * DT;

	WorldTime += DT;

	if (BulletPos.y >= PLAYG_HEIGHT || BulletPos.y <= 0 || BulletPos.x <= 0 || BulletPos.x >= PLAYG_WIDTH || ingame_memmap->GetGap<char>(BulletPos.x, BulletPos.y) == (char)AREA::CLEAR)
	{
		//Active_GScene->Set_Camera_Action(CAMERA_ACTION_TYPE::EARTHQUAKE3, -0.025, 0.3, 10);
		Eff = Active_GSystem->Instantiate(Boss12_Die_Eff_Prefab);
		Eff->transform.Set_LocalScale(0.3, 0.3, 0.3);
		Eff->transform.Set_LocalPosition(BulletPos.x + PG_LEFT, BulletPos.y + PG_TOP, 0);
		Eff->Prefab = false;

		gameObject->Destroy = true;
	}

	if (Col_Check(GVec2<float>(BulletPos.x - 50, BulletPos.y - 30), GVec2<float>(BulletPos.x + 50, BulletPos.y + 30), AREA::ACTION))
	{
		Hit_Check = true;

		Eff = Active_GSystem->Instantiate(Boss12_Die_Eff_Prefab);
		Eff->transform.Set_LocalScale(0.3, 0.3, 0.3);
		Eff->transform.Set_LocalPosition(BulletPos.x + PG_LEFT, BulletPos.y + PG_TOP, 0);
		Eff->Prefab = false;

		gameObject->Destroy = true;
	}

	GVec3<float> cha = *Player_gameobject->transform.Get_LocalPosition() - *gameObject->transform.Get_LocalPosition();
	ang = Get_Degree2D(GVec2<float>(-1, 0), GVec2<float>(cha.x, cha.y));
	gameObject->transform.Set_LocalRotation(ang);

	float Judo = atan2(Player_gameobject->transform.Get_LocalPosition()->y - (BulletPos.y + PG_TOP), Player_gameobject->transform.Get_LocalPosition()->x - (BulletPos.x + PG_LEFT));

	if(WorldTime > 0.5)
	{
		BulletPos += GVec3<float>(cosf((Judo)), sinf((Judo)), 0) * BulletSpeed * DT;
	}
	else
	{
		BulletPos += GVec3<float>(cosf(D3DXToRadian(BulletRotate)), sinf(D3DXToRadian(BulletRotate)), 0) * BulletSpeed * DT;
	}
	
	gameObject->transform.Set_LocalPosition(BulletPos.x + PG_LEFT, BulletPos.y + PG_TOP, 0);
}

void cEnemy_Rocket::BulletSet(GVec3<float> _pos, float _speed, float _ang, bool _worldtime)
{
	BulletPos = _pos;
	BulletSpeed = _speed;
	BulletRotate = _ang;
	WorldTime = _worldtime;
}


void cEnemy_Rocket::Late_Update()
{

}

void cEnemy_Rocket::Final_Update()
{

}

void cEnemy_Rocket::Render()
{

}

void cEnemy_Rocket::Reload()
{

}

void cEnemy_Rocket::Change()
{

}

void cEnemy_Rocket::Release()
{
	delete this;
}
