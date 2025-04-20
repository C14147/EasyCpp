#include"EasyCpp.h"
#include"FileOperator/FileOperator.h"
#include"String/String.h"
#include"FuncOptimize/func_io.h"
using namespace easycpp;

int main(){
    // File I/O & String Class Test
    File* a = open("test.txt","a+");
    a->write(
        String("hello world, this is a test\n你好\(@^0^@)/，{}！\n")
        .format((STRING_FOMATER)String("EasyCpp")) +
		String("EasyCpp Version: ") + String(_EASYCPP_VERSION) +
		String("\nFileOperator Version: {}\nString Version: {}")
		.format(_EASYCPP_FILEOPERATOR_VERSION, _EASYCPP_STRING_VERSION)
    );
    String(a->read_());
}
