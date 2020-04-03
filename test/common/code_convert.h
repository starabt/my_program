/***********************************************************
    Copyright (C), 2016,Guang Zhou Tongda auto electric Co., Ltd.
    File name:      code_convert.H
    Author:         Gao Zhigang
    Version:        1.0
    Date:           2016/07/27
    Description:    转换字符编码函数
    History:
        Date            Author          Version       Modification
*************************************************************/
#ifndef _CODE_CONVERT_H_
#define _CODE_CONVERT_H_

#include <iconv.h>
#include <errno.h>
#include <locale.h>
#include <stdio.h>

class CCodeConverter
{
public:
    CCodeConverter(const char * fromCode, const char * toCode);
    ~CCodeConverter();
    //转换函数
    int convert(char * srcBuf, int srcLen, char * destBuf, int destLen);
    //获取错误信息
    int getErrInfo();

private:
    //转换句柄
    iconv_t hCodeConverter;
    int nErr;
};
#endif //_CODE_CONVERT_H_