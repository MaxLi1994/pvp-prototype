#include <string>
#include <map>
#include <opencv2/opencv.hpp>

#include "type.hpp"

using namespace std;

namespace pvp
{
    void Params::set_int(const string &key, int value)
    {
        map_int.insert(pair<string, int>(key, value));
    }

    void Params::set_float(const string &key, float value)
    {
        map_float.insert(pair<string, float>(key, value));
    }

    void Params::set_string(const string &key, string value)
    {
        map_string.insert(pair<string, string>(key, value));
    }

    void Params::set_opencv_mat(const string &key, cv::Mat value)
    {
        map_opencv_mat.insert(pair<string, cv::Mat>(key, value));
    }

    void Params::set_opencv_size(const string & key, cv::Size value)
    {

    }

    int Params::get_int(const string &key)
    {
        return map_int[key];
    }

    float Params::get_float(const string &key)
    {
        return map_float[key];
    }

    string Params::get_string(const string &key)
    {
        return map_string[key];
    }

    cv::Mat Params::get_opencv_mat(const string &key)
    {
        return map_opencv_mat[key];
    }
    
    cv::Size Params::get_opencv_size(const string & key)
    {
        return map_opencv_size[key];
    }
}