#include "DXUT.h"
#include "cMaskBg.h"
#include "GSystem.h"

extern GSystem* Active_GSystem;

extern int Stage;

cMaskBg::cMaskBg()
{

}

cMaskBg::~cMaskBg()
{

}

void cMaskBg::NEW()
{
	
	MaskBg_Sc = gameObject->Add_Component<SpriteRenderer_Component>(L"MaskBg_Sc");
    switch (Stage)
    {
    case 1:
        MaskBg_Sc->Load_Texture(L"Stage1/MaskBg.png", 1, 1, true);
        break;
    case 2:
        MaskBg_Sc->Load_Texture(L"Stage2/MaskBg.png", 1, 1, true);
        break;
    case 3:
        MaskBg_Sc->Load_Texture(L"Stage3/MaskBg.png", 1, 1, true);
        break;
    }


    MaskBg_Sc->Backup();

	MaskBg_Sc->Lock_Check();
	gameObject->Render_Stack = 2;
	gameObject->transform.Set_LocalPosition((WISIZE_X - MaskBg_Sc->Gtex->width) / 2, (WISIZE_Y - MaskBg_Sc->Gtex->height) / 2, 0);

    ingame_gameobject = Active_GSystem->Find(L"Ingame");
    ingame_memmap = ingame_gameobject->Get_Component<MeMMap_Component>(L"Ingame_MeMMap");

    //MaskBg_Sc->ImageToTexture();
    //MaskBg_Sc->UpdateTexture();
}

void cMaskBg::Awake()
{

}

void cMaskBg::Start()
{

}

void cMaskBg::Notice(Notice_Item* notice)
{


}

void cMaskBg::UpdateMaskTexture()
{
    //D3DLOCKED_RECT LockRect;

    //MaskBg_Sc->Gtex->tex->LockRect(0, &LockRect, 0, D3DLOCK_DISCARD);

    //DWORD* pColor = (DWORD*)LockRect.pBits;
    //int width = LockRect.Pitch / 4;

    //for (int y = 0; y < PLAYG_HEIGHT; y++)
    //{
    //    for (int x = 0; x < PLAYG_WIDTH; x++)
    //    {
    //        int nIdx = y * width + x;
    //        int miIdx = y * PLAYG_WIDTH + x;

    //        D3DXCOLOR xclr = pColor[nIdx];

    //        if (ingame_memmap->GetGap<char>(x, y) == (char)AREA::CLEAR)
    //        {
    //            xclr.a = 0;
    //        }
    //        else if (ingame_memmap->GetGap<char>(x, y) == (char)AREA::OUTLINE)
    //        {
    //            xclr.g = 1;
    //            xclr.r = 0;
    //            xclr.b = 0;
    //            xclr.a = 1.0f;
    //        }
    //        else
    //        {
    //            xclr.a = 1;
    //        }
    //        //pColor[nIdx] = 0x80FFFFFF;
    //        pColor[nIdx] = xclr;
    //    }
    //}

    //MaskBg_Sc->Gtex->tex->UnlockRect(0);
}

void cMaskBg::Update()
{
   /* if (IsMaskUpdate)
    {
        UpdateMaskTexture();
        GLog(L"마스크 업데이트");
    }*/
}

void cMaskBg::Late_Update()
{

}

void cMaskBg::Final_Update()
{

}

void cMaskBg::Render()
{

}

void cMaskBg::Reload()
{

}

void cMaskBg::Change()
{

}

void cMaskBg::Release()
{
	delete this;
}
