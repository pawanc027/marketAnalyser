#ifndef MARKET_H
#define MARKET_H

#include <iostream>
#include <vector>
#include <map>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <numeric>

using namespace std;

namespace marketdata {
	struct security
	{
		std::string        symbol;
		unsigned long      timestamp;
		unsigned long long quantity;
		unsigned long      price;
	};

	using security_t     = security ;
	using tradebook_t    = std::map<std::string,std::vector<security_t>> ;

	class market
	{
		public:
			market(){}
			market(const market& src) = delete;
			market& operator=(const market& rhs) = delete;
			virtual ~market() {}

			virtual void pushTrade(const security_t& instrument);
			virtual void analyseTrades(std::ofstream& fileout) const;

		private:
			tradebook_t tradeMap_;	
	};
}

#endif
