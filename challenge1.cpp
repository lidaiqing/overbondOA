#include <bits/stdc++.h>

using namespace std;


class Solution {

	public:
		struct Bond {
			string bond, type;
			double term, yield;
			Bond() {}
			Bond(string _bond, string _type, double _term, double _yield) : bond(_bond), 
				type(_type), term(_term), yield(_yield) {}
		};
		struct Result {
			string bond, benchmark;
			double spread_to_benchmark;
			Result(string _bond, string _benchmark, double _spread_to_benchmark) : bond(_bond),benchmark(_benchmark), spread_to_benchmark(_spread_to_benchmark) {}
		};

		void input(string file_name)
		{
			ifstream file(file_name.c_str());
			string row;
			while (!getline(file, row).eof()) {
				Bond tmp = parseRow(row);
				if (tmp.type == "corporate")
					corporate.emplace_back(tmp);
				else
					government.emplace_back(tmp);		 
			}
		}

		Bond parseRow(string row)
		{
			// read a csv row and parse the data into Bond structure
			stringstream buffer(row);
			string s;
			string bond, type;
			double term, yield;
			vector<string> parser;
			while (getline(buffer, s, ','))
				parser.emplace_back(s);
			bond = parser[0], type = parser[1];
			term = atof(parser[2].c_str());  // extract double from string
			yield = atof(parser[3].c_str());
			return Bond{bond, type, term, yield};
		}
				
		void solve(string file_name) {
			vector<Result> res;
			for (int i = 0; i < corporate.size(); i++)
			{
				double min_dis = DBL_MAX; // record closest term
				Bond benchmark;
				for (int j = 0; j < government.size(); j++)
				{
					double diff = fabs(government[j].term - corporate[i].term);
					if (diff < min_dis) {
						min_dis = diff;
						benchmark = government[j];
					}
				}
				res.emplace_back(corporate[i].bond, benchmark.bond, corporate[i].yield - benchmark.yield);
			}
			output(file_name, res);
		}
		
		void output(string file_name, vector<Result>& res)
		{
			ofstream file;
			file.open(file_name.c_str());

			file << "bond,benchmark,spread_to_benchmark" << endl;
			for (int i = 0; i < res.size(); i++)
			{
				file << res[i].bond << "," << res[i].benchmark << ",";
				file << fixed << setprecision(2) << res[i].spread_to_benchmark << "%" << endl;
			}
			file.close();
		}
			
	private:
		vector<Bond> corporate;
		vector<Bond> government;
};


int main(int argc, char* argv[])
{
	assert(argc == 3);
	Solution ans = Solution();
	ans.input(argv[1]);
	ans.solve(argv[2]);
	return 0;
}
