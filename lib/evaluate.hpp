#include<bits/stdc++.h> 
using namespace std; 

#define PI 3.14159265
bool dbg = false;

bool isF(string op){

    if(op == "sin") return true;
    if(op == "cos") return true;
    if(op == "tan") return true;
    if(op == "cotan") return true;
    if(op == "arcsin") return true;
    if(op == "arccos") return true;
    if(op == "arctan") return true;
    if(op == "arccotan") return true;
    if(op == "sqrt") return true;
    if(op == "log_2") return true;
    if(op == "ln") return true;
    if(op == "log_3") return true;
    if(op == "log_4") return true;
    if(op == "log_5") return true;
    if(op == "log_6") return true;
    if(op == "log_7") return true;
    if(op == "log_8") return true;
    if(op == "log_9") return true;
    if(op == "log") return true;
    if(op == "abs") return true;

    return false;
}

int prec(string c) 
{ 
    if(isF(c))
        return 4;
	if(c == "^") 
	    return 3; 
	
    if(c == "*" || c == "/") 
	    return 2; 
	
    if(c == "+" || c == "-") 
	    return 1; 

	return -1; 
} 

bool isO(string op){
    return (prec(op) > 0 || isF(op))? true : false;
}

vector<string> infixToPostfix(vector<string> s) 
{ 
	stack<string> st;  
	int l = s.size(); 
	vector<string> ns; 
	for(int i = 0; i < l; i++) 
	{
		if(isO(s[i]) == false && isF(s[i]) == false && s[i] != "(" && s[i] != ")") 
		    ns.push_back(s[i]); 

		else 
            if(s[i] == "(") st.push("("); 

		else if(s[i] == ")") 
		{ 
			while(!st.empty() && st.top() != "(") 
			{  
			    ns.push_back(st.top()); 
				st.pop(); 
			} 
			if(st.top() == "(") 
				st.pop(); 
		} 
		else{ 
			while(!st.empty() && prec(s[i]) < prec(st.top())) 
			{ 
			    ns.push_back(st.top()); 
				st.pop(); 
			} 

			st.push(s[i]); 
		} 

	} 
	while(!st.empty()) 
	{ 
        ns.push_back(st.top()); 
    	st.pop(); 
	} 
	
	return ns;

} 

bool is_number(string number_string)
{
    string::size_type sz;
    bool is_valid;
    double parsed_number = 0.0;
    try 
    { 
        parsed_number = std::stod(number_string, &sz); 
        is_valid = true; 
    } 
    catch(std::exception& ia) 
	{ 
        is_valid = false; 
    } 

    return is_valid;
}

vector<string> tokenization(string token){
    string tmp = "";
    vector<string> ret;
    for(int i = 0; i < token.size(); i++){
        string x = string(1, token[i]) ;
        if(x != " "){
            if(isO(x) || x == "(" || x == ")" ){
                    ret.push_back(tmp);
                    ret.push_back(x);
                    tmp = "";
            }
            else
                tmp += x;
        }else
            continue;
    }

    if(tmp.size() > 0)
        ret.push_back(tmp);

    vector<string> retret;
    for(auto x : ret)
        if(x != "")
            retret.push_back(x);

    vector<string> newretret;
    bool flag = false;
    for(int i = 0; i < retret.size(); i++)
        if(i > 0 && i + 1 < retret.size() && (isO(retret[i-1]) || retret[i-1] == "(") && retret[i] == "-" && is_number(retret[i+1]))
            newretret.push_back("-" + retret[i+1]), i++;
        else        
            newretret.push_back(retret[i]);

    return newretret;
}

double apply(double a, double b, string op){

    if(op == "+") return a + b;
    if(op == "-") return a - b;
    if(op == "*") return a * b;
    if(op == "/") return a / b;
    if(op == "^") return pow(a,b);

    return 0;
}

double cbl(double base, double arg){
    return (double)log10(arg)/(double)log10(base);
}

double applyF(double a, string op){

    if(op == "sin") return sin(a);
    if(op == "cos") return cos(a);
    if(op == "tan") return tan(a);
    if(op == "cotan") return 1/tan(a);
    if(op == "arcsin") return asin(a);
    if(op == "arccos") return acos(a);
    if(op == "arctan") return atan(a);
    if(op == "arccotan") return PI/2 - atan(a);
    if(op == "sqrt") return sqrt(a);
    if(op == "log_2") return log2(a);
    if(op == "ln") return log(a);
    if(op == "log_3") return cbl(3,a);
    if(op == "log_4") return cbl(4,a);
    if(op == "log_5") return cbl(5,a);
    if(op == "log_6") return cbl(6,a);
    if(op == "log_7") return cbl(7,a);
    if(op == "log_8") return cbl(8,a);
    if(op == "log_9") return cbl(9,a);
    if(op == "log") return log10(a);
    if(op == "abs") return abs(a);
    return 0;
}


double evaluate(string expr){
    vector<string> tokens = tokenization(expr);
    vector<string> post = infixToPostfix(tokens);
    if(dbg){
        for(int i = 0; i < post.size(); i++)
            cout<<"["<<post[i]<<"]";
        cout<<endl;
    }

    stack<double> values;
    for(int i = 0; i < post.size(); i++){
        if(isF(post[i]) || isO(post[i])){
            if(isF(post[i])){
                double value = values.top();
                values.pop();
                values.push(applyF(value, post[i]));
            }else{
                double value1 = values.top();
                values.pop();
                double value2 = values.top();
                values.pop();
                values.push(apply(value2, value1, post[i]));
            }
        }else
            values.push(stold(post[i]));
        
        if(dbg){
            for(stack<double> tmp = values; !tmp.empty(); tmp.pop())
                cout<<tmp.top()<<" ";

            cout<<endl;
        }
    }

    return values.top();
}

string change(string newstr, double value){
    string str = newstr;
    string nstr = to_string(value);
    string nstrE = to_string(M_E);
    string nstrPi = to_string(M_PI);

    while(str.find('x') != std::string::npos){
        string left = str.substr(0, str.find('x'));
        string right = str.substr(str.find('x') + 1);
        str = left + "("+ nstr + ")" + right;
    }

    while(str.find('e') != std::string::npos){
        size_t startE = str.find('e');

        string left = str.substr(0, startE);
        string right = str.substr(startE + 1);
        str = left + "("+ nstrE + ")" + right;
    }
    
    while(str.find("pi") != std::string::npos){
        size_t startP = str.find("pi");

        string left = str.substr(0, startP);
        startP++;
        startP++;
        string right = str.substr(startP);
        str = left + "("+ nstrPi + ")" + right;
    }

    return str;
}