#include "DXUT.h"
#include "cSpeedUp_Item.h"
#include "GSystem.h"

extern GSystem* Active_GSystem;

extern float J_Speed;
extern SoundCLIP_Component* PowerUp_Sound;

cSpeedUp_Item::cSpeedUp_Item()
{

}

cSpeedUp_Item::~cSpeedUp_Item()
{

}

void cSpeedUp_Item::NEW()
{
	ingame_gameobject = Active_GSystem->Find(L"Ingame");

	ingame_memmap = ingame_gameobject->Get_Component<MeMMap_Component>(L"Ingame_MeMMap");

	SpeedUp_Item_Sc = gameObject->Add_Component<SpriteRenderer_Component>(L"SpeedUp_Item_Sc");
	SpeedUp_Item_Sc->Load_Texture(L"Item/SpeedUp.png", 1, 1, false);
	SpeedUp_Item_Sc->Lock_Check();

	gameObject->Set_Center(true);
	gameObject->Render_Stack = 3;
	gameObject->transform.Set_LocalScale(0.3, 0.3, 0.3);

	Sel = ITEMSTATE::START;
	Item_Pos = { 0, 0, 0 };
	WorldTime = timeGetTime();
	J_time = 0;
	SpeedUpPer = 200;
}

void cSpeedUp_Item::Awake()
{

}

void cSpeedUp_Item::Start()
{

}

void cSpeedUp_Item::Notice(Notice_Item* notice)
{
	
}

void cSpeedUp_Item::Update()
{
	//WorldTime = timeGetTime();

	switch (Sel)
	{
	case ITEMSTATE::START:
		Item_Pos = GVec3<float>(rand() % PLAYG_WIDTH, rand() % PLAYG_HEIGHT, 0);
		Sel = ITEMSTATE::DROP;
		break;
	case ITEMSTATE::DROP:
		if (ingame_memmap->GetGap<char>(Item_Pos.x, Item_Pos.y) == (char)AREA::CLEAR)
		{
			PowerUp_Sound->Play_Sound(false);
			Sel = ITEMSTATE::EAT;
		}
		break;
	case ITEMSTATE::EAT:
		J_Speed += SpeedUpPer;
		J_time = WorldTime + 3000;
		gameObject->Add_Component<Color_Component>(L"SpeedUp_Item_Cr")->Setup(GCOLOR(1, 1, 1, 1), GCOLOR(1, 1, 1, 0), -0.5f, COLOR_ACTIONTYPE::ONEWAY, 0xFFFFFFFF);
		gameObject->Add_Component<TRS_Component>(L"SpeedUp_Item_Trs")->Set_TRS(TRS_ENUM::SCALE, GVec3<float>(0.3, 0.3, 0.3), GVec3<float>(0.5, 0.5, 0.5), -0.5f, TRS_LOOPTYPE::ONEWAY, TRS_SPEEDTYPE::AVERAGE, 0, 0xFFFFFFFF);
		Sel = ITEMSTATE::ITEM_DIE;
		break;
	case ITEMSTATE::AFTER:
		if (J_time < WorldTime)
		{
			if (J_Speed > 300)
				J_Speed = J_Speed - SpeedUpPer;

			Sel = ITEMSTATE::ITEM_DIE;
		}
		break;
	case ITEMSTATE::ITEM_DIE:
		//gameObject->Destroy = true;
		break;
	}

	gameObject->transform.Set_LocalPosition(Item_Pos.x + PG_LEFT, Item_Pos.y + PG_TOP, 0);
}

void cSpeedUp_Item::Late_Update()
{

}

void cSpeedUp_Item::Final_Update()
{

}

void cSpeedUp_Item::Render()
{

}

void cSpeedUp_Item::Reload()
{

}

void cSpeedUp_Item::Change()
{

}

void cSpeedUp_Item::Release()
{
	delete this;
}
