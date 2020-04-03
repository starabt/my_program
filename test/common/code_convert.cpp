/***********************************************************
    Copyright (C), 2016,Guang Zhou Tongda auto electric Co., Ltd.
    File name:      code_convert.cc
    Author:         Gao Zhigang
    Version:        1.0
    Date:           2016/07/27
    Description:    转换字符编码函数
    History:
        Date            Author          Version       Modification
*************************************************************/
#include "code_convert.h"
CCodeConverter::CCodeConverter(const char * fromCode, const char * toCode)
{
    hCodeConverter = iconv_open(toCode, fromCode);
}

CCodeConverter::~CCodeConverter()
{
    iconv_close(hCodeConverter);
}

/*************************************************
    Function:       convert()
    Description:    转换函数.
*************************************************/
int CCodeConverter::convert( char * srcBuf, int srcLen, char * destBuf, int destLen)
{
    //返回转换的字符个数
    int nConv=iconv(hCodeConverter, &srcBuf, (size_t *)&srcLen, &destBuf, (size_t *)&destLen);
    //如果错误，则获取错误码
    nErr=errno;
    return nConv;
}

/*************************************************
    Function:       getErrInfo()
    Description:    获取错误信息.
*************************************************/
int CCodeConverter::getErrInfo()
{
    switch (nErr)
    {
    case E2BIG:
    {
        printf("errno:E2BGI（OutBuf空间不够）\n");
        break;
    }
    case EILSEQ:
    {
        printf("errno:EILSEQ（InBuf多字节序无效）\n");
        break;
    }
    case EINVAL:
    {
        printf("errno:EINVAL（有残留的字节未转换）\n");
        break;
    }
    default:
        break;
    }
    return nErr;
}
