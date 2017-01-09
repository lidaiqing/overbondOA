#include <bits/stdc++.h>

using namespace std;


class Solution {

        public:
                struct Bond {
                        string bond, type;
                        double term, yield;
                        Bond() {}
                        Bond(string _bond, string _type, double _term, double _yield) : bond(_bond),type(_type), term(_term), yield(_yield) {}
			bool operator<(const Bond& that) const {
				return this->term < that.term;
			}
                };
                struct Result {
                        string bond;
                        double spread_to_curve;
                        Result(string _bond, double _spread_to_curve) : bond(_bond), spread_to_curve(_spread_to_curve) {}
                };
		
		struct Point {
			double term, yield;
			Point(double _term, double _yield) : term(_term), yield(_yield) {}
		};
		//comarision function for lower_bound
		struct LessThan {
			bool operator() (const Bond &l, const double i) const {
				return l.term < i;
			}
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
                        stringstream buffer(row);
                        string s;
                        string bond, type;
                        double term, yield;
                        vector<string> parser;
                        while (getline(buffer, s, ','))
                                parser.emplace_back(s);
                        bond = parser[0], type = parser[1];
                        term = atof(parser[2].c_str());
                        yield = atof(parser[3].c_str());
                        return Bond{bond, type, term, yield};
                }
		
		pair<Point,Point> findRange(Point C)
		{
			// use lower_bound to find first point greater or equal to point C
			auto it = lower_bound(government.begin(), government.end(), C.term, LessThan());
			Point G2 = Point(it->term, it->yield);
			it--; // find the last end point
			Point G1 = Point(it->term, it->yield);
			return make_pair(G1,G2);
		}
		
		double findDistance(Point C, Point G1, Point G2)
		{
			double delta_term = C.term - G1.term; // x axis
			double slop = (G2.yield - G1.yield) / (G2.term - G1.term);
			double delta_yield = slop * delta_term; // y axis
			Point B = Point(G1.term + delta_term, G1.yield + delta_yield); // B is the point in the line G1 - G2
			return C.yield - B.yield; // vertical distance
		}
		
                void solve(string file_name) {
                        vector<Result> res;
			sort(government.begin(), government.end()); // sort in terms of term
			
                        for (int i = 0; i < corporate.size(); i++)
                        {
				Point C = Point(corporate[i].term, corporate[i].yield);
                		pair<Point, Point> range = findRange(C);
				double dist = findDistance(C, range.first, range.second);	
                                res.emplace_back(corporate[i].bond, dist);
                        }
                        output(file_name, res);
                }

                void output(string file_name, vector<Result>& res)
                {
                        ofstream file;
                        file.open(file_name.c_str());

                        file << "bond,spread_to_curve" << endl;
                        for (int i = 0; i < res.size(); i++)
                        {
                                file << res[i].bond << ",";
                                file << fixed << setprecision(2) << res[i].spread_to_curve << "%" << endl;
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

