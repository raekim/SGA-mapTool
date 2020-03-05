#pragma once
class Map
{
private:
	Sprite*			m_pBackground;

public:
	Map();
	~Map();

	void Render();

	float GetWidth() { return m_pBackground->GetWidth(); }
	float GetHeight() { return m_pBackground->GetHeight(); }
};

