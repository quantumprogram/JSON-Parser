#include <fstream>
#include <string>
#include <variant>
#include <iostream>
#include <vector>
#include <stack>
#include <map>

using namespace std;
struct json_list;
struct json_object;
using json_value=std::variant<float,bool,string,json_list,json_object>;


struct json_list	
{
	
	std::vector<json_value> list;					//to store JSON list
};
struct json_object 
{
	
std::map<string,json_value> obj;					//to store JSON object
};	
class jsonparsercustom
{
	public:
		ifstream file;
		jsonparsercustom(string FILE);
	private:
		std::vector<string>::iterator it;
		bool checkDelimit(char piece);
		string readstring();
		vector<string> lexer();
		bool boolchecker(string s);
		bool isFloat(string s);
		int checker(string s);
		void printval(std::vector<string> v);
		json_list addList();
		json_object addObject();
	public:
		json_object JSONreadFile(bool print);	

};