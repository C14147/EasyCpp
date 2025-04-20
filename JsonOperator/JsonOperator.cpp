#ifndef EASYCPP_JSONOPERATOR_H
#define EASYCPP_JSONOPERATOR_H

#include <string>
#include "FileOperator.h"

namespace easycpp {

  // 从文件中加载 json 数据
  std::string loadJson(char * filename);

  // 将 json 数据写入文件
  int saveJson(char * filename, const std::string &json);

}

#endif // EASYCPP_JSONOPERATOR_H