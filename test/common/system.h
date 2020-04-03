/*
 * system.h
 *
 *  Created on: Dec 16, 2016
 *      Author: root
 */

#ifndef COMMON_SYSTEM_H_
#define COMMON_SYSTEM_H_


// 执行shell指令
int ExeSysShellCmd(const char *cmd, char *result);

// 格式化硬盘
int FormatDisk(const char *dev);
// 强制退出占用挂载目录
int ForceUmmout(const char *dir);

#endif /* COMMON_SYSTEM_H_ */
