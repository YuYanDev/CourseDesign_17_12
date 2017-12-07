#include "json.hpp"
#include <fstream>
#include <iostream>
#include <sstream>
#include <stdlib.h>
#include <string>
#include <time.h>
#include <vector>
#include <unistd.h>

using namespace std;
using json = nlohmann::json;

/**
 * 筛选出单词
 */

vector<string> split(const string &s, const string &seperator) {
  vector<string> result;
  typedef string::size_type string_size;
  string_size i = 0;

  while (i != s.size()) {
    //找到字符串中首个不等于分隔符的字母；
    int flag = 0;
    while (i != s.size() && flag == 0) {
      flag = 1;
      for (string_size x = 0; x < seperator.size(); ++x)
        if (s[i] == seperator[x]) {
          ++i;
          flag = 0;
          break;
        }
    }

    //找到又一个分隔符，将两个分隔符之间的字符串取出；
    flag = 0;
    string_size j = i;
    while (j != s.size() && flag == 0) {
      for (string_size x = 0; x < seperator.size(); ++x)
        if (s[j] == seperator[x]) {
          flag = 1;
          break;
        }
      if (flag == 0)
        ++j;
    }
    if (i != j) {
      result.push_back(s.substr(i, j - i));
      i = j;
    }
  }
  return result;
}

//从文件读入到string里
string readFileIntoString(char *filename) {
  ifstream ifile(filename);
  //将文件读入到ostringstream对象buf中
  ostringstream buf;
  char ch;
  while (buf && ifile.get(ch))
    buf.put(ch);
  //返回与流对象buf关联的字符串
  return buf.str();
}

//大小写转换
void StringB2S(char *str) {
  int len = strlen(str);
  for (int i = 0; i < len; ++i) {
    if (str[i] >= 'A' && str[i] <= 'Z') {
      str[i] = str[i] + 32;
    }
  }
}

int main(int argc, char *argv[]) {
  // 获取目录
  char DirString[80];
  getcwd(DirString, sizeof(DirString));

  clock_t loadfile_start_time = clock();
  //文件名
  char *fn = argv[1];

  //建立json结构体
  json StringCount;

  //读取字符串
  string str;
  str = readFileIntoString(fn);

  //拆分字符串
  vector<string> v = split(str, ", .\n()“”'\"" "`- \/ ! * \r \\ $ ; : ? [ ]");

  //构造json
  for (vector<string>::size_type i = 0; i != v.size(); ++i) {
    // string 转 char
    char *p;
    const int len = v[i].length();
    p = new char[len + 1];
    strcpy(p, v[i].c_str());

    //大小写转换
    StringB2S(p);

    // 只统计单词
    if(p[0]>=97&&p[0]<=122){
      //统计并填入json
      if (StringCount[p].is_null()) {
        StringCount[p] = 1;
      } else {
        int number = StringCount.at(p).get<int>();
        StringCount[p] = StringCount.at(p).get<int>() + 1;
      }

    }
  }
  clock_t loadfile_end_time = clock();
  int i;
  system("clear");
  printf("+---------------------------------------------------------+\n");
  printf("|                       文章单词统计                      |\n");
  printf("+---------------------------------------------------------+\n");
  printf("| 读取文章:\n| %s\/%s \n",DirString,fn);
  cout << "| 文章载入耗时: "
       << static_cast<double>(loadfile_end_time - loadfile_start_time) /
              CLOCKS_PER_SEC * 1000
       << "ms" << endl;
start:
  printf("+---------------------------------------------------------+\n");
  printf("|1 | 按单词查询                                           |\n");
  printf("+--+------------------------------------------------------+\n");
  printf("|2 | 全部显示                                             |\n");
  printf("+--+------------------------------------------------------+\n");
  printf("|3 | 导出JSON                                             |\n");
  printf("+--+------------------------------------------------------+\n");
  printf("|4 | 退出                                                 |\n");
  printf("|---------------------------------------------------------|\n");
  printf("|请输入菜单选项:                                          |\n");
  scanf("%d", &i);
  if (i < 1 || i > 4) {
    system("clear");
    printf("+---------------------------------------------------------+\n");
    printf("| 输入错误,请重输:                                        |\n");
    goto start;
  }
  switch (i) {
  case (1): {
    system("clear");
    // InquireWords();
    string Words;
    printf("+---------------------------------------------------------|\n");
    printf("| 请输入单词                                              |\n");
    // scanf("%s",&Words);
    clock_t start_time = clock();
    cin >> Words;
    char *Word;
    const int len = Words.length();
    Word = new char[len + 1];
    strcpy(Word, Words.c_str());

    if (StringCount[Word].is_null()) {
      system("clear");
      printf("+---------------------------------------------------------|\n");
      printf("| 没有该单词                                              |\n");
      printf("+---------------------------------------------------------|\n");
      printf("| 请输入单词                                              |\n");
      printf("+---------------------------------------------------------|\n");
      printf("\n");
    } else {
      system("clear");
      int number = StringCount.at(Word).get<int>();
      printf("+---------------------------------------------------------|\n");
      printf("| %s 共计%d个\n", Word, number);
      clock_t end_time = clock();
      printf("+---------------------------------------------------------|\n");
      cout << "| 查询耗时: "
           << static_cast<double>(end_time - start_time) / CLOCKS_PER_SEC * 1000
           << "ms" << endl;
      printf("+---------------------------------------------------------|\n");
      printf("\n");
    }
    goto start;
    break;
  }
  case (2): {
    system("clear");
    // InquireAll();
    printf("+---------------------------------------------------------|\n");
    clock_t start_time = clock();
    for (json::iterator it = StringCount.begin(); it != StringCount.end(); ++it) {
      std::cout << "| " << it.key() << " 共计 " << it.value() << "个\n";
      printf("+---------------------------------------------------------|\n");
    }
    clock_t end_time = clock();
    printf("\n");
    printf("\n");
    printf("+---------------------------------------------------------|\n");
    cout << "| 输出完毕, 耗时: "
         << static_cast<double>(end_time - start_time) / CLOCKS_PER_SEC * 1000
         << "ms" << endl;
    printf("+---------------------------------------------------------|\n");
    printf("| Console输出查看不完整，建议导出JSON查看                 |\n");
    printf("+---------------------------------------------------------|\n");
    printf("\n");
    goto start;
    break;
  }
  case (3): {
    system("clear");
    // InquireAll();
    printf("+---------------------------------------------------------|\n");
    clock_t start_time = clock();
    // for (json::iterator it = StringCount.begin(); it != StringCount.end(); ++it) {
    //   std::cout << "| " << it.key() << " 共计 " << it.value() << "个\n";
    //   printf("+---------------------------------------------------------|\n");
    // }
    ofstream out("output.json");
    out<<StringCount.dump()<<endl;
    out.close();
    // std::ofstream StringCount("pretty.json");
    clock_t end_time = clock();
    // printf("| 导出JSON成功,保存为 :\n| %s\/pretty.json\n",DirString);
   
    cout << "| 输出耗时: "
         << static_cast<double>(end_time - start_time) / CLOCKS_PER_SEC * 1000
         << "ms" << endl;
    printf("| 导出JSON成功,保存为 :\n| %s\/output.json\n",DirString);
    printf("+---------------------------------------------------------|\n");
    printf("\n");
    goto start;
    break;
  }
  case (4): {
      system("clear");
    }
  }

  return 0;

}