#include<stdio.h>          //标准输入、输出头文件
#include<string.h>          //包含字符串函数处理头文件
#include<stdlib.h>          //包含动态存储与释放函数头文件
#include<conio.h>          //包含字符串地输入、输出头文件
#define N 10000 
struct flight              //定义结构体数组
{
int flightno;
char start[10];
char end[10];
char day[10];
int totalticket;
int sellticket;
}
s[N];
int i;
int m=0;
#define PRINT "%-d%14s%13s%12s%12d%16d\n",s[i].flightno,s[i].start,s[i].end,s[i].day,s[i].totalticket,s[i].sellticket    //定义输出格式
void menu();                //进入系统菜单
void print();              //输出航班信息           
void booking();            //订票信息
void input();              //输入航班信息
void save();                //保存航班信息           
void read();                //读取航班信息
void search();              //查询航班信息
void back();                //退票信息               
void correct();            //修改信息
void menu()       
{
int  j;
printf("                  欢迎进入飞机订票管理系统!\n");
printf("======================================================================\n");
do
{
printf("                      1.录入航班信息            \n");
printf("                      2.浏览航班信息            \n");
printf("                      3.修改航班信息            \n");
printf("                      4.查询航班信息            \n");
printf("                      5.订票信息                \n");
printf("                      6.退票信息                \n");
printf("                      0.退出航班信息管理系统    \n");
printf("======================================================================\n");
printf("请在0-6中选择以回车键结束：\n");
scanf("%d",&j);
switch(j)
{
case 1: input();            //调用输入模块
break;
case 2:print();              //调用打印模块
break;
case 3:correct();            //调用修改模块
break;
case 4:search();            //调用查询模块
break;
case 5:booking();            //调用订票模块
break;
case 6:back();              //调用退票模块
break;
case 0:;
break;
}while(j!=0);                        //判断结束
printf("谢谢使用，再见!\n");
}                                    //主函数结束
void main()                          //打印主函数程序信息
{
int i,k,part1,part2;
char name[10]="dianke",password[10]={"\0"};
char person[10], c[10]="12345";
printf ("\t\t **********  欢迎进入飞机订票管理系统！**********\n\n");    //打印提示信息
printf ("\t\t     \n\n");
printf ("\t\t                  \n\n");
printf ("\t\t\t          用 户 登 录\n\n");
for(k=0;k!=3;)                                                        //打开文件并判断
{
printf("\t\t\t\t  用户名:");                                      //打印用户名
gets(person);
part1=strcmp(person,name);
printf("\t\t\t\t  密码:");                                        //打印密码
for(i=0;i<5;i++)     
{     
c[i]=getch();     
printf("*");
} 
gets(c);
part2=strcmp(c,password);
if(part1==0 && part2==0)
{
printf("\t\t\t\t  登陆成功!\n\n");
menu();
break;
}
else
{
printf ("\t\t\t      用户名或密码错误!\n\n");
printf ("\t\t\t      请注意：您还剩%d次机会!\n\n",2-k);
k++;
}
}
if (k=3)
printf ("对不起，由于您输入地用户名或密码3次有误,已被强制退出.\n");
}
void input()                                          //打印模块程序
{
int y;
printf("请依次输入航班信息:\n");                  //打印提示信息
printf("完成输入信息请键入w以回车键结束\n");     
printf("--------------------------------------------------------------------------\n");
for(i=0;i<N;i++)
{
printf("请输入航班号:\n"); 
scanf("%d",&s[i].flightno);              //读取航班号
printf("请输入起始站:\n");
scanf("%s",s[i].start);                  //读取起始站
printf("请输入终点站:\n");
scanf("%s",s[i].end);                    //读取终点站
printf("请输入时间:\n");
scanf("%s",s[i].day);                    //读取时间
printf("请输入预售票总数:\n");
scanf("%d",&s[i].totalticket);        //读取预售票数   
printf("请输入已售票总数:\n",m);
scanf("%d",&s[i].sellticket);        //读取已售票总数
m++;
printf("第%d个信息已经输完是否继续?按任意数字键继续，按0结束",m);
scanf("%d",&y);
if(y==0)
{
save();                            //将结构体信息存盘
print();                        //输出输入地航班信息
break;
}
}
}
void save()                                        //保存模块程序
{
FILE *fp,*fp1;                                    //定义文件指针
if((fp=fopen("chen.dat","wb"))==NULL)    //打开文件并判断是否出错  
{
printf("创建文件失败!\n\n");              //打印出错提示
getchar();
return;
}
if((fp1=fopen("hao.dat","wb"))==NULL)    //打开文件并判断是否出错  
{
printf("创建文件失败!\n\n");                //打印出错提示
getchar();
return;
}
for(i=0;i<m;i++)
if(fwrite(&s[i],sizeof(struct flight),1,fp)==0) //向文件写入数据，并判断是否出错
printf("向文件输入数据失败!\n\n");
fprintf(fp1,"%d",m);
fclose(fp);                                      //关闭文件
fclose(fp1);                                    //关闭文件
}
void read()                                      //从文件读取信息模块
{
FILE *fp,*fp1;                                    //定义文件指针
if((fp=fopen("chen.dat","rb"))==NULL)  //打开文件，并判断是否出错
{
printf("出错，请检查文件是否存在，按任意键返回住菜单");//打印出错提示
getchar();
}
if((fp1=fopen("hao.dat","rb"))==NULL)  //打开文件并判断是否出错  
{
printf("创建文件失败!\n\n");                //打印出错提示
getchar();
return;
}
fscanf(fp1,"%d",&m);
fclose(fp1);                                        //关闭文件
for(i=0;i<m;i++)
{
fread(&s[i],sizeof(flight),1,fp);        //从文件中读取信息
}
fclose(fp);                                        //关闭文件
}
void print()                                              //打印模块
{
char w[10];
read();                                        //调用读取文件函数
printf("航班号      起始站      终点站      时间        预售票总数      已售票总数\n");
for(i=0;i<m;i++)
{
printf(PRINT);                                    //打印信息
}
printf("请按任意键回车键结束返回上层菜单以:\n");
scanf("%s",w);
}
void search()                                            //查询模块
{
char startname[10];
char endname[10];
char day[10];
char p[10];
int n,no;
do
{
printf("请选择查询方式：\n");              //打印查询方式菜单
printf("1.按航班号查询\n");
printf("2.按起点站查询\n");
printf("3.按终点站查询\n");
printf("4.按航线查询\n");
printf("5.按飞行时间查询\n");
printf("0.返回\n");
printf("请在0-5中选择：\n");
printf("按其他键以回车键结束返回主菜单:\n");
scanf("%d",&n);                                //读取查找方式
if(n==0)
break;
switch(n)
{
case 1:
printf("请输入航班号：\n");
scanf("%d",&no);                          //航班号
break;
case 2:
printf("请输入起点站名称：\n");
scanf("%s",&startname);
break;
case 3:
printf("请输入终点站名称：\n");
scanf("%s",endname);                    //读取终点站
break;
case 4:
printf("请输入起始站名称：\n");
scanf("%s",startname);                  //读取起始站
printf("请输入终点站名称：\n");
scanf("%s",endname);                      //终点站
break;
case 5:
printf("请输入飞行时间：\n");
scanf("%s",&day);
break;
}
read();                                        //调用读取函数文档来自于网络搜索赔荊紳谘侖驟辽輩袜錈。
for(i=0;i<m;i++)
{
if(strcmp(s[i].end,startname)==0||strcmp(s[i].end,endname)==0)//按终点站起始站判断输出条件
{
printf("\n查询航班信息成功!\n");
printf("航班号      起始站      终点站      时间        预售票总数      已售票总数\n");
printf(PRINT);                            //打印信息
break;
}
if(s[i].flightno==no)                //按航班号判断输出条件
{
printf("\n查询航班信息成功!\n");
printf("航班号      起始站      终点站      时间        预售票总数      已售票总数\n");
printf(PRINT);                                //打印信息
break;
}
if(strcmp(s[i].day,day)==0)
{
printf("\n查询航班信息成功!");
printf("\n航班号        起始站        终点站        时间        剩余机票数      预售机票数\n");
printf(PRINT);//打印信息
break;
}
}
no=0;                                          //将航班号赋值为0
printf("没有您需要地信息或查找完毕：\n\n"
"是否继续查找?请键入yes或no以回车键结束\n");
scanf("%s",p);
}while(strcmp(p,"yes")==0);                          //判断结束
}
void booking()                                            //订票模块
{
int n;
char f[10];
do
{
search();                                      //调用查询模块
printf("请输入您要订地机票数以回车键结束：\n");
scanf("%d",&n);                              //读取所订机票数
if(n<0)
{
printf("请输入有效地机票数！\n");    //判断机票数是否出错
break;
}
if(s[i].totalticket!=0&&s[i].totalticket>=n)  //判断是否出错
{
s[i].totalticket=s[i].totalticket-n;
s[i].sellticket=s[i].sellticket+n;
save();                                    //调用保存函数
printf("订票成功!\n\n");
break;
}
if(s[i].totalticket<n)                        //判断是否出错
{
printf("请输入有效地机票数：\n");
break;
}
printf("是否继续？ 请输入yes或no以回车键结束:\n");  //判断是否继续订票
scanf("%s",f);
}while(!strcmp(f,"yes"));                              //判断结束
}
void back()                                              //退票模块
{
int n;
char f[10];
do
{
search();                                      //调用查询模块
printf("请输入您要退地机票数目：\n");
scanf("%d",&n);                                //输入所退票数
if(n<0)                                    //判断票数是否有效
printf("请输入有效地机票数！\n");
s[i].totalticket=s[i].totalticket+n;
s[i].sellticket=s[i].sellticket-n;
save();                                        //调用保存模块
printf("退票成功!\n\n");
printf("是否继续？ 请键入yes或no以回车键结束:\n\n");//判断是否继续退票
scanf("%s",f);
}while(!strcmp(f,"yes"));                        //判断并跳出循环
getchar();
}
void correct()                                          //修改模块
{
struct cor                                          //定义结构体 
{
int no;
char startname[10];
char endname[10];
char day[10];
int totalticket;
int sellticket;
}x[1];
char j[10];
int n;
{
read();                                        //调用读取模块
do
{
printf( "请选择修改方式：\n");
printf( "*1,按航班号修改:\n");
printf( "*2,按航线修改: \n");
printf("请在1---2中修改以回车键结束：\n");
scanf("%d",&n);                            //读取修改方式
switch(n)
{
case 1:printf("请输入航班号：\n");
scanf("%d",&x[0].no);                  //读取航班号
break;
case 2:printf("请输入起始站：\n");
scanf("%s",x[0].startname);            //读取起始站
printf("请输入终点站：\n");
scanf("%s",x[0].endname);              //读取终点站
break;
}
for(i=0;i<m;i++)
{ 
if(strcmp(s[i].end,x[0].startname)==0&&strcmp(s[i].end,x[0].endname)==0)    //判断输出条件
{
printf("航班号      起始站      终点站      时间        预售票总数      已售票总数\n");
printf(PRINT);
break;
}
if(s[i].flightno==x[0].no)        //判断输出条件
{ 
printf("航班号      起始站      终点站      时间        预售票总数      已售票总数\n");
printf(PRINT);
break;
}
}
x[0].no=0;                          //将结构体中地号为零
printf("请输入新航班号、起始站、终点站、时间（星期几）、预售票总数、已售票总数：\n");
scanf("%d%s%s%s%d%d",&x[0].no,x[0].startname,x[0].endname,x[0].day,&x[0].totalticket,&x[0].sellticket);    //定义输入格式
s[i].flightno=x[0].no;                      //替换航班号
strcpy(s[i].start,x[0].startname);          //替换其始站
strcpy(s[i].end,x[0].endname);              //替换终点站
strcpy(s[i].day,x[0].day);                  //替换时间
s[i].totalticket=x[0].totalticket;      //替换预售票总数
s[i].sellticket=x[0].sellticket;          //替换已售票总数
save();                                  //调用保存模块
printf("是否继续？请键入yes或no以回车键结束:\n\n");
scanf("%s",j);
}while(strcmp(j,"yes")==0);                      //判断结束
}
}
