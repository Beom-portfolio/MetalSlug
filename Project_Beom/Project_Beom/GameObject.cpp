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

void GameObject::SetAngle(float angle)
{
	m_Angle = angle;
}

void GameObject::SetSpeed(float speed)
{
	m_Speed = speed;
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

void GameObject::SetRenderCheck(bool render)
{
	m_renderCheck = render;
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

void GameObject::SetFollowedObj(GameObject* obj)
{
	m_FollowedObj = obj;
}

bool GameObject::LoadPixelCollider(const char* pFilePath, unsigned char r, unsigned char g, unsigned char b)
{
	if (nullptr != m_PixelInfo)
	{
		m_PixelInfo->vecPixel.clear();

		delete m_PixelInfo;
		m_PixelInfo = nullptr;
	}

	m_PixelInfo = new PIXELCOLLIDERINFO;
	m_PixelInfo->CollPixel.r = r;
	m_PixelInfo->CollPixel.g = g;
	m_PixelInfo->CollPixel.b = b;

	FILE* pFile = NULL;

	fopen_s(&pFile, pFilePath, "rb");

	if (pFile)
	{
		// File Header�� Info Header ����
		// ��Ʈ�� ���� ��ü�� ���� ������ ������.
		BITMAPFILEHEADER	fh = {};
		// ũ��(���� ��, ���� ����)�� ���� ���� � ���� ������ ������.
		BITMAPINFOHEADER	ih = {};

		// ���� ��ü�� ������ �д´�.
		fread(&fh, sizeof(fh), 1, pFile);
		// ��Ʈ���� �ƴϸ� �����Ѵ�.
		if (fh.bfType != 0x4d42)
		{
			fclose(pFile);
			return false;
		}

		fread(&ih, sizeof(ih), 1, pFile);
		// 24��Ʈ���� üũ, ���� �ȵǾ� �ִ��� üũ
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

		// Ȯ�ο�
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
	POSITION CamPos = GET_MANAGER<CameraManager>()->GetPos();

	if (true == m_isNoScroll)
	{
		ZeroMemory(&CamPos, sizeof(POSITION));
	}

	m_TotalPos = POSITION{ m_Info.Pos_X + CamPos.X , m_Info.Pos_Y + CamPos.Y };

	// ������Ʈ ������ �������� Rect ������ �����Ѵ�.
	m_Rect.left = (int)m_TotalPos.X - m_Info.Size_X / 2;
	m_Rect.top = (int)m_TotalPos.Y - m_Info.Size_Y / 2;
	m_Rect.right = (int)m_TotalPos.X + m_Info.Size_X / 2;
	m_Rect.bottom = (int)m_TotalPos.Y + m_Info.Size_Y / 2;

	// Collide Rect ������ �����Ѵ�.
	m_CollideRect.left = (int)(m_TotalPos.X + m_CollideInfo.Pos_X) - m_CollideInfo.Size_X / 2;
	m_CollideRect.top = (int)(m_TotalPos.Y + m_CollideInfo.Pos_Y) - m_CollideInfo.Size_Y / 2;
	m_CollideRect.right = (int)(m_TotalPos.X + m_CollideInfo.Pos_X) + m_CollideInfo.Size_X / 2;
	m_CollideRect.bottom = (int)(m_TotalPos.Y + m_CollideInfo.Pos_Y) + m_CollideInfo.Size_Y / 2;

	return 0;
}

void GameObject::CollisionActivate(GameObject* collideTarget)
{
}

void GameObject::CollisionDeactivate(GameObject* collideTarget)
{
}

void GameObject::CollisionPixelPart(DIRECTION dir, GameObject* PixelTarget)
{
}