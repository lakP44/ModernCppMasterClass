#include <iostream>
#include <memory>
#include <string>

// unique_ptr
	// 하나의 포인터가 하나의 위치만 가리킴
	// 따로 메모리 해제를 해줄 필요가 없음
// shared_ptr
// weak_ptr

struct Dog
{
	std::string name;

	Dog(std::string name) : name(name)
	{
		std::cout << name << " initialized dog" << std::endl;
	}

	~Dog() 
	{
		std::cout << name << " destructed dog" << std::endl;
	}

	void print_dog()
	{
		std::cout << name << std::endl;
	}

	// 뒤에 붙은 const는 멤버변수를 바꾸지 않는다는걸 컴파일러에게 알리는 용도
	std::string get_name() const {
		return name;
	}
};

struct Person
{
	std::string name;

	Person(std::string name) : name(name)
	{
		std::cout << name << " initialized person" << std::endl;
	}

	~Person()
	{
		std::cout << name << " destructed person" << std::endl;
	}

	void adopt_dog(std::unique_ptr<Dog> dog) {
		std::cout << name << " just adopted the dog " << dog->get_name() << std::endl;
	}

	void adopt_dog_v2(const std::unique_ptr<Dog>& dog) {
		std::cout << name << " just adopted the dog!!!!! " << dog->get_name() << std::endl;
	}
};

// 함수 내부의 포인터 return
std::unique_ptr<Dog> get_unique_ptr()
{
	std::unique_ptr<Dog> p_dog = std::make_unique<Dog>("Function Local ptr");
	// 아래는 스마트 포인터 자체의 주소
	std::cout << "unique function local ptr : " << &p_dog << std::endl;
	// 아래는 스마트 포인터가 가리키는 객체의 주소
	std::cout << "local object address : " << p_dog.get() << std::endl;
	return p_dog;
}

int main()
{
	bool 스마트_포인터를_사용하지_않을_경우 = false;
	bool unique_ptr_사용 = false;
	bool unique_ptr_사용_2 = false;
	bool 함수_인자로_unique_ptr_사용 = false;
	bool 함수_인자로_unique_ptr_사용_2 = false;
	bool 함수_내부의_unique_ptr를_밖으로_꺼내는_예제 = false;
	bool 배열에서의_unique_ptr_사용 = false;
	bool shared_ptr_사용 = false;
	bool unique_ptr와_shared_ptr를_스위칭 = true;

	if (스마트_포인터를_사용하지_않을_경우)
	{
		// 스마트 포인터를 사용하지 않을 경우
		Dog* p_dog2 = new Dog("Dog2"); // 힙에 할당
		int* p_int1 = new int(100); // 힙에 할당

		delete p_dog2;
		delete p_int1;
	}

	if (unique_ptr_사용)
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
		std::unique_ptr<Dog> up_dog_null{ nullptr }; //  unique pointer에 nullptr 할당도 가능

		// new를 사용하지 않고 사용하는 방법, 내부적으로는 new가 사용되지만 코드상으로 보이는건 더 깔끔해짐
		std::unique_ptr<Dog> up_dog4 = std::make_unique<Dog>("Dog4");
		std::unique_ptr<int> up_int3 = std::make_unique<int>(300); // 이렇게 사용하면 unique pointer를 기존 자료형에도 바로 사용할 수 있음

		std::cout << "p_int3의 주소 : " << up_int3.get() << std::endl;
		// unique pointer는 unique하기 때문에 복사할수 없음

		// error 예시
		// std::unique_ptr<Dog> error_test = up_dog3;
		// std::unique_ptr<Dog> error_test{ up_dog3 }; // <-- 이렇게 copy도 delete 됨
		// unique_ptr& operator=(const unique_ptr&) = delete; 이런식으로 복사 생성자 자체를 삭제해버림, std::unique_ptr를 타고가서 코드 확인 가능
	}

	if (unique_ptr_사용_2)
	{
		// 스마트 포인터 사용 2
		std::unique_ptr<Dog> up_dog{ new Dog("Dog") }; // 이렇게 사용하면 unique pointer를 바로 사용할 수 있음
		// 단순 복사는 불가능 하기 때문에 기존것의 메모리 관리 권한을 포기하고 넘겨줘야 함
		std::unique_ptr<Dog> up_dog5 = std::move(up_dog);
		std::cout << "up_dog5 : " << up_dog5 << ", up_dog : " << up_dog << std::endl;

		up_dog5.reset(); // nullptr로 초기화
	}

	if (함수_인자로_unique_ptr_사용)
	{
		// 함수 인자로 스마트 포인터 사용
		std::unique_ptr<Dog> up_dog{ new Dog("ddu") }; // 이렇게 사용하면 unique pointer를 바로 사용할 수 있음
		Person person{"rak"};

		// person.adopt_dog(up_dog); // <-- 이렇게 인자로 바로 넣으면 복사가 안되기 때문에 컴파일러 에러가 남
		person.adopt_dog(std::move(up_dog));
		// 함수에 포인터를 옮기고 나면 up_dog는 null이 되고 함수 내부로 저 포인터 주소가 옮겨짐
		// 그러니 adopt_dog 함수가 끝나면 dog의 소멸자가 호출됨
		std::cout << "up_dog : " << up_dog.get() << std::endl;
		std::cout << "=================================================================================" << std::endl;

		////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		// 임시객체를 넘겨줌, 함수가 끝나면 바로 사라질것임
		person.adopt_dog(std::make_unique<Dog>("Temporary Dog"));
	}

	if (함수_인자로_unique_ptr_사용_2)
	{
		// 함수 인자로 스마트 포인터 사용
		std::unique_ptr<Dog> up_dog{ new Dog("ddu2") }; // 이렇게 사용하면 unique pointer를 바로 사용할 수 있음
		Person person{ "rak2" };

		// 레퍼런스로 받아가는 함수에 넘겨주면 복사가 아니니 에러도 안뜸, 포인터가 해제되지 않음
		person.adopt_dog_v2(up_dog);
		std::cout << "up_dog : " << up_dog.get() << std::endl;
		std::cout << "=================================================================================" << std::endl;
	}

	if (함수_내부의_unique_ptr를_밖으로_꺼내는_예제)
	{
		std::unique_ptr<Dog> test = get_unique_ptr();

		test->print_dog();
		// 아래는 스마트 포인터 자체의 주소
		std::cout << "test : " << &test << std::endl;
		// 아래는 스마트 포인터가 가리키는 객체의 주소
		std::cout << "test object address : " << test.get() << std::endl;
		std::cout << "=================================================================================" << std::endl;
	}

	if (배열에서의_unique_ptr_사용)
	{
		// std::unique_ptr<Dog[]> dog_array {new Dog[3]{ Dog("ddu"), Dog("ddu2"), Dog("ddu3") }}; // 명확한 선언
		// 또는
		auto dog_array = std::unique_ptr<Dog[]>{ new Dog[3]{ Dog("ddu"), Dog("ddu2"), Dog("ddu3") } }; // 간결한 선언

		for (size_t i = 0; i < 3; ++i)
		{
			dog_array[i].print_dog();
		}
	}

	if (shared_ptr_사용)
	{
		// 어떠한 데이터가 있고 그걸 참조하는 포인터가 3개가 있으면 참조카운트는 3임
		// 만약 포인터가 하나씩 해제되면 참조카운트가 1씩 감소하고 참조카운트가 0이 될때 메모리가 해제됨

		std::shared_ptr<int> int_ptr_1{ new int(20) };
		std::cout << "count for int_ptr_1 : " << int_ptr_1.use_count() << std::endl;

		std::shared_ptr<int> int_ptr_2 = int_ptr_1;
		std::shared_ptr<int> int_ptr_3 = int_ptr_2;

		*int_ptr_2 = 70;
		std::cout << *int_ptr_1 << std::endl;

		
		std::cout << "count for int_ptr_2 : " << int_ptr_2.use_count() << std::endl;
		std::cout << "count for int_ptr_3 : " << int_ptr_3.use_count() << std::endl;

		std::cout << "============================ int_ptr_3를 참조해제 ============================" << std::endl;
		int_ptr_3.reset();

		std::cout << "count for int_ptr_1 : " << int_ptr_1.use_count() << std::endl;
		std::cout << "count for int_ptr_2 : " << int_ptr_2.use_count() << std::endl;

		// 이런식으로 만들수도 있음
		std::shared_ptr<int> int_ptr_4 = std::make_shared<int>(55);
	}

	
}