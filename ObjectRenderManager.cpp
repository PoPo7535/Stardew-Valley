#include "ObjectRenderManager.h"

void ObjectRenderManager::PushObjectVector(GameObject* obj)
{
	// 배열에 넣기 전에 백터를 순회하며 비교
	for (vector<GameObject*>::iterator iter = objectVector.begin();
		iter != objectVector.end(); ++iter)
	{	// 이미 자기 자신이 들어가 있다면 함수 종료
		if ((*iter) == obj)
		{
			cout << "ObjectRenderManager::PushObjectQueue : 이미 벡터에 같은 오브젝트가 있음" << "\n";
			return;
		}	
	}

	// 백터에 렌더해줄 오브젝트를 추가
	objectVector.push_back(obj);
}

void ObjectRenderManager::DeleteObjectVector()
{
	while (objectQueue.empty() == false)
	{
		// 백터를 순회하며 삭제
		for (vector<GameObject*>::iterator iter = objectVector.begin();
			iter != objectVector.end(); ++iter)
		{
			if ((*iter) == objectQueue.front())
			{
				(*iter)->Release();
				objectVector.erase(iter);
				objectQueue.pop();
				break;
			}
		}
	}
}
void ObjectRenderManager::DeleteObject(GameObject* obj)
{
	objectQueue.push(obj);
}


void ObjectRenderManager::ObjectRender(HDC hdc)
{
	DeleteObjectVector();

	// 백터를 정렬
	sort(objectVector.begin(), objectVector.end(),
		[](const GameObject* a, const GameObject* b)
		{
			return a->GetPosY() < b->GetPosY();
		});

	// 백터를 순회하며 렌더
	for (vector<GameObject*>::iterator iter = objectVector.begin();
		iter != objectVector.end(); 
		++iter)
	{	
		(*iter)->Render(hdc);
	}
}

void ObjectRenderManager::VectorClear()
{
	// 백터 클리어
	for (vector<GameObject*>::iterator iter = objectVector.begin();
		iter != objectVector.end();)
	{	// 백터를 순회하며 삭제
		iter = objectVector.erase(iter);
	}
	objectVector.clear();
}

void ObjectRenderManager::Release()
{
	VectorClear();
	ReleaseSingleton();
}

