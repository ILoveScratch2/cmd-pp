#include<bits/stdc++.h>
#include<windows.h>
#define EDITOR
using namespace std;
//editorapi.cpp
//-std=c++14 -Os -s
#ifndef EDITORAPI_INC
#define EDITORAPI_INC
HANDLE hConsole;
string exedir;
struct Hook {
    string event;    // onSave, onRun
    string command;  //"python myplugin.py"
};
vector<Hook> hooks;
unordered_map<int, string> langMap;
//string currentLang = "zh-cn"; //Ĭ������
string lan_str(int num){
    if(langMap.find(num)!=langMap.end()){
        return langMap[num];
    }
    return "[missing:"+to_string(num)+"]";
}
void edt_pause(){
	cout<<lan_str(300);
	char c = _getch();
}
string lan_cstr(int num){
    return lan_cstr(num).c_str();
}
void load_language(const string& langCode){
    langMap.clear();
    //currentLang = langCode;
    string fn = exedir+"setting\\"+langCode+".lang";
    ifstream ifs(fn);
    if(!ifs.is_open()){
        cerr<<"[lang] cannot open "<<fn<<endl;
        return;
    }
    string line;
    while(getline(ifs, line)){
        if(line.empty() || line[0]=='#') continue;
        size_t pos = line.find('=');
        if(pos == string::npos) continue;

        int id = stoi(line.substr(0, pos));
        string text = line.substr(pos+1);
        langMap[id] = text;
    }
    cout<<"[lang] loaded "<<langMap.size()<<" entries from "<<fn<<endl;
}
void load_hooks() {
    hooks.clear();
    string fn = exedir + "setting\\plugins.ini";
    ifstream ifs(fn);
    if(!ifs.is_open()){
        cout << "no plugins.ini, skip" << endl;
        return;
    }
    string line;
    while(getline(ifs,line)){
        if(line.empty() || line[0]=='#') continue;// ignore comment
        // ??: event=command
        auto pos = line.find('=');
        if(pos==string::npos) continue;
        Hook h;
        h.event = line.substr(0,pos);
        h.command = line.substr(pos+1);
        hooks.push_back(h);
    }
    cout<<"Loaded "<<hooks.size()<<" hooks"<<endl;
}
void runHooks(const string& event, const string& fname){
    for(auto &h : hooks){
        if(h.event == event){
        	if(h.command==""){
        		cout<<"[Hook] No hook at "<<event<<endl;
			}
			else{
	            string cmd = h.command + " \"" + fname + "\"";
	            cout << "[Hook] "<<event<<" -> "<<cmd<<endl;
	            system(cmd.c_str());				
			}
        }
    }
}
//init
EDITOR void Edinit(){
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
}
// �ƶ���굽ָ��λ��
EDITOR void EdmoveTo(int x, int y) {
    COORD pos = {static_cast<SHORT>(y), static_cast<SHORT>(x)};
    SetConsoleCursorPosition(hConsole, pos);
}
// ��ȡ��ǰ���λ��
EDITOR COORD EdgetPosition() {
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(hConsole, &csbi);
    return csbi.dwCursorPosition;
}
EDITOR void clearInputBuffer() {
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}
EDITOR void clearOutputBuffer(HWND hConsole) {
    if (!hConsole) return;
    
    // ��ȡ��ǰ����̨��Ϣ
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    
    // ������Ҫ������ַ���
    COORD coordScreen = {0, 0};
    DWORD cCharsWritten;
    DWORD dwConSize = csbi.dwSize.X * csbi.dwSize.Y;
    
    // �ÿո��������������
    FillConsoleOutputCharacter(
        GetStdHandle(STD_OUTPUT_HANDLE),
        ' ',
        dwConSize,
        coordScreen,
        &cCharsWritten
    );
    
    // ���ù��λ��
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coordScreen);
    
    // ��ѡ���������������
    if (hConsole) {
        SendMessage(hConsole, EM_SETSEL, 0, -1);
        SendMessage(hConsole, EM_REPLACESEL, 0, (LPARAM)"");
    }
}
// ����ƶ����
EDITOR void EdmoveRelative(int dx, int dy) {
    COORD current = EdgetPosition();
    EdmoveTo(current.X + dx, current.Y + dy);
}
// ������ֵ������� 
EDITOR void EdwriteToConsole(int x, int y, const std::string& text) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD charsWritten;
    COORD pos = {static_cast<SHORT>(x), static_cast<SHORT>(y)};
    
    WriteConsoleOutputCharacterA(
        hConsole,
        text.c_str(),
        text.length(),
        pos,
        &charsWritten
    );
}
// �������n������ƶ���
EDITOR void EdmoveLeft(int n) {
    COORD current = EdgetPosition();
    int newY = current.Y - n;
    
    // �߽��飬ȷ�������Ƴ�����̨��߽�
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(hConsole, &csbi);
    int minY = csbi.srWindow.Left;
    
    newY = max(newY, minY);
    EdmoveTo(newY,current.X );
}
// ��ȡ����̨�ߴ�
EDITOR void EdgetConsoleSize(int& width, int& height) {
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(hConsole, &csbi);
    width = csbi.srWindow.Right - csbi.srWindow.Left + 1;
    height = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
}
#endif //EDITORAPI_INC
