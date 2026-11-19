#include<iostream>
#include<string_view>
#include<string>
#include<fstream>

void trim(std::string& input)
{
    const std::string whitespaces = "\t\n\r\f\v";

    size_t start = input.find_first_not_of(whitespaces);
    if (start == std::string::npos)
    {
        input.clear();
        return;
    }

    size_t end = input.find_last_not_of(whitespaces);
    input.erase(end+1);
    input.erase(0,start);
}

template<size_t N>
bool exit_instructed(const std::string_view (&exit_options)[N], const std::string& input)
{
    for(const string_view i : exit_options)
    {
        if(input == i)
            return true;
    }
    return false;
}

bool create_file(const std::string& path, const std::string& launcher_name, const std::string& file_name)
{
    std::ofstream file("D:\\LaunchApps\\" + file_name + ".bat");
    if(!file.is_open())
    {
        std::cout << "File was not created\n";
        return false;
    }
    file << "@echo off\n";
    file << "start \"\" /b /d \"" << path << "\\\" \"" << launcher_name << "\" %*";
    file.close();

    return file.good();
}

int main()
{
    constexpr std::string_view exit_options[] = {
        "exit","Exit","EXIT",
        "quit","Quit","QUIT"
    };
    std::string input = "";
    std::string path = "";
    std::string launcher_name = "";
    std::string file_name = "";

    while(true)
    {
        std::cout<<"Enter the path: ";
        std::getline(std::cin, input);
        trim(input);

        if(exit_instructed(exit_options, input))
            break;
        
        if(
            input.size()<3 ||
            input[1] != ':' ||
            input[2] != '\\' && input[2] != '/'
        )
        {
            std::cout<<"Entered path format is wrong.\nEnter correct path format.\n\n";
            continue;
        }

        path = input;

        while(true)
        {
            std::cout<<"Enter launcher name: ";
            std::getline(std::cin,input);
            trim(input);

            if(exit_instructed(exit_options, input))
                break;

            if(
                input.size() < 4 ||
                input.compare(input.size()-4, 4, ".exe") != 0
            )
            {
                std::cout<<"Entered file format is wrong.\n";
                std::cout<<"Enter correct file format.\n";
                continue;
            }

            launcher_name = input;
            break;
        }
        if(exit_instructed(exit_options, input))
            break;

        std::cout<<"Enter File Name: ";
        std::getline(std::cin,input);
        trim(input);

        if(exit_instructed(exit_options, input))
            break;
        file_name = input;

        if(!create_file(path, launcher_name, file_name))
            continue;
        break;
    }

    return 0;
}