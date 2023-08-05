#pragma once
#include "hyResource.h"			// ��ο� �̸� �����صδ� Ŭ����

namespace hy
{
	class Resources
	{
	public:
		template <typename T>
		static T* Find(const std::wstring& name)		// �̹� �ε��� �̹����� �ִ��� ã�� �Լ�(�̹� �ε��� ���� �ٽ� �α��� �ʿ䰡 �����Ƿ�)
		{
			auto iter = mResources.find(name);			// auto : �ڷ����� �˾Ƽ� ������ �߷�����(�ڵ尡 ª������ ������ �� ���� ���� �ڷ������� �� �� ����)
			if (iter == mResources.end())
				return nullptr;							// ������ nullptr ��ȯ

			return dynamic_cast<T*>(iter->second);		// �������ڸ��� �ڽİɷ� ����ȯ�� ������->dynamic cast(�ڽĲ��� �ٲ���)
		}

		template <typename T>	//(�̹����� �ε��ϴ� �Լ��� ���带 �ε��ϴ� �Լ��� �޶�� �ϹǷ� ���ø� ���)
		static T* Load(const std::wstring& name, const std::wstring& path)
		{
			T* resource = Resources::Find<T>(name);		// �ϴ� �̹� �ִ��� Ȯ��

			if (resource != nullptr)					// resource�� nullptr�� �ƴ϶�� �޸𸮸� ���� �Ҵ��� �ʿ䰡 ����
				return resource;						// ���ҽ� ��ȯ

			resource = new T();
			if (FAILED(resource->Load(path)))			// ���� �ƴϸ� �ε� ����, ���̸� ����� �ε尡 �� ��
			{
				MessageBox(nullptr, L"Resource Load Failed!", L"Error", MB_OK);
				delete resource;						// ������ ����
				return nullptr;
			}

			resource->SetName(name);
			resource->SetPath(path);
			mResources.insert(std::make_pair(name, resource));

			return resource;							// �� ���ٸ� resource ��ȯ
		}

		template <typename T>
		static void Insert(const std::wstring& name, T* resource)
		{
			resource->SetName(name);
			mResources.insert(std::make_pair(name, resource));
		}

		static void Release()
		{
			for (auto iter : mResources)
			{
				delete iter.second;
				iter.second = nullptr;
			}
		}

	private:
		static std::map<std::wstring, Resource*> mResources;
		//Player Object, Monster Object������ ���� �����ؾ��ϹǷ� static
		// Ʈ�� ������ ����ؾ� ������ Ž���Ͽ� ������ �� �����Ƿ� map ���
	};

}

