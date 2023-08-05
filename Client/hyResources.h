#pragma once
#include "hyResource.h"			// 경로와 이름 저장해두는 클래스

namespace hy
{
	class Resources
	{
	public:
		template <typename T>
		static T* Find(const std::wstring& name)		// 이미 로드한 이미지가 있는지 찾는 함수(이미 로드한 것은 다시 로그할 필요가 없으므로)
		{
			auto iter = mResources.find(name);			// auto : 자료형을 알아서 데이터 추론해줌(코드가 짧아지긴 하지만 딱 보고 무슨 자료형인지 알 수 없음)
			if (iter == mResources.end())
				return nullptr;							// 없으면 nullptr 반환

			return dynamic_cast<T*>(iter->second);		// 가져오자마자 자식걸로 형변환을 해주자->dynamic cast(자식껄로 바꿔줌)
		}

		template <typename T>	//(이미지를 로드하는 함수와 사운드를 로드하는 함수가 달라야 하므로 템플릿 사용)
		static T* Load(const std::wstring& name, const std::wstring& path)
		{
			T* resource = Resources::Find<T>(name);		// 일단 이미 있는지 확인

			if (resource != nullptr)					// resource가 nullptr이 아니라면 메모리를 새로 할당할 필요가 없음
				return resource;						// 리소스 반환

			resource = new T();
			if (FAILED(resource->Load(path)))			// 참이 아니면 로드 실패, 참이면 제대로 로드가 된 것
			{
				MessageBox(nullptr, L"Resource Load Failed!", L"Error", MB_OK);
				delete resource;						// 강제로 지움
				return nullptr;
			}

			resource->SetName(name);
			resource->SetPath(path);
			mResources.insert(std::make_pair(name, resource));

			return resource;							// 잘 들어갔다면 resource 반환
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
		//Player Object, Monster Object에서도 접근 가능해야하므로 static
		// 트리 구조를 사용해야 빠르게 탐색하여 가져올 수 있으므로 map 사용
	};

}

