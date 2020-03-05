#include <market.hpp>
using namespace marketdata;

int main(int argc, const char* argv[])
{

	if( argc != 3)
	{
		std::cout<<"usage: "<< argv[0] <<" <input filename>" << " <output filename>\n";
		return -1;
	}

	market    stockMarket;
	security_t  newTrade;

	std::string line;
	std::vector<std::string> vec;
	std::stringstream ss;
	std::string word;
	const char delimiter = ',';

	try 
	{
		std::ifstream infile(argv[1]);
		std::ofstream outfile(argv[2]);

		if(infile.is_open() && outfile.is_open())
		{
			while(getline(infile,line))
			{
				memset(&newTrade, 0 , sizeof(security_t));
				vec.clear();
				ss.clear();
				ss << line;
				while(getline(ss,word,delimiter))
					vec.emplace_back(word);
				if(vec.size() == 4)
				{
					newTrade.timestamp = std::stoul(vec[0]);
					newTrade.symbol    = vec[1];
					newTrade.quantity  = std::stoul(vec[2]);
					newTrade.price     = std::stoul(vec[3]);

					stockMarket.pushTrade(newTrade);
				}
			}

			stockMarket.analyseTrades(outfile);

			infile.close();
			outfile.close();
		}
		else
		{
			std::cerr << "Unable to open either the infile or outfile or both\n";
		}
	}
	catch(const exception& ex)
	{
		std::cout<<"Caught exception:"<< ex.what() << std::endl;
	}
	catch(...)
	{
		std::cout<<"Caught unknown exception:" << std::endl;
	}

	return 0;
}
