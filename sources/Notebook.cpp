#include "Notebook.hpp"
using namespace ariel;
#include <string>

const int MAX_LINE = 100;
const int number_of_lines = 20;
void Notebook::write(int page, int row, int col, Direction dir, const std::string &str)
{
  

    if (!can_write(page, row, col, dir, str))
    {
        throw std::invalid_argument("already written in this place.\n");
    }

    if (dir == Direction::Horizontal)
    {
        notebook_data[page][row].data.replace((size_t)col, str.length(), str);
    }

    else
    {
        for (int i = row; i < row + (int)str.length(); i++)
        {
            notebook_data[page][i].data[(size_t)col] = str[(size_t)i];
        }
    }
}

std::string Notebook::read(int page, int row, int col, Direction dir, int len)
{
    if (col >= MAX_LINE)
    {
        throw std::invalid_argument("Max line is 100.\n");
    }

    if (col < 0 || row < 0 || page < 0 || len < 0)
    {
        throw std::invalid_argument("the varibale must be positive integers.\n");
    }
    if (len + col > MAX_LINE && dir == Direction::Horizontal)
    {
        throw std::invalid_argument("Max line is 100.\n");
    }

    if (dir == Direction::Horizontal)
    {
        return notebook_data[page][row].data.substr((size_t)col, (size_t)len);
    }

    string str;
    for (int i = row; i < row + len; i++)
    {
        str += notebook_data[page][i].data[(size_t)col];
    }

    return str;
}

void Notebook::erase(int page, int row, int col, Direction dir, int len)
{
    if (col < 0 || row < 0 || page < 0 || len < 0)
    {
        throw std::invalid_argument("the varibale must be positive integers.\n");
    }
    if (col >= MAX_LINE)
    {
        throw std::invalid_argument("Max line is 100.\n");
    }

    if (len + col > MAX_LINE && dir == Direction::Horizontal)
    {
        throw std::invalid_argument("Max line is 100.\n");
    }

    if (dir == Direction::Horizontal)
    {
        notebook_data[page][row].data.replace((size_t)col, (size_t)len, string((size_t)len, '~'));
    }

    else if (dir == Direction::Vertical)
    {
        for (int i = row; i < row + len; i++)
        {
            notebook_data[page][i].data[(size_t)col] = '~';
        }
    }
};

void Notebook::show(int page)
{
    if (page < 0)
    {
        throw std::invalid_argument("Page must be a positive integer.\n");
    }

    cout << "\nPage: " << page << "." << endl;
    int last_row = 0;
    int max=0;
    for (auto const &row : notebook_data[page])
    {
      
        string lin=row.second.data;
        cout << lin << endl;
    }

  
};

bool Notebook::can_write(int page, int row, int col, Direction dir, const string &str)
{
    if (!check_str(str))
    {
        throw std::invalid_argument("string contains a problem char.\n");
    }
    if (str.find('~') != string::npos)
    {
        throw std::invalid_argument("string Cant containg char `~`.\n");
    }

    if (col < 0 || row < 0 || page < 0)
    {
        throw std::invalid_argument("the varibale must be positive integers.\n");
    }
    if (col >= MAX_LINE)
    {
        throw std::invalid_argument("Max line is 100.\n");
    }

    if ((int)str.length() + col >= MAX_LINE && dir == Direction::Horizontal)
    {
        throw std::invalid_argument("Max line is 100.\n");
    }
    if (dir == Direction::Horizontal)
    {
        for (int i = col; i < col + (int)str.length(); i++)
        {
            if (notebook_data[page][row].data[(size_t)i] != '_')
            {
              
                return false;
            }
        }
    }

    else
    {
        for (size_t i = (size_t)row; i < row + (int)str.length(); i++)
        {
            if (notebook_data[page][i].data[(size_t)col] != '_')
            {
                return false;
            }
        }
    }
    return true;
};

bool Notebook::check_str(const std::string &str)
{
    for (char c : str)
    {
        if (isprint(c) == 0)
        {
            return false;
        }
    }
    return true;
};

