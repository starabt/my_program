#!python3

import requests,bs4,xlsxwriter,time

#环境运行基础数据定义

#**********************************************************************

scriptRuningTime = time.strftime("%Y%m%d_%H%M%S", time.localtime())

outFileName = 'LotteryHistoryDataList_' + scriptRuningTime + '.xlsx'

baseWebAddress = "http://kaijiang.zhcw.com/zhcw/html/ssq"

#函数定义

#**********************************************************************

def GetWinningInfo(webaddress):

	res = requests.get(webaddress).text

	htmlinfo = bs4.BeautifulSoup(res,'html.parser')

	resultinfo_qishu = htmlinfo.select('td')

	resultinfo_haoma = htmlinfo.select('em')

	#包括每一期的期号；开奖日期等信息

	resultinfo_haomalist = str(resultinfo_haoma).replace('<em class="rr">','').replace('</em>','').replace('<em>','').replace('[','').replace(']','').split(',')

	#print(len(resultinfo_qishu))

	issuerDatas = []

	for i in range(0,len(resultinfo_qishu)-1,7):

		issuerData = []

		for j in range(0,2):

			if j == 0:

	#print('开奖日期：' + str(resultinfo_qishu[i+j]).replace('<td align="center">','').replace('</td>',''))

				a = str(resultinfo_qishu[i+j]).replace('<td align="center">','').replace('</td>','')

				issuerData.append(a)

			else:

	#print('期 号：' + str(resultinfo_qishu[i+j]).replace('<td align="center">','').replace('</td>',''))

				b = str(resultinfo_qishu[i+j]).replace('<td align="center">','').replace('</td>','')

				issuerData.append(b)

		x = []

		for n in range(0,7):

			x.append(resultinfo_haomalist[i+n])

	#print('红色球：%s,%s,%s,%s,%s,%s;蓝色球：%s' % (x[0],x[1],x[2],x[3],x[4],x[5],x[6]))

			issuerData.append(x)

			issuerDatas.append(issuerData)

	return issuerDatas

#main

#**********************************************************************

#TODO:获取总的页码数量

numberOfPages = 113 #如果有兴趣可以尝试将这个数字也从网站中获取。

#创建Excel文件并写入表头

workbook = xlsxwriter.Workbook(outFileName)

worksheet = workbook.add_worksheet('Lottery')

worksheet.hide_gridlines(2)

tableHeader = ["NO.","开奖日期","期 号","红球1","红球2","红球3","红球4","红球5","红球6","蓝球1",]

a = workbook.add_format({'border': 1, 'font_size': 20, 'bold': True, 'align': 'center','bg_color': 'ccccc0'})

b = workbook.add_format({'border': 1, 'font_size': 13,'align': 'left','bg_color': '5F9EA0'})

c = workbook.add_format({'border': 1, 'font_size': 13,'align': 'left','bg_color': 'D2B48C'})

worksheet.write_row('A1', tableHeader,a)

#开始逐个网页爬取数据

i = 0

for e in range(1,numberOfPages+1):

	print('--------这是第%s页--------' % e)

	realWebAddress = baseWebAddress + '/list_'+ str(e) + '.html'

	resultall = GetWinningInfo(realWebAddress)

	for everyIssuerData in resultall:

		i = i + 1

		cellPos1 = 'A' + str(i+1)

		cellPos2 = 'B' + str(i+1)

#小细节把抓取的数据写入前转换成数字格式

		cellValue = [everyIssuerData[0],int(everyIssuerData[1]),int(everyIssuerData[2][0]),int(everyIssuerData[2][1]),int(everyIssuerData[2][2]),int(everyIssuerData[2][3]),int(everyIssuerData[2][4]),int(everyIssuerData[2][5]),int(everyIssuerData[2][6])]

		if (i % 2) == 0:

			worksheet.write(cellPos1,i,b)

			worksheet.write_row(cellPos2, cellValue,b)

		else:

			worksheet.write(cellPos1,i,c)

			worksheet.write_row(cellPos2, cellValue,c)

#增加一个Sheet

chartSheet = workbook.add_worksheet('Chart')

#增加一个折线图图表对象

chart_col = workbook.add_chart({'type': 'line'})

name = '=%s!$J$1' % 'Lottery'

categories = '=%s!$B$2:$B$%s' % ('Lottery',(i + 1))

values = '=%s!$J$2:$J$%s' % ('Lottery',(i + 1))

print('%s|%s|%s' % (name,categories,values))

chart_col.add_series({

# 这里的sheet1是默认的值，因为我们在新建sheet时没有指定sheet名

# 如果我们新建sheet时设置了sheet名，这里就要设置成相应的值

'name': name,

'categories': categories,

'values': values,

'line': {'color': 'blue'},

})

chart_col.set_title({'name': '蓝色球分析'})

chart_col.set_x_axis({'name': '开奖日期'})

chart_col.set_y_axis({'name': 'BlueNumber'})

chart_col.set_style(1)

chartSheet.insert_chart('B2', chart_col)

chart_col.set_size({'width': 10000, 'height': 500})

workbook.close()