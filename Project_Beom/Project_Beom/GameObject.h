#pragma once

class GameObject
{
public:
	GameObject();
	virtual ~GameObject();

public:
	const GAMEOBJINFO& GetInfo() { return m_Info; }
	const GAMEOBJINFO& GetCollideInfo() { return m_CollideInfo; }
	const RECT& GetCollideRect() { return m_CollideRect; }
	const RECT& GetOriginCollideRect() { return m_OriginCollideRect; }
	const RENDERTYPE& GetRenderType() { return m_RenderType; }
	const bool& GetDeadCheck() { return m_isDead; }
	const bool& GetNotDeadCheck() { return m_isNotDead; }
	const bool& GetRenderCheck() { return m_renderCheck; }
	const bool& GetFallCheck() { return m_fallCheck; }
	const bool& GetCullingCheck() { return m_cullingCheck; }
	const bool& GetCollideCheck() { return m_isCollide; }
	const bool& GetCollideOnCheck() { return m_isCollideOn; }
	const float& GetAngle() { return m_Angle; }
	const float& GetSpeed() { return m_Speed; }
	const float& GetGravity() { return m_GravitySpeed; }
	const PIXELCOLLIDERINFO* GetPixelCollider() { return m_PixelInfo; }
	const SPRITEINFO& GetSpriteInfo() { return m_SpriteInfo; }
	const DIRECTION& GetDirection() { return m_Direction; }
	const OBJTYPE& GetObjectType() { return m_ObjType; }
	const POSITION GetPosition() { return POSITION{m_Info.Pos_X, m_Info.Pos_Y}; }
	const POSITION& GetTotalPosition() { return m_TotalPos; }
	const POSITION& GetOriginCollidePosition() { return m_OriginCollidePos; }

public:
	void SetPosition(float posX, float posY);
	void SetSize(int sizeWidth, int sizeHeight);
	void SetCollideInfo(const GAMEOBJINFO& info);
	void SetAngle(float angle);
	void SetSpeed(float speed);
	void SetDead(float state);
	void SetGravitySpeed(float gravitySpeed);
	void SetCollideOn(bool on);
	void SetFall(bool fall);
	void SetCulling(bool culling);
	void SetRenderCheck(bool render);
	void SetCollideCheck(bool collide);
	void SetSpriteInfo(SPRITEINFO spriteInfo);
	void SetObjectType(OBJTYPE type);
	void SetFollowedObj(GameObject* obj);
	void SetHypotenuse(float hypotenuse);

	virtual void SetDirection(DIRECTION dir);

public:
	bool LoadPixelCollider(const char* pFilePath,
		unsigned char r, unsigned char g, unsigned char b);

public:
	virtual bool Initialize() PURE;
	virtual int  Update(const float& TimeDelta);
	virtual void Render(HDC hdc) PURE;
	virtual void Release() PURE;
	virtual void CollisionActivate(GameObject* collideTarget);
	virtual void CollisionDeactivate(GameObject* collideTarget);
	virtual void CollisionPixelPart(DIRECTION dir, GameObject* PixelTarget);

protected:
	void GotoAngle(const float& TimeDelta);

protected:
	GAMEOBJINFO		m_Info;
	SPRITEINFO		m_SpriteInfo;
	RENDERTYPE		m_RenderType = RENDER_OBJ;
	DIRECTION		m_Direction = DIR_END;
	DWORD			m_Dir = 0;

	// Render
	PIXELCOLLIDERINFO* m_PixelInfo = nullptr;
	RECT				m_Rect;
	// Collider
	GAMEOBJINFO			m_CollideInfo;
	RECT				m_CollideRect;
	RECT				m_OriginCollideRect; // 카메라 좌표를 뺀
	POSITION			m_OriginCollidePos;

	OBJTYPE				m_ObjType = OBJ_END;

	bool			m_isNoScroll = false;
	bool			m_isDead = false;
	bool			m_isNotDead = false;
	bool			m_isCollideOn = true;
	bool			m_fallCheck = true;
	bool			m_renderCheck = true;
	bool			m_cullingCheck = false;
	bool			m_isCollide = false;

	// 회전
	float			m_Angle = 0.f;
	float			m_DeltaX = 0.f;
	float			m_DeltaY = 0.f;
	float			m_Hypotenuse = 1.f;

	float			m_Speed = 0.f;
	float			m_GravitySpeed = 0.f;
	float			m_GravityTime = 0.f;
	float			m_TimeStack = 0.f;

	int				m_Damage = 0;
	int				m_Hp = 0;
	POSITION        m_TotalPos;

	// 따라다녀야 할 오브젝트
	GameObject* m_FollowedObj = nullptr;
};
