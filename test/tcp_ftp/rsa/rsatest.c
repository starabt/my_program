




//将十进制数转换成二进制，用于检验大素数p和q 

int t,temp=-1; 

while(b>0){ 
 t=b%2; 
 temp++; 
 a[temp]=t; 
 b=b/2; 
}  
return temp; 


欧几里得算法，用于判断加密指数e是否符合要求 


int r1=n,r2=b,r; 
while(r2>0){ 
 r=r1%r2; 
 r1=r2; 
 r2=r; 
} 
return r1; 


扩展欧几里得算法求乘法逆元，即求解密指数d 


int q,r,r1=n,r2=b,t,t1=0,t2=1,i=1; 
 while(r2>0) 
 { 
  q=r1/r2; 
  r=r1%r2; 
  r1=r2;   r2=r; 
  t=t1-q*t2; 
  t1=t2; 
  t2=t; 
 } 
 if(t1>=0)   return t1%n; 
 else{ 
  while((t1+i*n)<0) 
   i++; 
  return t1+i*n; 
 } 


检验大素数，符合要求返回1，否则返回0 


int d=1,k,r=n-1,i,x,b[1000]; 
k=zhuan_huan(r,b,1000); 
for(i=k;i>=0;i--){ 
 x=d; 
 d=(d*d)%n; 
 if((d==1)&&(x!=1)&&(x!=n-1)) return 0; 
  if(b[i]==1)  d=(d*a)%n; 
} 
if(d!=1) return 0; 
else return 1; 


快速计算模指数 


int x=0,y=1,k,i,s[1000]; 
k=zhuan_huan(b,s,1000); 
for(i=k;i>=0;i--){ 
 x=2*x; 
 y=(y*y)%n; 
 if(s[i]==1){ 
  x++; 
  y=(y*a)%n; 
 } 
} 
return y; 



主函数。。。。。。。。。。。。。。。。。。。。。。。。。。。。。。。。。。。。。。。。。。。 


int p,q,e,d,n,yn,m[1000],c[10000];//c[10000]存放加密后的数字密文，m[1000]存放解密后
zimu_biao[69]中的下标。 
int i,j;  //i,j用于循环遍历数组 
int mi_yue;  //用户输入的密钥 
int count=1; //统计输入密钥的次数，count>3时将不允许用户再输入。 
char min_wen[1000],re_min_wen[1000];//分别为用户输入的明文、密文，解密后的明文。 
密钥生成 
char 


printf("请输入您要发送的明文文件（小写英文表示）:\n"); 
printf("******************************************************\n"); 
gets(min_wen); 
printf("******************************************************\n"); 
printf("\n加密开始，请按要求操作。。。\n\n"); 
printf("请输入第一个大素数p：\n"); 
while(1){ 
  scanf("%d",&p); 
  if(Witness(2,p)==1){ 
   printf("您输入的第一个大素数 %d 符合要求\n",p);  
   break; 
  } 
  else 
   printf("您输入的 %d 不是素数,请重新输入：\n",p); 
} 
printf("请输入第二个大素数q：\n"); 
while(1){ 
  scanf("%d",&q); 
  if(Witness(2,q)){ 
   printf("您输入的第二个大素数 %d 符合要求\n",q);  
   break; 
  } 
  else 
   printf("您输入的 %d 不是素数,请重新输入：\n",q); 
} 

n=p*q; yn=(p-1)*(q-1); 

printf("请输入加密指数（整数）e,且0<e<%d\n",yn);//下面由用户设定加密指数 
while(1){ 
  scanf("%d",&e); 
  if(gcd(yn,e)==1){ 
   printf("您输入加密指数 %d 与 %d 互素,符合要求\n",e,yn);  
   break; 
  } 
  else 
   printf("您输入加密指数 %d 与 %d 不互素,请重新输入。。。\n",e,yn); 
} 

d=extend(yn,e);  //求解密指数d 
printf("\n\n请记住您的两个大素数分别为p=%d(保密),q=%d(保密),模数n=%d(公开),欧
函数yn=%d(保密),加密指数e=%d(公钥,公开),。。。解密指数 d=%d(私钥,保
)\n\n",p,q,n,yn,e,d); 
明文转换过程 

scanf("%s",min_wen);  
printf("%s",min_wen); */ 
 for(i=0;i<strlen(min_wen);i++) 
   for(j=0;j<68;j++) //for(j=0;j<26;j++) 
     if(min_wen[i]==zimu_biao[j]) 
      m[i]=j;//将字符串明文换成数字，并存到整型数组m里面，即明文的
 

加密过程 
for(i=0;i<strlen(min_wen);i++) 
 c[i]=js_mod(m[i],e,n); 
printf("输出密文：\n"); 
printf("******************************************************\n"); 
for(i=0;i<strlen(min_wen);i++) 
 printf("%d",c[i]); 
printf("\n******************************************************\n"); 

解密过程 
for(i=0;i<strlen(min_wen);i++) 
 m[i]=js_mod(c[i],d,n); 
for(i=0;i<strlen(min_wen);i++) 
 re_min_wen[i]=zimu_biao[m[i]]; 

提示用户解密 
printf("\n\n您有3次输入密钥的机会，密钥正确后将进行解密显示明文，3次输入错误
。。\n\n"); 
while(1){ 
  scanf("%d",&mi_yue); 
  if(mi_yue==d){ 
   printf("密钥输入正确，您得到的明文为：\n\n"); 
   for(i=0;i<strlen(min_wen);i++) 
    printf("%c",re_min_wen[i]);  
   printf("\n\n"); 
   break; 
  } 
  else{ 
   printf("您第%d次输入的密钥错误，请重新输入。。。\n",count); 
   count++; 
   if(count>3){ 
    printf("\n您已%d次输入的密钥错误，将不允许继续输入\n",count-1); 
    break; 
  } 
 }   
}   
