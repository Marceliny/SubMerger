#include <string>
#include <vector>
#include <map>
#include <algorithm>

class ReadFile
{
private:
    const std::string basepath;
    const std::string toppath;
    static std::string mergedpath;

public:
    static void ReadSubtitleFile(const std::string &, std::map<std::string, std::string> &, bool);
    static std::map<std::string, std::string> base_map;
    static std::map<std::string, std::string> top_map;
    static std::vector<std::pair<std::string, std::string>> merged_vec;
    ReadFile(std::string b, std::string t, std::string m) : basepath(b), toppath(t)
    {
        mergedpath = m;
        ReadSubtitleFile(basepath,base_map,false);
        ReadSubtitleFile(toppath,top_map,true);
        MergeFiles();
        WriteMerge();
    }
    static void MergeFiles();
    static void WriteMerge();
};

extern inline void rtrim(std::string &s) {
    s.erase(std::find_if(s.rbegin(), s.rend(), [](int ch) {
        return !std::isspace(ch);
    }).base(), s.end());
}

extern inline void ltrim(std::string &s) {
    s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](int ch) {
        return !std::isspace(ch);
    }));
}

extern inline void trim(std::string &s) {
    ltrim(s);
    rtrim(s);
}
