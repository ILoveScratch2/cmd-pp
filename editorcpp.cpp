#include<bits/stdc++.h>
#include<conio.h>
#include<sstream>
#pragma once
#include"editorapi.cpp"
#include"editorrgb.cpp"
#include"editorstr.cpp"
using namespace std;
namespace _ed_cpp{
	string _ed_gpp_path = "";//g++ path
	string _ed_in_f = "";    //cpp path
	string _ed_out_f = "";   //exe path
	string _ed_yh = "-std=c++14 -O2 -s";
	string _ed_include = "";
	string _ed_yh2 = "-static-libgcc";
	string exedir;
	void getexedir(){
		char path[MAX_PATH];
	    DWORD len = GetModuleFileName(NULL, path, MAX_PATH);
	    string t = string(path, len);
	    exedir = t.substr(0,t.find_last_of("\\"))+"\\";
	    cout<<"getexedir:exedir is "<<exedir<<endl;
	}
	void init(){
		getexedir();
		string fn = exedir+"setting\\mingw_g++.ini";
		ifstream ifs(fn.c_str());
		getline(ifs,_ed_gpp_path);
		getline(ifs,_ed_yh);
		getline(ifs,_ed_yh2);
		getline(ifs,_ed_include);
		ifs.close();
	}
	string _gen_cmd(string gpp_path,string in_f,string out_f,
		string yh,string include,string yh2){
		stringstream ss("");
		ss
		<<"\""<<gpp_path<<"\" \""<<in_f<<"\" -o \""
		<<out_f<<"\" "<<yh<<" "<<include<<" "
		<<yh2;
		return ss.str();
	}
	bool runProcess1(const std::string &commandLine) {
	    STARTUPINFOA si;
	    PROCESS_INFORMATION pi;
	    ZeroMemory(&si, sizeof(si));
	    si.cb = sizeof(si);
	    ZeroMemory(&pi, sizeof(pi));
	    // ע�⣺CreateProcess ��Ҫ��д������
	    char *cmd = _strdup(commandLine.c_str());
	    BOOL success = CreateProcessA(
	        NULL,   // ��ִ���ļ�·����NULL=�����е�һ�� token��
	        cmd,    // �����У������д��
	        NULL,   // ���̰�ȫ����
	        NULL,   // �̰߳�ȫ����
	        TRUE,   // �Ƿ�̳о��
	        CREATE_NEW_CONSOLE ,      // ����ѡ��
	        NULL,   // ��������
	        NULL,   // ��ǰĿ¼
	        &si,    // ��������
	        &pi     // ������Ϣ
	    );
	    free(cmd);
	    if (!success) {
	        std::cerr << "CreateProcess failed. Error code: " << GetLastError() << std::endl;
	        return false;
	    }
	    CloseHandle(pi.hProcess);
	    CloseHandle(pi.hThread);
	    return true;
	}
	bool runProcess(const std::string &commandLine) {
	    STARTUPINFOA si;
	    PROCESS_INFORMATION pi;
	    ZeroMemory(&si, sizeof(si));
	    si.cb = sizeof(si);
	    ZeroMemory(&pi, sizeof(pi));
	    // ע�⣺CreateProcess ��Ҫ��д�Ļ�����
	    char *cmd = _strdup(commandLine.c_str());
	    // ��������
	    BOOL success = CreateProcessA(
	        NULL,   // ��ִ���ļ�����NULL=���������������һ��token��
	        cmd,    // �����У������д��
	        NULL,   // ��ȫ����
	        NULL,   // ��ȫ����
	        TRUE,   // �Ƿ�̳о��
	        0,      // ��������
	        NULL,   // ��������
	        NULL,   // ��ǰĿ¼
	        &si,    // ��������
	        &pi     // ������Ϣ
	    );
	    free(cmd);
	    if (!success) {
	        std::cerr << "CreateProcess failed. Error code: " << GetLastError() << std::endl;
	        return false;
	    }
	    // �ȴ����̽���
	    WaitForSingleObject(pi.hProcess, INFINITE);
	    // �رվ��
	    CloseHandle(pi.hProcess);
	    CloseHandle(pi.hThread);
	    return true;
	}
	void _ed_complete_file(bool run = 0){
		system("cls");
		clearInputBuffer();
		EdmoveTo(0,0);g_conc.SetRGBmap(135);
		cout<<"C++Դ�ļ�����������\n";
		unsigned int ts = GetTickCount();
		string in=_ed_in_f,out;
		//cin>>out;
		out = in.substr(0,in.find_last_of("."))+".exe";
		cout<<"C++������:"<<_ed_gpp_path<<endl;
		cout<<"����ļ���:"<<out<<"\n";
		/*cmd = "cd \""+_ed_gpp_path.substr(0,_ed_gpp_path.find_last_of("\\"))+"\"";
		cout<<"����:"<<cmd<<endl;
		system(cmd.c_str());*/
		string cmd = _gen_cmd(_ed_gpp_path,in,out,_ed_yh,_ed_include,_ed_yh2);
		//replace(cmd.begin(), cmd.end(), '\\', '/');
		cout<<"����:"<<cmd<<endl;
		cout<<"��ʼ����\n";
		runProcess(cmd);
		cout<<"ֹͣ����\n";
		unsigned int es = GetTickCount();
		unsigned int dt = es - ts;
		cout<<"����ʱ��:"<<dt<<"ms\n";
		if(run){
			cout<<"��ʼ����\n";
			cmd = "\""+exedir+"tool\\ConsolePauser.exe\" \""+out+"\"";
			cout<<"����:"<<cmd<<endl;
			runProcess1(cmd);
			//system(cmd.c_str());
		}
		system("pause");
	}
}
/*int main(){
	_ed_cpp::init();
	system((_ed_cpp::_ed_gpp_path + " --version").c_str());
	cout << "G++ path = [" << _ed_cpp::_ed_gpp_path << "]" << endl;
	string s = _ed_cpp::_gen_cmd(_ed_cpp::_ed_gpp_path,"C:\\hg\\1.cpp","C:\\hg\\1.exe",_ed_cpp::_ed_yh,_ed_cpp::_ed_include,_ed_cpp::_ed_yh2);
	cout<<s<<endl;
	//system(s.c_str());
	_ed_cpp::runProcess(s);
	system("pause");
}*/
