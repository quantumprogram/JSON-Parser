#include "jsonparser.h"
#include <iostream>

using namespace std;

int main()
{
	jsonparsercustom object("startup.json");
	json_object j1;
	
	int i;
	j1=object.JSONreadFile(true);						//Set this parameter true to display the object first
														//call this function again to read next object		
	cout<<get<float>(get<json_list>(j1.obj["array"]).list[0])<<endl; //accessing element of a list in the jsonobject			  	
	cout<<get<string>(get<json_list>(get<json_list>(j1.obj["array"]).list[1]).list[0])<<endl;//accessing nested list
	cout<<get<string>(j1.obj["color"])<<endl;			//accessing a string
	cout<<get<string>(get<json_object>(get<json_list>(j1.obj["array"]).list[2]).obj["key"])<<endl; //for elements in nested objects 
}

	