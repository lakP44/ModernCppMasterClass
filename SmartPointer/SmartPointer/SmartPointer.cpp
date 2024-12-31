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
		// ����Ʈ �����͸� ������� ���� ���
		Dog* p_dog2 = new Dog("Dog2"); // ���� �Ҵ�
		int* p_int1 = new int(100); // ���� �Ҵ�

		delete p_dog2;
		delete p_int1;
	}

	{
		// ����Ʈ ������ ���
		Dog* p_dog2 = new Dog("Dog2"); // ���� �Ҵ�
		std::unique_ptr<Dog> up_dog_2{ p_dog2 }; // �̷��� �̹� �����ϴ� �����͸� unique pointer�� ������� ����
		// �׷��� �� �۾��� �����ϰ� �� �ڿ��� p_dog2�� ������� �ʴ°��� ����, unique pointer�� �����ϴ� �۾��� ������ �� ����
		// �̷��� null�� �������ִ°��� ���� ����
		p_dog2 = nullptr ;
		// delete�� �ϴϱ� unique pointer�� �����, null�� �ؾ��ϴµ�

		std::unique_ptr<Dog> up_dog3{ new Dog("Dog3") }; // �̷��� ����ϸ� unique pointer�� �ٷ� ����� �� ����
		std::unique_ptr<int> up_int2{ new int(200) }; // �̷��� ����ϸ� unique pointer�� ���� �ڷ������� �ٷ� ����� �� ����
		std::unique_ptr<Dog> up_dog3{ nullptr }; //  unique pointer�� nullptr �Ҵ絵 ����
	}
}