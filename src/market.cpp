#include <market.hpp>
using namespace marketdata;

void market::pushTrade(const security_t& instrument)
{
	std::vector<security_t> temp;
	auto itr = tradeMap_.find(instrument.symbol);
	if(itr != tradeMap_.end())
	{
		itr->second.emplace_back(instrument);
	}
	else
	{
		temp.push_back(instrument);
		tradeMap_[instrument.symbol] = temp;
		temp.clear();
	}
}

void market::analyseTrades(std::ofstream& fileout) const
{
	for(const auto& stk: tradeMap_)
	{
		auto init = 0;
		auto maxTimeGap = 0;

		if( stk.second.size() >= 2 )
		{
			for( size_t x = 0; x < stk.second.size() - 1 ; ++x )
			{
				auto delta = stk.second[x+1].timestamp - stk.second[x].timestamp ;
				maxTimeGap = delta > maxTimeGap ? delta : maxTimeGap ;
			}
		}

		auto volume      = std::accumulate(stk.second.begin(), stk.second.end(), init, 
				[](int sum, const security_t& curr) { return sum + curr.quantity ; });

		auto totalPrice  = std::accumulate(stk.second.begin(), stk.second.end(), init, 
				[](int sum, const security_t& curr) { return sum + ( curr.quantity * curr.price ) ; });

		auto weightedAveragePrice =  totalPrice / volume ;  

		auto maxPrice    = std::accumulate(stk.second.begin(), stk.second.end(), init, 
				[](int max, const security_t& curr) { return max > curr.price? max: curr.price ; });

		fileout  << stk.first << "," << maxTimeGap << "," << volume << "," << weightedAveragePrice << "," << maxPrice << "\n";
	}
}
