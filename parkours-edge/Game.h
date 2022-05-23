#pragma once
#include "SDL2/SDL.h"
#include "SDL2/SDL_mixer.h"
#include <unordered_map>
#include <string>
#include <vector>
#include "Math.h"
#include <queue>

class Game
{
public:
	Game();
	bool Initialize();
	void RunLoop();
	void Shutdown();

	void addActor(class Actor* actor);
	void removeActor(class Actor* actor);

	Mix_Chunk* GetSound(const std::string& fileName);

	class Renderer* GetRenderer() {	return mRenderer; }
    
    class Player* getPlayer(){return mPlayer;}
    void savePlayer(class Player* player){mPlayer = player;}
    
    void addBlock(class Actor* block);
    void removeBlock(class Actor* block);
    std::vector<Actor*> getBlocks(){return mBlocks;}
    
    std::queue<class Checkpoint*> getCheckpoints(){return mCheckpoints;}
    void addCheckpoint(class Checkpoint*);
    bool removeCheckpoint();
    
    bool LevelSet(){if (mNextLevel.size() == 0){return false;}return true;}
    void setLevel(std::string level){mNextLevel = level;}
    
    void AddCoin(){mCoinNum++;newCoin = true;}
    float GetTime(){return mTime;}
    void SetTime(float f){mTime = f;}
    
    int GetCoin(){return mCoinNum;}
    
    bool GetNewCoin(){return newCoin;}
    void SetNewCoin(bool b){newCoin = b;}
    
    void LoadNextLevel();
    
    const float WINDOW_WIDTH = 1024.0f;
    const float WINDOW_HEIGHT = 768.0f;
    
    float GetCheckTime(){return CheckTime;}
    void SetCheckTime(float f){CheckTime = f;}
    
    void addSecCams(class SecurityCamera* s);
    void removeSecCams(class SecurityCamera* s);
    std::vector<class SecurityCamera*> GetSecCams(){return mSecurityCameras;}
    
private:
	void ProcessInput();
	void UpdateGame();
	void GenerateOutput();
	void LoadData();
	void UnloadData();

	std::unordered_map<std::string, Mix_Chunk*> mSounds;

	// All the actors in the game
	std::vector<class Actor*> mActors;

	class Renderer* mRenderer = nullptr;
    
    class Player* mPlayer;
    
    std::vector<Actor*> mBlocks;

	Uint32 mTicksCount = 0;
	bool mIsRunning;
    
    std::queue<class Checkpoint*> mCheckpoints;
    
    std::string mNextLevel = "";
    
    float mTime;
    int mCoinNum = 0;
    bool newCoin = false;
    float CheckTime = 0.0f;
    
    std::vector<class SecurityCamera*> mSecurityCameras;
};
