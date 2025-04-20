#ifndef EASYCPP_JSONOPERATOR_H
#define EASYCPP_JSONOPERATOR_H

#include "FileOperator.h"
#include <string>

namespace easycpp {
    // 读取 JSON 文件，返回 json 数据字符串；失败时抛出异常
    EASYCPP_API std::string loadJson(char * filename);

    // 保存 json 数据到文件，返回写入的字节数；失败时抛出异常
    EASYCPP_API int saveJson(char * filename, const std::string &json);
}

#endif // EASYCPP_JSONOPERATOR_H
