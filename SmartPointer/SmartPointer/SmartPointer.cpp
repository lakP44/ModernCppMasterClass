#include <iostream>
#include <memory>
#include <string>

// unique_ptr
	// 
// shared_ptr
// weak_ptr

struct Dog
{
	std::string name;
	
	Dog(std::string name) : name(name) {};
};

int main()
{
	{
		// 스마트 포인터를 사용하지 않을 경우
		Dog* p_dog2 = new Dog("Dog2"); // 힙에 할당
		int* p_int1 = new int(100); // 힙에 할당

		delete p_dog2;
		delete p_int1;
	}

	{
		// 스마트 포인터 사용
		Dog* p_dog2 = new Dog("Dog2"); // 힙에 할당
		std::unique_ptr<Dog> up_dog_2{ p_dog2 }; // 이렇게 이미 존재하는 포인터를 unique pointer로 만들수도 있음
		// 그런데 이 작업을 수행하고 난 뒤에는 p_dog2을 사용하지 않는것을 권장, unique pointer가 수행하는 작업을 방해할 수 있음
		// 이렇게 null로 설정해주는것이 가장 좋음
		p_dog2 = nullptr ;
		// delete를 하니까 unique pointer도 사라짐, null로 해야하는듯

		std::unique_ptr<Dog> up_dog3{ new Dog("Dog3") }; // 이렇게 사용하면 unique pointer를 바로 사용할 수 있음
		std::unique_ptr<int> up_int2{ new int(200) }; // 이렇게 사용하면 unique pointer를 기존 자료형에도 바로 사용할 수 있음
		std::unique_ptr<Dog> up_dog3{ nullptr }; //  unique pointer에 nullptr 할당도 가능
	}
}