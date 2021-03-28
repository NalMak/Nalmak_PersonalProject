#pragma once
class MainGame
{
public:
	MainGame();
	~MainGame();

private:
	void ApplicationSetting();
	void SystemSetting();
public:
	int Run();
	class Core* m_engine;
};

