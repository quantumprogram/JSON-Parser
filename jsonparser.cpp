#include "jsonparser.h" 
jsonparsercustom::jsonparsercustom(string FILE)       // parameterized constructor to open input file when object is created 
	{
		file.open(FILE);
	}

bool jsonparsercustom::checkDelimit(char piece)       // Checks whether a given character is a delimiter
	{
		char delimit[]={'{','}','[',']',',',':','"'};
		int i=-1;
		do
		{
			i++;
			if(piece==delimit[i])
				return true;
			
		}while(delimit[i]!='"');
		return false;

	}
string jsonparsercustom::readstring()               //Reads and stores a string         
	{
		char piece;
		string token="";
		while(1)
		{
			file>>std::noskipws>>piece;		       //reads string without skipping white spaces
			if(piece == '"')
				return token;
			token +=piece;
		}	


	}
	vector<string> jsonparsercustom::lexer()       //This functions job is to tokenize the various elements of a json grammar
													// in a vector		
	{
		stack<char> s;
		char piece;
		string temp;
		string token="";
		std::vector<string> value;
		int flag=0;
		do
		{
			file >>std::skipws>>piece;
            if(piece=='{')
            {
            	flag=1;
            	token+=piece;	
				s.push(piece);
				value.push_back(token);
				token="";
			}	
			else if(piece=='}')
			{	
				token+=piece;	
				s.pop();
				value.push_back(token);
				token="";
			}	
			else if(flag==1)
			{
				if (checkDelimit(piece))
				 {
				 	if(piece=='"')
				 	{
				 		temp=piece;
				 		value.push_back(temp);	
				 		char ab;
				 		while(1)
				 		{
				 			ab=piece;
				 			file>>std::noskipws>>piece;
				 			if(piece=='"')
				 			{
				 				if(ab!='\\')
				 					break;
				 			}
				 			token=token+piece;	
				 		}	
				 		//token=readstring();
				 		value.push_back(token);
				 		value.push_back(temp);
				 		token="";

				 	}
				 else
				 {		
            		temp = piece;
            	if (token != "") {
                	value.push_back(token);
                    value.push_back(temp);
                    token = "";
                }

             else 
                value.push_back(temp);
            
         	 }
         	}
         	else 
            	token += piece;
        
    
			}			

		}while((!s.empty())||(flag==0));

    return value; 
	}
	bool jsonparsercustom::boolchecker(string s)               //check a given string is boolean datatype
	{
		if(s=="true")
			return true;
		else
		    return false; 	
	}
	bool jsonparsercustom::isFloat(string s)			      //check a given string is float or not
	{	
		char k;
		for(int i=0;i<s.length();i++)
		{
			k=s.at(i);
			if(!((k>='0'&&k<='9')||k=='.'))
				return false;
		}
		return true;

	}
	int jsonparsercustom::checker(string s)						//driver function of checking functions
	{
		if(s=="true"||s=="false")
			return 1;
		if(isFloat(s))
			return 2;
		if(s=="[")
			return 3;
		if(s=="{")
			return 4;
		if(s[0]=='"')
			return 5;
		/*if(checkDelimit(s[0]))
			return 4;*/
		return 0;

	}
	void jsonparsercustom::printval(std::vector<string> v)		//prints the elements in current json object
	{
		cout<<endl;
		int count=0;
		for (auto it = v.begin(); it != v.end(); ++it)
		
					
			 	cout<<*it;		
			 	
			 	
		cout<<endl; 
		
	}
	
	json_list jsonparsercustom::addList()						//to add list in the json file to our container
	{				
		//stack<string> list1;
		json_list jl;
		while(*it!="]")
		{
			int check=checker(*it);
			switch(check)
			{
				case 1:
					jl.list.push_back(json_value(boolchecker(*it)));
					break;
				case 2:
					jl.list.push_back(json_value(stof(*it)));	
					break;
				case 3:
				 	it++;	
					jl.list.push_back(json_value(addList()));
					break;
				case 4:
					it++;
					jl.list.push_back(json_value(addObject()));	
					break;
				case 5:
					jl.list.push_back(json_value(*(++it)));
					++it;	
					break;	
				
			}


		++it; 	
		}
		
		return jl;
	}
	json_object jsonparsercustom::addObject()				//same as above with json_object
	{
		json_object j1;
		string temp;
		while((*it)!="}")
		{
			if((*it)[0]=='"' && *(it+3)==":")
		 	{	
		 			    	 		
		 			
		 		  int check=checker(*(it+4));
		 		  temp=*(it+1);
		 		  switch(check)
		 		  {
		 		  	case 1:
		 		  		it=it+4; 	
		 		  		j1.obj[temp]=json_value(boolchecker(*(it)));
		 		  		break;
		 		  	case 2:
		 		  		it=it+4;
		 		  		j1.obj[temp]=json_value(stof(*(it)));
		 		  		break;	
		 		  	case 3:
		 		  		it=it+5;
		 		  		j1.obj[temp]=json_value(addList());
		 		  		break;
		 		  	case 4:
		 		  		it=it+5;
		 		  		j1.obj[temp]=json_value(addObject());
		 		  		break;
		 		  	case 5:
		 		  		it=it+5;
		 		  		j1.obj[temp]=json_value(*(it));
		 		  		++it;
		 		  		break;	
		 		  				
		 		  	
		 		  }	
		 			
		 	}
		 	++it;			
		}
		
		return j1;	
	}
	json_object jsonparsercustom::JSONreadFile(bool print)				//the main file reader and calls other functions
	{
		 json_object jo;
		 std::vector<string> v=lexer();
		 
		     
			it=v.begin();
			it=it+1;		 
		 	jo=addObject();	
					 
		 
		 if(print)
         	printval(v);   	 
		
         return jo; 
	}

