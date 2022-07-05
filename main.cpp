#include "connect5.h"


int main()
{
	std::cout << "Loading..." << "\n\n";

	//ohdone();
	//ohdtwo();
    //ohdthr();
    //ohdfor();
    //ohdfiv();
	std::vector<std::vector<int>> test {{-7,-6,-12,-33},{5,5,7,24},{1,0,4,5}};
	std::vector<std::vector<Rational>> tx;
	for(int i = 0; i < 3; i++)
	{
		tx.push_back(std::vector<Rational>());
		for(int j = 0; j < 4; j++)
		{
			tx[i].push_back(Rational(test[i][j],1));
		}
	}
	
	RREF(tx);//broken?
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			tx[i][j].Display();
		}
		std::cout << std::endl;
	}

	std::cin.get();//waits for keypress
	return 0;
}