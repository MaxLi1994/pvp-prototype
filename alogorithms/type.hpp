#include <string>
#include <map>
#include <opencv2/opencv.hpp>

using namespace std;

namespace pvp
{
  class Params
  {
    public:
      void set_int(const string &key, int value);
      void set_float(const string &key, float value);
      void set_string(const string &key, string value);
      void set_opencv_mat(const string &key, cv::Mat value);
      void set_opencv_size(const string &key, cv::Size value);

      int get_int(const string &key);
      float get_float(const string &key);
      string get_string(const string &key);
      cv::Mat get_opencv_mat(const string &key);
      cv::Size get_opencv_size(const string &key);

    private:
      map<string, int> map_int;
      map<string, float> map_float;
      map<string, string> map_string;
      map<string, cv::Mat> map_opencv_mat;
      map<string, cv::Size> map_opencv_size;
  };

  class Data: public Params {};
  class ReturnType: public Params {};
}