#include<iostream>
#include<string_view>
#include<string>
#include<fstream>
using namespace std;

template<size_t N>
bool exit_instructed(const string_view (&exit_options)[N], const string& input)
{
    for(const string_view i : exit_options)
    {
        if(input == i)
            return true;
    }
    return false;
}

bool create_file(const string& path, const string& launcher_name, const string& file_name)
{
    ofstream file("D:\\LaunchApps\\" + file_name + ".bat");
    if(!file.is_open())
    {
        cout << "File was not created\n";
        return false;
    }
    file << "@echo off\n";
    file << "start \"\" /b /d \"" << path << "\\\" \"" << launcher_name << "\" %*";
    file.close();

    return file.good();
}

int main()
{
    constexpr string_view exit_options[] = {
        "exit","Exit","EXIT",
        "quit","Quit","QUIT"
    };
    string input = "";
    string path = "";
    string launcher_name = "";
    string file_name = "";
    bool exit_condition = false;
    bool created_file = false;

    while(true)
    {
        cout<<"Enter the path: ";
        getline(cin, input);

        if(exit_instructed(exit_options, input))
            break;
        
        if(input[1] != ':')
        {
            cout<<"Entered path format is wrong.\nEnter correct path format.\n\n";
            continue;
        }

        path = input;

        while(true)
        {
            cout<<"Enter launcher name: ";
            getline(cin,input);

            if(exit_instructed(exit_options, input))
                break;

            if(input.substr(input.length()-4,input.length()) != ".exe")
            {
                cout<<"Entered file format is wrong."<<endl;
                cout<<"Enter correct file format."<<endl;
                continue;
            }

            launcher_name = input;
            break;
        }
        if(exit_instructed(exit_options, input))
            break;

        cout<<"Enter File Name: ";
        cin>>input;

        if(exit_instructed(exit_options, input))
            break;
        file_name = input;

        created_file = create_file(path, launcher_name, file_name);
        if(!created_file)
            continue;
        break;
    }

    return 0;
}