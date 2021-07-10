#include "heads.h"

void input();
void translator();//使用map进行翻译
void select(string cutter,string information,int num_c,int num,int start);//递归筛选

vector<string> target,translated;

void input()
{
    bool control[5] = {true}; //嵌套控制变量    由小到大依次控制向深层的嵌套
    fstream operate;
    string cutter, file_name, asker;
    while (control[0])
    {
        cout << "请输入分割符" << endl;
        cout << "注:若要将空格作为分割符,请输入 space*[空格个数]" << endl;
        cout << "例:若要 2个空格作为分隔符 则输入 space*2" << endl;
        cout << "若要将回车作为分隔符,则输入enter" << endl;
        cout << "请输入..." << endl;
        cin >> cutter;
        cout << "请输入要读取的摩斯密码所在的文件名" << endl;
        cout << "请输入..." << endl;
        cin >> file_name;
        control[1] = true;
        if(cutter.compare("space*0")==0)//方式后面使用空格作为分隔符时发现 0个空格作为分隔符
        {
            cout<<"space*0 不可取!"<<endl<<"请重新输入!"<<endl;
            continue;
        }
        while (control[1])
        {
            cout << "分隔符为" << endl
                 << cutter << endl
                 << "文件名为:" << endl
                 << file_name << endl
                 << "是否重新输入?(y/n)" << endl;//再次询问
            cin >> asker;
            if (asker.compare("y") == 0)
            {
                cout << "您已选择重新输入" << endl
                     << endl;
                control[1] = false;
                continue;
            }
            else
            {
                if (asker.compare("n") == 0)
                {
                    control[0] = false;
                    control[1] = false;
                    continue;
                }
                else
                {
                    cout << "您的指令无效..." << endl;//指令无效重新输入
                    continue;
                }
            }
        }
    }
    control[0] = true;
    cout << "读取中..." << endl
         << endl;
    operate.open(file_name, ios::in);
    if (operate.fail())
    {
        cout << "读取文件失败!"<<endl<<"请检查文件名是否有误!"<<endl;
        cout<<"文件名:"<<endl<<file_name<<endl;
        cout<<"请再次输入文件名..."<<endl<<"请输入..."<<endl;
        cin>>file_name;
        operate.open(file_name, ios::in);
        if(operate.fail())
        {
            cout<<"文件名再次出错!"<<endl<<"正在退出程序..."<<endl;
            Sleep(3000);
            exit(-1);
        }
    }
    if(cutter.compare("enter")!=0)
    {
        string information;//文件内的莫斯密码以及其分隔符
        getline(operate,information);
        //cout<<information<<endl;//ok
        //cout<<information.size()<<endl;
        if(cutter.find("space*")!=cutter.npos&&cutter.size()==7)
        {
            int nums=(int)cutter[6]-48;//获取要几个空格
            cutter.clear();
            for(int counter=0;counter<nums;counter++)//使用空格作为分隔符
            {
                cutter+=" ";
            }
            //cout<<cutter.size()<<endl;
            //cout<<"cutter:"<<cutter<<"!"<<endl;
        }
        else
        {
            for(int counter=0;counter<information.size();counter++)//如果不使用空格作为分隔符 则清楚所有的空格
            {
                if(information[counter]==' ')
                {
                    information.erase(counter,1);
                }
            }
            //cout<<information<<endl;
        }
        select(cutter, information, 0, 0, 0);
        //cout<<target.size()<<endl;
        /*
        for(int num=0;num<target.size();num++)
        {
            cout<<endl<<target[num]<<num<<endl;
        }
        */
        for (int counter = 0; counter < target.size(); counter++) //即使使用空格作为分隔符 筛选后清除空格防止干扰翻译
        {
            //cout<<target[counter]<<target[counter].size()<<endl;
            for (int num = 0; num < target[counter].size(); num++)
            {
                //cout<<num<<endl;
                //cout<<"in"<<endl;
                //cout<<target[counter][num]<<"!"<<endl;
                if (target[counter][num] == ' ')
                {
                    //cout<<"!"<<endl;
                    target[counter].erase(num, 1);
                }
            }
            if (target[counter].size() == 0)
            {
                //cout << "0" << endl;
                vector<string>::iterator it;
                it = target.begin() + counter;
                target.erase(it); //!!!在消去元素的同时 容器本身的大小也在变小 !!!2021 07 .06  0.00
                counter--;
            }
        }
        /*
        for(int k=0;k<target.size();k++)
        {
            cout<<target[k]<<endl;
        }
        */
        translator();
    }
    else
    {
        string information;
        while(getline(operate,information))//若使用回车作为分隔符 直接getline 读取
        {
            //cout<<information<<endl;
            target.push_back(information);
        }
        translator();
    }
}


void translator()
{
    map<string, string> morse_code = {
        {".-", "A"}, {"-...", "B"}, {"-.-.", "C"}, 
        {"-..", "D"}, {".", "E"}, {"..-.", "F"}, 
        {"--.", "G"}, {"....", "H"}, {"..", "I"},
        {".---", "J"}, {"-.-", "K"}, {".-..", "L"},
        {"--", "M"}, {"-.", "N"}, {"---", "O"},
        {".--.", "P"}, {"--.-", "Q"}, {".-.", "R"},
        {"...", "S"}, {"-", "T"}, {"..-", "U"}, 
        {"...-", "V"}, {".--", "W"}, {"-..-", "X"}, 
        {"-.--", "Y"}, {"--..", "Z"}, {".----", "1"},
        {"..---", "2"}, {"...--", "3"}, {"....-", "4"}, 
        {".....", "5"}, {"-....", "6"}, {"--...", "7"},
        {"---..", "8"}, {"----.", "9"}, {"-----", "0"}, 
        {"..--..", "?"}, {"-..-.", "/"}, {"-.--.-", "()"},
        {"-....-", "-"}, {"---...",":"},{"-.-.-.",";"},
        {"..--..","?"},{"-...-","="},{".----.","'"},
        {"-..-.","/"},{"-.-.--","!"},{"-....-","-"},
        {"..--.-","_"},{".-..-.","\""},{"-.--.","("},
        {"-.--.-",")"},{"...-..-","$"},{"....","&"},
        {".--.-.","@"},{".-.-.","AR"},{".-...","AS"},
        {"...-.-","SK"},{"-...-","BT"},{".-.-.-", "."}};
    map<string,string>::iterator it;//迭代器

    for (int pos_T = 0; pos_T < target.size(); pos_T++)
    {
        it=morse_code.find(target[pos_T]);
        if(it!=morse_code.end())
        {
            cout<<it->second;
        }
        else
        {
            if(target[pos_T].compare(".-.-.-")==0)
            {
                cout<<".";
            }
            else
            {
                cout<<endl<<"无法翻译:"<<endl<<target[pos_T]<<endl;
                cout<<"请检查翻译内容是否有多加了空格的现象!"<<endl;
            }
        }
    }
}

void select(string cutter, string information, int num_c, int num, int start)
{
    /*
    cout << "cutter:" << endl
         << cutter << endl;
    cout << "information:" << endl
         << information << endl;
    cout << "当前start" << endl
         << start << endl;
    cout << "当前num_c" << endl
         << num_c << endl;
    cout << "当前num" << endl
         << num << endl;
    cout<<"information size"<<endl<<information.size()<<endl;
    */
    if (cutter[num_c] == information[num])
    {
        num_c++;
        if (num_c == cutter.size()) //如果情况为真,则表明完整的分隔符被发现
        {
            /*
            cout << "true!!" << endl
                 << endl;
            */
            num_c = 0;
            string deliver;
            for (; start < num - cutter.size() +1; start++)
            {
              //  cout << information[start] << endl;
                deliver += information[start];
            }
            start += cutter.size();
            /*
            cout << endl
                 << deliver << endl;
            */
            target.push_back(deliver);
            deliver.clear();
            num++;
            if (num >= information.size())
            {
                return;
            }
            select(cutter, information, num_c, num, start);
        }
        else
        {
            
            num++;
            select(cutter, information, num_c, num, start);
        }
    }
    else
    {
        num_c = 0;
        num++;
        if (num >= information.size())
        {
            string deliver;
            for (; start < num; start++)
            {
              //cout << information[start] << endl;
                deliver += information[start];
            }
            start += cutter.size();
            /*
            cout << endl
                 << deliver << endl;
            */
            target.push_back(deliver);
            deliver.clear();
            return;
        }
        select(cutter, information, num_c, num, start);
    }
}