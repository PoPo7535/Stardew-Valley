#pragma once
#include "Config.h"
#include "GameObject.h"
class ObjectRenderManager : public Singleton<ObjectRenderManager>
{
private:
	//priority_queue<GameObject*, vector<GameObject*>, compare> objectQueue;
	vector<GameObject*> objectVector;
	queue<GameObject*> objectQueue;


public:
	void Init() {}
	void PushObjectVector(GameObject* obj);
	void DeleteObjectVector();
	void DeleteObject(GameObject* obj);
	void ObjectRender(HDC hdc);
	void VectorClear();
	void Release();
};

