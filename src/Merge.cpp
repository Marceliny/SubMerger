#include "Merge.h"
#include <iostream>
#include <string>
#include <fstream>
#include <algorithm>

void rtrim(std::string &s);
void ltrim(std::string &s);
void trim(std::string &s);
std::map<std::string, std::string> ReadFile::base_map;
std::map<std::string, std::string> ReadFile::top_map;
std::vector<std::pair<std::string, std::string>> ReadFile::merged_vec;
std::string ReadFile::mergedpath;

void ReadFile::ReadSubtitleFile(const std::string &spaths, std::map<std::string, std::string> &mymap, bool tr)
{
    std::ifstream file;
    file.open(spaths);
    std::string line;
    std::string time;
    std::string dialog;
    bool pass = true;
    bool taketime = false;
    int i = 1;
    while (getline(file, line))
    {
        trim(line);
        if (pass)
        {
            taketime = true;
            pass = false;
            continue;
        }

        else if (taketime)
        {
            time = line;
            taketime = false;
            continue;
        }

        else if (line == "")
        {
            dialog = std::string(dialog.begin() + 1, dialog.end());
            if (tr)
            {
                dialog = "{\\an8}" + dialog;
            }
            mymap.insert({time, dialog});
            dialog = "";
            pass = true;
            continue;
        }
        dialog = dialog + "\n" + line;
    }
    if (!dialog.empty())
    {
        dialog = std::string(dialog.begin() + 1, dialog.end());
        if (tr)
        {
            dialog = "{\\an8}" + dialog;
        }
            mymap.insert({time, dialog});
    }
    
    file.close();
}

void ReadFile::WriteMerge()
{
    std::ofstream file;
    file.open(mergedpath, std::ios::trunc);
    int i = 1;
    for (auto &&item : merged_vec)
    {
        file << i << "\n";
        file << item.first + "\n";
        file << item.second + "\n\n";
        i++;
    }
    file.close();
}

void ReadFile::MergeFiles()
{
    std::copy(base_map.begin(), base_map.end(), std::back_inserter(merged_vec));
    std::copy(top_map.begin(), top_map.end(), std::back_inserter(merged_vec));
    std::sort(merged_vec.begin(), merged_vec.end(), [](std::pair<std::string, std::string> a, std::pair<std::string, std::string> b) { return a.first < b.first; });
}