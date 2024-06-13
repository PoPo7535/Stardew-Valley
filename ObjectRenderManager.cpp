#include "ObjectRenderManager.h"

void ObjectRenderManager::PushObjectVector(GameObject* obj)
{
	// �迭�� �ֱ� ���� ���͸� ��ȸ�ϸ� ��
	for (vector<GameObject*>::iterator iter = objectVector.begin();
		iter != objectVector.end(); ++iter)
	{	// �̹� �ڱ� �ڽ��� �� �ִٸ� �Լ� ����
		if ((*iter) == obj)
		{
			cout << "ObjectRenderManager::PushObjectQueue : �̹� ���Ϳ� ���� ������Ʈ�� ����" << "\n";
			return;
		}	
	}

	// ���Ϳ� �������� ������Ʈ�� �߰�
	objectVector.push_back(obj);
}

void ObjectRenderManager::DeleteObjectVector()
{
	while (objectQueue.empty() == false)
	{
		// ���͸� ��ȸ�ϸ� ����
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

	// ���͸� ����
	sort(objectVector.begin(), objectVector.end(),
		[](const GameObject* a, const GameObject* b)
		{
			return a->GetPosY() < b->GetPosY();
		});

	// ���͸� ��ȸ�ϸ� ����
	for (vector<GameObject*>::iterator iter = objectVector.begin();
		iter != objectVector.end(); 
		++iter)
	{	
		(*iter)->Render(hdc);
	}
}

void ObjectRenderManager::VectorClear()
{
	// ���� Ŭ����
	for (vector<GameObject*>::iterator iter = objectVector.begin();
		iter != objectVector.end();)
	{	// ���͸� ��ȸ�ϸ� ����
		iter = objectVector.erase(iter);
	}
	objectVector.clear();
}

void ObjectRenderManager::Release()
{
	VectorClear();
	ReleaseSingleton();
}

