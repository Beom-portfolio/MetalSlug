#include "pch.h"
#include "GameObject.h"

GameObject::GameObject()
{
	ZeroMemory(&m_Info, sizeof(GAMEOBJINFO));
	ZeroMemory(&m_Rect, sizeof(RECT));
	ZeroMemory(&m_SpriteInfo, sizeof(SPRITEINFO));
	ZeroMemory(&m_CollideInfo, sizeof(GAMEOBJINFO));
	ZeroMemory(&m_CollideRect, sizeof(RECT));
}


GameObject::~GameObject()
{
	if (nullptr != m_PixelInfo)
	{
		m_PixelInfo->vecPixel.clear();

		delete m_PixelInfo;
		m_PixelInfo = nullptr;
	}
}

void GameObject::SetPosition(float posX, float posY)
{
	m_Info.Pos_X = (float)posX;
	m_Info.Pos_Y = (float)posY;
}

void GameObject::SetSize(int sizeWidth, int sizeHeight)
{
	m_Info.Size_X = sizeWidth;
	m_Info.Size_Y = sizeHeight;
}

void GameObject::SetCollideInfo(const GAMEOBJINFO& info)
{
	m_CollideInfo = info;
}

void GameObject::SetAngle(float angle)
{
	m_Angle = angle;
	m_DeltaX = cosf(ToRadian(angle)) * m_Hypotenuse;
	m_DeltaY = -sinf(ToRadian(angle)) * m_Hypotenuse;
}

void GameObject::SetSpeed(float speed)
{
	m_Speed = speed;
}

void GameObject::SetDead(float state)
{
	m_isDead = state;
}

void GameObject::SetGravitySpeed(float gravitySpeed)
{
	m_GravitySpeed = gravitySpeed;
}

void GameObject::SetCollideOn(bool on)
{
	m_isCollideOn = on;
}

void GameObject::SetFall(bool fall)
{
	if (true == fall && false == m_fallCheck)
	{
		m_GravitySpeed = 0.f;
		m_GravityTime = 0.f;
		m_fallCheck = fall;
	}

	if (false == fall && true == m_fallCheck)
	{
		m_GravitySpeed = 0.f;
		m_GravityTime = 0.f;
		m_fallCheck = fall;
	}
}

void GameObject::SetCulling(bool culling)
{
	m_cullingCheck = culling;
}

void GameObject::SetRenderCheck(bool render)
{
	m_renderCheck = render;
}

void GameObject::SetCollideCheck(bool collide)
{
	m_isCollide = collide;
}

void GameObject::SetSpriteInfo(SPRITEINFO spriteInfo)
{
	m_SpriteInfo = spriteInfo;
}

void GameObject::SetDirection(DIRECTION dir)
{
	m_Direction = dir;
}

void GameObject::SetObjectType(OBJTYPE type)
{
	m_ObjType = type;
}

void GameObject::SetParentObj(GameObject* obj)
{
	m_ParentObj = obj;
}

void GameObject::SetHypotenuse(float hypotenuse)
{
	m_Hypotenuse = hypotenuse;
	SetAngle(m_Angle);
}

void GameObject::SetState(DWORD state)
{
	m_State = state;
}

void GameObject::Hit(int damage)
{
	m_Hp -= damage;
}

bool GameObject::LoadPixelCollider(const char* pFilePath, vector<PIXEL24> collpixels)
{
	if (nullptr != m_PixelInfo)
	{
		m_PixelInfo->vecPixel.clear();

		delete m_PixelInfo;
		m_PixelInfo = nullptr;
	}

	m_PixelInfo = new PIXELCOLLIDERINFO;
	m_PixelInfo->CollPixels = collpixels;

	FILE* pFile = NULL;

	fopen_s(&pFile, pFilePath, "rb");

	if (pFile)
	{
		// File Header와 Info Header 선언
		// 비트맵 파일 자체에 관한 정보를 가진다.
		BITMAPFILEHEADER	fh = {};
		// 크기(가로 폭, 세로 높이)와 색상 포맷 등에 관한 정보를 가진다.
		BITMAPINFOHEADER	ih = {};

		// 파일 자체의 정보를 읽는다.
		fread(&fh, sizeof(fh), 1, pFile);
		// 비트맵이 아니면 종료한다.
		if (fh.bfType != 0x4d42)
		{
			fclose(pFile);
			return false;
		}

		fread(&ih, sizeof(ih), 1, pFile);
		// 24비트인지 체크, 압축 안되어 있는지 체크
		if (ih.biBitCount != 24 || ih.biCompression != BI_RGB)
		{
			fclose(pFile);
			return false;
		}

		m_PixelInfo->Width = ih.biWidth;
		m_PixelInfo->Height = ih.biHeight;

		m_PixelInfo->vecPixel.clear();
		m_PixelInfo->vecPixel.resize(ih.biWidth * ih.biHeight);

		fread(&m_PixelInfo->vecPixel[0], sizeof(PIXEL24), m_PixelInfo->vecPixel.size(), pFile);

		PIXEL24* pixelArr = new PIXEL24[ih.biWidth];

		for (int i = 0; i < ih.biHeight / 2; ++i)
		{
			memcpy(pixelArr, &m_PixelInfo->vecPixel[i * ih.biWidth],
				sizeof(PIXEL24) * ih.biWidth);
			memcpy(&m_PixelInfo->vecPixel[i * ih.biWidth],
				&m_PixelInfo->vecPixel[(ih.biHeight - i - 1) * ih.biWidth],
				sizeof(PIXEL24) * ih.biWidth);
			memcpy(&m_PixelInfo->vecPixel[(ih.biHeight - i - 1) * ih.biWidth], 
				pixelArr, sizeof(PIXEL24) * ih.biWidth);
		}

		SAFE_DELETE_ARRAY(pixelArr);

		fclose(pFile);

		// 확인용
		/*fopen_s(&pFile, "test.bmp", "wb");
		ih.biHeight = -ih.biHeight;
		fwrite(&fh, sizeof(fh), 1, pFile);
		fwrite(&ih, sizeof(ih), 1, pFile);
		fwrite(&m_PixelInfo->vecPixel[0], sizeof(PIXEL24), m_PixelInfo->vecPixel.size(), pFile);
		fclose(pFile);*/

	}
	else
	{
		return false;
	}
	return true;
}

int GameObject::Update(const float& TimeDelta)
{
	m_TimeStack += TimeDelta;

	POSITION CamPos = GET_MANAGER<CameraManager>()->GetPos();

	if (m_isNoScroll)
		ZeroMemory(&CamPos, sizeof(POSITION));

	m_TotalPos = POSITION{ m_Info.Pos_X + CamPos.X , m_Info.Pos_Y + CamPos.Y };

	// 오브젝트 정보를 바탕으로 Rect 정보를 갱신한다.
	m_Rect.left = (int)m_TotalPos.X - m_Info.Size_X / 2;
	m_Rect.top = (int)m_TotalPos.Y - m_Info.Size_Y / 2;
	m_Rect.right = (int)m_TotalPos.X + m_Info.Size_X / 2;
	m_Rect.bottom = (int)m_TotalPos.Y + m_Info.Size_Y / 2;

	// Collide Rect 정보를 갱신한다.
	m_CollideRect.left = (int)(m_TotalPos.X + m_CollideInfo.Pos_X) - m_CollideInfo.Size_X / 2;
	m_CollideRect.top = (int)(m_TotalPos.Y + m_CollideInfo.Pos_Y) - m_CollideInfo.Size_Y / 2;
	m_CollideRect.right = (int)(m_TotalPos.X + m_CollideInfo.Pos_X) + m_CollideInfo.Size_X / 2;
	m_CollideRect.bottom = (int)(m_TotalPos.Y + m_CollideInfo.Pos_Y) + m_CollideInfo.Size_Y / 2;


	// 카메라 좌표 포함
	m_OriginCollideRect.left = (int)(m_Info.Pos_X + m_CollideInfo.Pos_X) - m_CollideInfo.Size_X / 2;
	m_OriginCollideRect.top = (int)(m_Info.Pos_Y + m_CollideInfo.Pos_Y) - m_CollideInfo.Size_Y / 2;
	m_OriginCollideRect.right = (int)(m_Info.Pos_X + m_CollideInfo.Pos_X) + m_CollideInfo.Size_X / 2;
	m_OriginCollideRect.bottom = (int)(m_Info.Pos_Y + m_CollideInfo.Pos_Y) + m_CollideInfo.Size_Y / 2;

	m_OriginCollidePos.X = m_Info.Pos_X + m_CollideInfo.Pos_X;
	m_OriginCollidePos.Y = m_Info.Pos_Y + m_CollideInfo.Pos_Y;

	if (m_GravitySpeed > 5000.f)
		m_isDead = true;

	return 0;
}

void GameObject::RenderAfter(HDC hdc)
{
}

void GameObject::CollisionActivate(GameObject* collideTarget)
{
}

void GameObject::CollisionDeactivate(GameObject* collideTarget)
{
}

void GameObject::CollisionPixelPart(DIRECTION dir, GameObject* PixelTarget, PIXEL24 collPixelColor)
{
}

void GameObject::GotoAngle(const float& TimeDelta)
{
	m_Info.Pos_X += m_DeltaX * m_Speed * TimeDelta;
	m_Info.Pos_Y += m_DeltaY * m_Speed * TimeDelta;
}
