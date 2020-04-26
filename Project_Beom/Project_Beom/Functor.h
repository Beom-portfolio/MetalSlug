#pragma once

class StringCmp
{
public:
	StringCmp(const TCHAR* pKey)
		: m_Key(pKey) {}

public:
	template <typename T>
	bool operator()(T& dst) // find_if의 단항 조건자.
	{
		return !lstrcmp(dst.first, m_Key);
	}

private:
	const TCHAR* m_Key;
};