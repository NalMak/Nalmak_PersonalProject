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

private:
	void SetDamageFont();
	void CreateSkillIcon(const wstring& _texName, UINT _x, UINT _y);
private:
	Texture* m_damageFont[10];
	Texture* m_criticalDamageFont[10];
};

