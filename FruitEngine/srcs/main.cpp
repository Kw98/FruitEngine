#include <iostream>

#include "FruitEngine.h"
#include "GameObject.h"

int	main()
{
	std::cout << "Hello" << std::endl;
	FE::FruitEngine	fe({ 1024, 780 }, "LOL");
	FE::Scene scene1 = FE::SceneManager::Instance()->CreateScene("space_level", [](FE::Scene& scene) {std::cout << "LOADED FUNCTION" << std::endl; });
	FE::GameObject* player = scene1.EmptyGameObject();
	std::cout << player->Id << std::endl;
	fe.Run();
	return 0;
}