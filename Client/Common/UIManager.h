#pragma once
class UIManager
{
	DECLARE_SINGLETON(UIManager)
public:
	UIManager();
	~UIManager();
public:
	void CreateMainUI();
private:
	GameObject* m_hpBar;
	GameObject* m_energyBar;
	GameObject* m_enduranceBar;
};

