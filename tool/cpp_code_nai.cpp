#include<bits/stdc++.h>
using namespace std;
string replaceall(string s,const string& s1,const string& s2){
    if(s1.empty()) return s;// ��������ѭ��
    size_t pos = 0;
    while((pos = s.find(s1,pos)) != string::npos){
        s.replace(pos,s1.length(),s2);
        pos += s2.length();// �������滻���֣������ظ�����
    }
    return s;
}
std::string readFileToString(const std::string& filePath){
    std::ifstream file(filePath);
    if(!file.is_open()){
        throw std::runtime_error("Failed to open file: " + filePath);
    }

    std::stringstream buffer;
    buffer<<file.rdbuf();// Read entire file at once
    file.close();
    return buffer.str();
}
int main1(){
	string fn;
	cout<<"cpp file style Դ�����ʽ��\ninput fn\n";
	cin>>fn;
	string s = readFileToString(fn);
	s = replaceall(s," (","(");
	s = replaceall(s," )",")");
	s = replaceall(s," {","{");
	s = replaceall(s,", ",",");
	s = replaceall(s,"; ",";");
	s = replaceall(s,"} ","}");
	s = replaceall(s," == ","==");
	s = replaceall(s," < ","<");
	s = replaceall(s," > ",">");
	s = replaceall(s," <= ","<=");
	s = replaceall(s," >= ",">=");
	s = replaceall(s," << ","<<");
	s = replaceall(s," >> ",">>");
	s = replaceall(s," + ","+");
	s = replaceall(s," - ","-");
	s = replaceall(s,"\t","    ");
	cout<<"ended\n============================\n";
	cout<<s<<endl;
	system("pause");
	return 0;
}
int main(int argc,char **argv){
	if(argc!=3){
		cout<<"CPP FILE STYLE Դ�����ʽ��\n20250818 hty\nusage:"<<argv[0]<<" _input _output\n";
		return 0;
	}
	string s = readFileToString(argv[1]);
	s = replaceall(s," (","(");
	s = replaceall(s," )",")");
	s = replaceall(s," {","{");
	s = replaceall(s,", ",",");
	s = replaceall(s,"; ",";");
	s = replaceall(s,"} ","}");
	s = replaceall(s," == ","==");
	s = replaceall(s," < ","<");
	s = replaceall(s," > ",">");
	s = replaceall(s," <= ","<=");
	s = replaceall(s," >= ",">=");
	s = replaceall(s," << ","<<");
	s = replaceall(s," >> ",">>");
	s = replaceall(s," + ","+");
	s = replaceall(s," - ","-");
	s = replaceall(s,"\t","    ");
	ofstream ofs(argv[2]);
	const char *c = s.c_str();
	ofs.write(c,s.size());
	ofs.close();
	return 0;
}
