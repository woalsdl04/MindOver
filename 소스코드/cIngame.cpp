#include "DXUT.h"
#include "cIngame.h"
#include "GSystem.h"
#include "cPlayer.h"

extern GSystem* Active_GSystem;

DWORD LineColor = 0xFF00FFFF;

cIngame::cIngame()
{
	
}

cIngame::~cIngame()
{

}

void cIngame::NEW()
{
	Ingame_MeMMap = gameObject->Add_Component<MeMMap_Component>(L"Ingame_MeMMap");
	Ingame_AlphaMeMMap = gameObject->Add_Component<MeMMap_Component>(L"Ingame_AlphaMeMMap");
	Ingame_AlphaMeMMap->Init_Setup<char>(PLAYG_WIDTH, PLAYG_HEIGHT);
	Ingame_MeMMap->Init_Setup<char>(PLAYG_WIDTH, PLAYG_HEIGHT);
	Ingame_MeMMap->Rectangle(GVec2<int>(0, 0), GVec2<int>(PLAYG_WIDTH - 1, PLAYG_HEIGHT - 1), AREA::OUTLINE);

	Ingame_Line = gameObject->Add_Component<Line_Component>(L"Ingame_Line");
	Ingame_Line->Setup(10000, 3, true, 0xF0F0F0F0, 50, LineColor);
	gameObject->Render_Stack = 3;

	MaskBg_gameobject = Active_GSystem->Find(L"MaskBg");
	MaskBg_Sc = MaskBg_gameobject->Get_Component<SpriteRenderer_Component>();
	
	MeM2_MaskBg();


}

void cIngame::MeM2_MaskBg()
{
	for(int y = 0; y < PLAYG_HEIGHT; y++)
	{
		for (int x = 0; x < PLAYG_WIDTH; x++)
		{
			AREA Gap = (AREA)Ingame_MeMMap->GetGap<char>(x, y);

			switch(Gap)
			{
			case AREA::OUTLINE:
				MaskBg_Sc->Set_Pixel_Color(x, y, 0, 255, 255, 255);
				break;
			case AREA::CLEAR:
				MaskBg_Sc->Set_Pixel_Alpha(x, y, 0);
				break;
			}
		}
	}

	MaskBg_Sc->UpdateTexture();
}

void cIngame::Awake()
{

}

void cIngame::Start()
{

}

void cIngame::Notice(Notice_Item* notice)
{


}

void cIngame::Update()
{
	Ingame_Line->Color = LineColor;
}

void cIngame::Late_Update()
{

}

void cIngame::Final_Update()
{

}

void cIngame::Render()
{

}

void cIngame::Reload()
{

}

void cIngame::Change()
{

}

void cIngame::Release()
{
	delete this;
}
