#include "DXUT.h"
#include "cEnemy_BaseBullet.h"
#include "GSystem.h"
#include "cPlayer_Die_Eff.h"
#include "cEnemy_Die_Eff.h"

extern GSystem* Active_GSystem;
extern bool Hit_Check;
extern GameObject* Boss3_Die_Eff_Prefab;
extern SoundCLIP_Component* Shoot_Sound;

GameObject* Eff_Prefab = NULL;

cEnemy_BaseBullet::cEnemy_BaseBullet()
{

}

cEnemy_BaseBullet::~cEnemy_BaseBullet()
{

}

bool cEnemy_BaseBullet::Col_Check(GVec2<float> min, GVec2<float> max, AREA area)
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

void cEnemy_BaseBullet::NEW()
{
	ingame_gameobject = Active_GSystem->Find(L"Ingame");

	ingame_memmap = ingame_gameobject->Get_Component<MeMMap_Component>(L"Ingame_MeMMap");

	/*gameObject->Add_Component<SpriteRenderer_Component>(L"cEnemy_BaseBullet_Sc")->Load_Texture(L"Enemy_Bullet.png", 1, 1, false);
	gameObject->Get_Component<SpriteRenderer_Component>()->Lock_Check();*/
	Eff_Prefab = new GameObject(L"Eff_Prefab");
	Eff_Prefab->Set_Center(true);
	Eff_Prefab->Render_Stack = 6;
	Eff_Prefab->transform.Set_LocalScale(0.5f, 0.5f, 0.5f);
	Eff_Prefab->Add_Component<cEnemy_Die_Eff>(L"cEnemy_Die_Eff_Script");
	Enemy_Die_Eff_Sc = Eff_Prefab->Add_Component<SpriteRenderer_Component>(L"Enemy_Die_Eff_Sc");
	Enemy_Die_Eff_Sc->Load_Texture(L"Eff/Enemy_Die_Eff.png", 8, 1, false);
	Enemy_Die_Eff_Sc->Lock_Check();

	Enemy_Die_Eff_Ani = Eff_Prefab->Add_Component<FrameAni_Component>(L"Enemy_Die_Eff_Ani");
	Enemy_Die_Eff_Ani->Set_FrameTime(75, false);

	Eff_Prefab->Prefab = true;
}

void cEnemy_BaseBullet::Awake()
{

}

void cEnemy_BaseBullet::Start()
{

}

void cEnemy_BaseBullet::Notice(Notice_Item* notice)
{


}

void cEnemy_BaseBullet::Update()
{
	if (BulletPos.y >= PLAYG_HEIGHT || BulletPos.y <= 0 || BulletPos.x <= 0 || BulletPos.x >= PLAYG_WIDTH || ingame_memmap->GetGap<char>(BulletPos.x, BulletPos.y) == (char)AREA::CLEAR)
	{
		//Active_GScene->Set_Camera_Action(CAMERA_ACTION_TYPE::EARTHQUAKE3, -0.025, 0.3, 10);
		if(!IsStage3)
			Eff = Active_GSystem->Instantiate(Eff_Prefab);
		else
		{
			Eff = Active_GSystem->Instantiate(Boss3_Die_Eff_Prefab);
			Eff->transform.Set_LocalScale(0.3, 0.3, 0.3);
		}
		
		Eff->transform.Set_LocalPosition(BulletPos.x + PG_LEFT, BulletPos.y + PG_TOP, 0);
		Eff->Prefab = false;

		gameObject->Destroy = true;
	}
	
	if (Col_Check(GVec2<float>(BulletPos.x - 25, BulletPos.y - 25), GVec2<float>(BulletPos.x + 25, BulletPos.y + 25), AREA::ACTION))
	{
		Hit_Check = true;
	}

	if(IsRadian)
		BulletPos += GVec3<float>(cosf(D3DXToRadian(BulletRotate)), sinf(D3DXToRadian(BulletRotate)), 0) * BulletSpeed * DT;
	else
		BulletPos += GVec3<float>(cosf((BulletRotate)), sinf((BulletRotate)), 0) * BulletSpeed * DT;

	gameObject->transform.Set_LocalPosition(BulletPos.x + PG_LEFT, BulletPos.y + PG_TOP, 0);
}

void cEnemy_BaseBullet::BulletSet(GVec3<float> _pos, float _speed, float _ang, bool _isradian, bool _stage3)
{
	BulletPos = _pos;
	BulletSpeed = _speed;
	BulletRotate = _ang;
	IsRadian = _isradian;
	IsStage3 = _stage3;
}

void cEnemy_BaseBullet::Late_Update()
{

}

void cEnemy_BaseBullet::Final_Update()
{

}

void cEnemy_BaseBullet::Render()
{

}

void cEnemy_BaseBullet::Reload()
{

}

void cEnemy_BaseBullet::Change()
{

}

void cEnemy_BaseBullet::Release()
{
	delete this;
}
