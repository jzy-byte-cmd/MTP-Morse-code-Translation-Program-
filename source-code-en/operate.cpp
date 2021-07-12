#include "heads.h"//common heads

void input();
void translator();//use map to translate
void select(string cutter,string information,int num_c,int num,int start);//recursion filtrate

vector<string> target,translated;

void input()
{
    bool control[5] = {true}; //the control variate,index from 0 to 5,the bigger the index is,the deeper loop it is
    fstream operate;
    bool space=false;//the variate checks whether use space as separator
    string cutter, file_name, asker;//cutter：contains separator. file_name:contains file name which has morse code in it 
    while (control[0])                    //asker:contains the command inputed by user
    {
        cout<<"after you input the command,press enter to take the next step.."<<endl<<endl;
        cout << "please input a separator" << endl;
        cout << "comment:if you want to use spaces as the separator,input space*[number of space]" << endl;
        cout << "example:,use 2 spaces as separator,input space*2" << endl;
        cout << "if you want to use enter as the separator,input enter" << endl;
        cout << "please input..." << endl;
        cin >> cutter;
        cout << "please input the file name that contains morse code(make sure it is in the same file with the program)" << endl;
        cout << "please input..." << endl;
        cin >> file_name;
        control[1] = true;
        if(cutter.find("space*")!=cutter.npos&&cutter.size()==7)//if might use space as separator.
        {
            string check_space="space*";
            for(int num=0;num<6;num++)
            {
                if(cutter[num]!=check_space[num])
                {
                    break;
                }
                if(num==5)
                {
                    space=true;
                }
            }
            if(space==true)
            {
                if((int)cutter[6]-48==0)//if use space*0
                {
                    cout<<"space*0 is not applicable"<<endl<<"please re-input"<<endl;//N/A
                    continue;
                }
            }
        }
        while (control[1])
        {
            cout << "separator:" << endl
                 << cutter << endl
                 << "file name:" << endl
                 << file_name << endl
                 << "re-input?(y/n)" << endl;//check 
            cin >> asker;
            if (asker.compare("y") == 0)//re -input
            {
                cout <<"you have chosen to re-input" << endl
                     << endl;
                control[1] = false;
                continue;
            }
            else
            {
                if (asker.compare("n") == 0)//check is over
                {
                    control[0] = false;
                    control[1] = false;
                    continue;
                }
                else
                {
                    cout << "command is invalid..." << endl;//invalid command
                    continue;
                }
            }
        }
    }
    control[0] = true;
    cout << "reading..." << endl
         << endl;
    operate.open(file_name, ios::in);
    if (operate.fail())//if read fail
    {
        cout << "failed to read!" << endl
             << "please check the file name!and make sure it is in the same file with this program" << endl;
        cout << "file name:" << endl
             << file_name << endl;
        cout<<"re-input file name..."<<endl<<"please input..."<<endl;
        cin>>file_name;
        operate.open(file_name, ios::in);
        if(operate.fail())//fail again
        {
            cout<<"read failed again!"<<endl<<"exit..."<<endl;
            Sleep(3000);
            exit(-1);
        }
    }
    if(cutter.compare("enter")!=0)//use enter as separator
    {
        string information;//the morse code with separator will be stored in this variate
        getline(operate,information);
        //cout<<information<<endl;//ok
        //cout<<information.size()<<endl;
        if(space==true)
        {
            int nums=(int)cutter[6]-48;//obtain the number of space
            cutter.clear();
            for(int counter=0;counter<nums;counter++)//use space as separator
            {
                cutter+=" ";
            }
            //cout<<cutter.size()<<endl;
            //cout<<"cutter:"<<cutter<<"!"<<endl;
        }
        else
        {
            for(int counter=0;counter<information.size();counter++)//if the separator was not space,
            {                           //eliminate all the spaces between morse code and separator
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
        for (int counter = 0; counter < target.size(); counter++) //even if the separator was space,
        {                  //eliminate the spaces in case of interfering with translation after being filtrated.
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
                target.erase(it); 
                counter--;
            }
        }
        /*
        for(int k=0;k<target.size();k++)
        {
            cout<<target[k]<<endl;
        }
        */
        translator();//start translating
    }
    else
    {
        string information;
        while(getline(operate,information))//if the separator was enter,just getline
        {
            //cout<<information<<endl;
            target.push_back(information);
        }
        translator();
    }
}


void translator()
{
    map<string, string> morse_code = {//morse code
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
    map<string,string>::iterator it;

    for (int pos_T = 0; pos_T < target.size(); pos_T++)//search in morse code and print
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
                cout<<endl<<"can not translate:"<<endl<<target[pos_T]<<endl;
                cout<<"please check whether there is more space!"<<endl;
            }
        }
    }
}

void select(string cutter, string information, int num_c, int num, int start)//recursion filtrate
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
        if (num_c == cutter.size()) //if true ,then the complete separator was found
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
            start += cutter.size();//record the location of the separator
            /*
            cout << endl
                 << deliver << endl;
            */
            target.push_back(deliver);//push the morse code without separator into target
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