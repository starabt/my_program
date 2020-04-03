/**************************************************************************************
    AppName:    RSA.cpp
    Description:    RSA encrypt and decrypt
    Auther:     Lu xican 
    Usage:      README.txt

                                                                                      
************************************************************************************/
*此程序为AES-128加密，密钥为128bits 即16bytes，自行设定，引用KeyExpansion()进行密钥扩展得到44字扩展密钥，分别用于11轮密钥加
                                                                                      
* 使用此程序进行AES128加解密，只需引用encryptlong（）进行加密，decryptlong（）进行解密，KeyExpansion()进行密钥扩展;

*编译时将此cpp文件和AES.h包含进去即可。此加密程序已在AES.h中包装成AES类，引用时需先定义一个AES类对象；
                                                                                    
* 本程序中有一个main（）函数示例，实际引用时请将其删除。     