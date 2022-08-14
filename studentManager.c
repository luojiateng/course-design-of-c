#include<stdio.h>
#include<stdlib.h>
#include<windows.h>//windows环境下控制光标
#include<string.h>
#include<malloc.h>
#define LEN sizeof(struct timetable)//测结构体的长度
//定义一个关于课程信息的结构体
typedef struct timetable
{
    int ID;//课号
    char name[20];//课名
    char type[20];//类型
    int A_time;//总学时
    int T_time;//授课学时
    int D_time;//实验或上机学时
    int score;//学分
    float year;//学年2020年第一学期2020.1
    struct timetable* next;//指向下一个的指针
}timetable;
//所有的函数
void luojiateng();//自我介绍的页面
void begin_ui();//开始的界面
void all_ui();//整体界面，外观框架
void MoveCursor(int x, int y);//设置光标的位置
void lookup_ui();//课程查找界面
void login_ui();//登录界面（二选一结果）
int login();//登录密码处理
void S_choose_ui();//学生登录以后的界面(如果返回S)
void choose();//学生选课操作界面
void S_see();//学生查看选课结果的界面
void T_choose_ui();//管理员登录以后的界面（如果返回T)
void T_see();//管理员查看选课结果的界面
void change();//学生修改选课界面
void T_input();//管理员输入数据的界面
void T_change();//管理员修改选课数据界面
void logins();//密码登录系统密码
void class();//输入课程
void score_lookup();//以学分形式查看
void type_lookup();//以类型方式查看
void add();//学生加课
void delete();//学生删课
void T_dele();//管理员删课
void T_increase();//管理员加课
timetable* input();//课程数据输入
void output(timetable* head);//输出函数
void output_2(timetable *head); //专门打印选修课的课表
timetable* lookfor(timetable* head, int LID);//查找数据
timetable* dele(timetable* head, int DID);//删除该号码下的课程数据
timetable* increase(timetable* head, int AID);//增加一组值
timetable *new_list();//从文件得到一个新的课程的动态链表
timetable *S_new_list();//从文件得到一个新的学生选课结果的动态链表
void save(timetable *head);//将课程的动态链表数据保存至文件
void S_save(timetable *head);//将学生的动态链表保存至文件
//======================================================================
int i;
int main()
{
    // luojiateng();//自我介绍界面
    begin_ui();//开始界面
    system("pause");//防止闪屏
    return 0;//结束程序
}
//================================界面及外观=============================
//自我介绍界面UI
void luojiateng()
{
    all_ui();
    MoveCursor(21, 10);//在第21列第10行打印下面的东西
    printf("您好！欢迎观看我的C语言课设\n");
    printf("\n");
    MoveCursor(21, 12);
    printf("姓名：骆家腾\n");
    MoveCursor(21, 13);
    printf("班级：通信1902\n");
    MoveCursor(21, 14);
    printf("学号：201907020223\n");
    MoveCursor(21, 15);
    printf("时间：2020年6月\n");
    MoveCursor(21, 19);
    printf("请稍等......\n");
    int i;
    for (i = 0; i <= 2000000000; i++) {}//等待一会
    system("cls");//将屏幕刷新
}
//开始的屏幕UI
void begin_ui()
{
    all_ui();
    int tip;
    printf("\n");
    MoveCursor(21, 10);
    printf("欢迎进入西安石油大学选课系统 V1.0\n");
    printf("\n");
    MoveCursor(21, 12);
    printf("1:登录\n");
    MoveCursor(21, 13);
    printf("2:课程查找\n");
    MoveCursor(21, 14);
    printf("0:退出\n");
    MoveCursor(21, 16);
    printf("请选择您的操作： ");
    scanf("%d", &tip);
    switch (tip)
    {
    case 1:system("cls");login_ui();break; //转到登录界面
    case 2:system("cls");lookup_ui();break;
    case 0:exit(0); //结束程序
    default:
        MoveCursor(21, 20);
        printf("请选择正确的指令\n");
        for (i = 0; i <= 500000000; i++) {}
        system("cls");begin_ui();break;
    }//system（cls）是C语言的清屏函数，将屏幕刷新
}//绘制初始界面
//整体的外观框架UI-------------------待定
void all_ui()
{
    MoveCursor(15, 6);
    printf("  *================================================*\n");
    printf("\t\t\t\t‖\t\t\t\t\t\t‖\n");
    printf("\t\t\t\t‖\t\t\t\t\t\t‖\n");
    printf("\t\t\t\t‖\t\t\t\t\t\t‖\n");
    printf("\t\t\t\t‖\t\t\t\t\t\t‖\n");
    printf("\t\t\t\t‖\t\t\t\t\t\t‖\n");
    printf("\t\t\t\t‖\t\t\t\t\t\t‖\n");
    printf("\t\t\t\t‖\t\t\t\t\t\t‖\n");
    printf("\t\t\t\t‖\t\t\t\t\t\t‖\n");
    printf("\t\t\t\t‖\t\t\t\t\t\t‖\n");
    printf("\t\t\t\t‖\t\t\t\t\t\t‖\n");
    printf("\t\t\t\t‖\t\t\t\t\t\t‖\n");
    printf("\t\t\t\t‖\t\t\t\t\t\t‖\n");
    printf("\t\t\t\t‖\t\t\t\t\t\t‖\n");
    printf("\t\t\t\t‖\t\t\t\t\t\t‖\n");
    printf("\t\t\t\t*================================================*\n");
}
//课程查找界面UI
void lookup_ui()
{
    all_ui();
    int tip;
    MoveCursor(21, 10);
    printf("课程查找界面：\n");
    MoveCursor(21, 12);
    printf("1:按照学分查找\n");
    MoveCursor(21, 13);
    printf("2:按照课程性质查找\n");
    MoveCursor(21, 14);
    printf("3:退出\n");
    MoveCursor(21, 16);
    printf("请选择您的操作： ");
    scanf("%d", &tip);
    switch (tip)
    {
    case 1:system("cls");score_lookup();break;//学分查找界面
    case 2:system("cls");type_lookup();break;//类型查找界面
    case 3:system("cls");begin_ui();break;
    default:printf("请选择正确的操作方式\n");break;
    }
}
//按照学分查找界面
void score_lookup()
{
    all_ui();
    timetable *p1;
    p1 = new_list();
    int tip;
    MoveCursor(21, 10);
    printf("以学分查找\n");
    MoveCursor(21, 12);
    printf("1:0~5分\n");
    MoveCursor(21, 13);
    printf("2:6~8分\n");
    MoveCursor(21, 14);
    printf("3:9~12分\n");
    MoveCursor(21, 15);
    printf("0:退出\n");
    MoveCursor(21, 17);
    printf("请选择您的操作： ");
    scanf("%d", &tip);
    printf("最终的结果是:\n");
    switch (tip)
    {
    case 1:
        while (p1!=NULL)
        {
            if(p1->score>0 && p1->score<=5)
            {
                printf("|%d |%s  |%s  |%d  |%d  |%d  |%d  |%f  |\n", p1->ID, p1->name, p1->type, p1->A_time, p1->T_time, p1->D_time, p1->score, p1->year);  
            }
            p1 = p1->next;
        }
        break;
    case 2:
        if(p1->score>5 && p1->score<=8)
        {
            printf("|%d |%s  |%s  |%d  |%d  |%d  |%d  |%f  |\n", p1->ID, p1->name, p1->type, p1->A_time, p1->T_time, p1->D_time, p1->score, p1->year);  
        }
        p1 = p1->next;
        break;
    case 3:
        if(p1->score>8 && p1->score<=12)
        {
            printf("|%d |%s  |%s  |%d  |%d  |%d  |%d  |%f  |\n", p1->ID, p1->name, p1->type, p1->A_time, p1->T_time, p1->D_time, p1->score, p1->year);  
        }
        p1 = p1->next;
        break;
    case 0:system("cls");lookup_ui();break;
    default:break;
    }
    int t;
    printf("\n");
    printf("0:返回上一界面\n");
    printf("\n");
    printf("请选择操作：");
    scanf("%d", &t);
    switch (t)
    {
    case 0:system("cls");begin_ui();break;
    default:printf("请选择正确的指令\n");
        int i;
        for (i = 0; i <= 500000000; i++) {}
        system("cls");begin_ui();break;
    }
}
//按照类型查找界面
void type_lookup()
{
    all_ui();
    timetable *p1;
    p1 = new_list();
    int tip;
    MoveCursor(21, 10);
    printf("以课程类型查找\n");
    MoveCursor(21, 12);
    printf("1：必修课(com)\n");
    MoveCursor(21, 13);
    printf("2：选修课(ele)\n");
    MoveCursor(21, 14);
    printf("3：公共课(pub)\n");
    MoveCursor(21, 15);
    printf("0：退出\n");
    MoveCursor(21, 17);
    printf("请选择您的操作： ");
    scanf("%d", &tip);
    printf("最终的结果是:\n");
    switch (tip)
    {
    case 1:
        while (p1!=NULL)
        {
            if(strcmp("com",p1->type)==0)
            {
                printf("|%d |%s  |%s  |%d  |%d  |%d  |%d  |%f  |\n", p1->ID, p1->name, p1->type, p1->A_time, p1->T_time, p1->D_time, p1->score, p1->year);  
            }
            p1 = p1->next;
        }
        break;
    case 2:
        while (p1!=NULL)
        {
            if(strcmp("ele",p1->type)==0)
            {
                printf("|%d |%s  |%s  |%d  |%d  |%d  |%d  |%f  |\n", p1->ID, p1->name, p1->type, p1->A_time, p1->T_time, p1->D_time, p1->score, p1->year);  
            }
            p1 = p1->next;
        }
        break;
    case 3:
        while (p1!=NULL)
        {
            if(strcmp("pub",p1->type)==0)
            {
                printf("|%d |%s  |%s  |%d  |%d  |%d  |%d  |%f  |\n", p1->ID, p1->name, p1->type, p1->A_time, p1->T_time, p1->D_time, p1->score, p1->year);  
            }
            p1 = p1->next;
        }
        break;
    case 0:system("cls");lookup_ui();break;
    default:break;
    }
    int t;
    printf("\n");
    printf("0:返回上一界面\n");
    printf("\n");
    printf("请选择操作：");
    scanf("%d", &t);
    switch (t)
    {
    case 0:system("cls");begin_ui();break;
    default:printf("请选择正确的指令\n");
        for (i = 0; i <= 500000000; i++) {}
        system("cls");begin_ui();break;
    }
}
//设置光标位置
void MoveCursor(int x, int y)
{
    /*  COORD是Windows API中定义的一种结构体
    * typedef struct _COORD
    * {
    * SHORT X;
    * SHORT Y;
    * } COORD;
    *  */
    COORD pos = { x * 2,y };
    HANDLE output = GetStdHandle(STD_OUTPUT_HANDLE);//获得 标准输出的句柄   
    SetConsoleCursorPosition(output, pos); //设置控制台光标位置
}
//==============================登录======================================
//账号登录界面的UI
void login_ui()
{
    all_ui();
    int n;
    n = login();
    switch (n)
    {
    case 1:
        system("cls");//清理旧屏幕
        T_choose_ui();//调用管理员登录以后的界面
        break;
    case 2:
        system("cls");//清理旧屏幕
        S_choose_ui();//调用学生登陆以后界面
        break;
    default:
        break;
    }
}
//登录系统密码判断操作
int login()
{
    int n;
    int zhanghao, mima;
    printf("学生1，管理员2");
    MoveCursor(21, 12);
    printf("账号：");
    MoveCursor(21, 14);
    printf("密码：");
    MoveCursor(24, 12);
    scanf("%d", &zhanghao);//输入账号和密码
    MoveCursor(24, 14);
    scanf("%d", &mima);
    if (zhanghao == 1 && mima == 1)
    {
        n = 2;//暂时内定学生的账号2019 密码9012
    }
    else if (zhanghao == 2 && mima == 2)
    {
        n = 1;//暂时内定管理员的账号1951 密码1591
    }
    else
    {
        n = 0;//密码错误的情况
    }
    switch (n)
    {
    case 1:
        return 1;//1是管理员
        break;
    case 2:
        return 2;//2是学生
        break;
    case 0:
        system("cls");
        printf("您输入的密码有误，请重试！\n");
        printf("\n");
        login();
        break;
    default:
        MoveCursor(20, 15);
        printf("请检查您的输入是否正确\n");
        break;
    }
}
//================================学生操作==================================
//学生登录以后的界面UI
void S_choose_ui()
{
    all_ui();
    timetable *p1;
    int tip;
    MoveCursor(21, 10);
    printf("同学您好，欢迎进入学生选课界面\n");
    MoveCursor(21, 12);
    printf("1:选择课程\n");
    MoveCursor(21, 13);
    printf("2:修改选课\n");
    MoveCursor(21, 14);
    printf("3:查看选课结果\n");
    MoveCursor(21, 15);
    printf("0:退出\n");
    MoveCursor(21, 17);
    printf("请选择您的操作： ");
    scanf("%d", &tip);
    switch (tip)
    {
    case 1:
        system("cls");
        choose();
        p1 = S_new_list();
        output(p1);
        break;
    case 2:
        system("cls");
        change();
        break;
    case 3:
        system("cls");
        S_see();
        break;
    case 0:
        system("cls");
        begin_ui();
        break;
    default:
        break;
    }
}
//学生选课的操作-------------待定
void choose()
{
    FILE *write = fopen("student_class.txt", "w+");
    printf("这是选修课的课表：\n");
    timetable *p,*p1,*p2,*top;
    top=p = new_list();
    output_2(p);
    // MoveCursor(20, 10);
    while (p!=NULL)
    {
        if(strcmp("com",p->type)==0||strcmp("pub",p->type)==0)
        {
            fprintf(write, "|%d |%s  |%s  |%d  |%d  |%d  |%d  |%f  |\n", p->ID, p->name, p->type, p->A_time, p->T_time, p->D_time, p->score, p->year);
        }
            p = p->next;        
    }
    p = top;
    int sum = 0;
    while (p!=NULL)
    {
        if(strcmp("com",p->type)==0||strcmp("pub",p->type)==0)
        {
            sum = sum + p->score;
        }
        p = p->next;        
    }
    p = top;
    int i, LID,tip;
    printf("输入编号，输0结束\n");
    for (i = 0;; i++)
    {
        printf("请选择您本学期要上的选修课：");
        scanf("%d", &LID);
        if (LID == 0)
        {
            if(sum>15)
            {
                break;
            }
            else
            {
                printf("你的学分不够，继续选课！\n");
                continue;
            }           
        }
        p1 = lookfor(p, LID);
        if(p1->ID==0)
        {
            printf("没有这个课：\n");
            continue;
        }
        fprintf(write, "|%d |%s  |%s  |%d  |%d  |%d  |%d  |%f  |\n", p1->ID, p1->name, p1->type, p1->A_time, p1->T_time, p1->D_time, p1->score, p1->year);
        sum = sum + p1->score;
        printf("你现在的学分总计：%d分\n", sum);
    }
    fprintf(write, "|%d |%d  |%d  |%d  |%d  |%d  |%d  |%d  |\n", 0, 0, 0, 0, 0, 0, 0, 0);
    fclose(write);
    printf("您选课的结果是：\n");
    p2 = S_new_list();
    output(p2);
    printf("您已完成选课！\n");
    printf("\n");
    printf("0:返回上一界面\n");
    printf("1:退出程序\n");
    printf("\n");
    printf("请选择操作：");
    scanf("%d", &tip);
    switch (tip)
    {
    case 0:
        system("cls");
        S_choose_ui();//返回上一界面
        break;
    case 2:
        exit(0);
        break;

    default:
        printf("请选择正确的指令\n");
        int i;
        for (i = 0; i <= 500000000; i++) {}
        system("cls");//刷新屏幕
        begin_ui();
        break;
    }
}
//学生更改选课的界面UI
void change()
{
    all_ui();
    int tip;
    MoveCursor(20, 10);
    printf("同学您已进入选课结果修改页面\n");
    MoveCursor(20, 12);
    printf("1:增加课程\n");
    MoveCursor(20, 13);
    printf("2:删除已选课程\n");
    MoveCursor(20, 14);
    printf("0:退出\n");
    MoveCursor(20, 16);
    printf("请选择您的操作： ");
    scanf("%d", &tip);
    switch (tip)
    {
    case 1:
        system("cls");
        add();
        break;
    case 2:
        system("cls");
        delete();
        break;
    case 0:
        system("cls");
        S_choose_ui();
        break;
    default:
        break;
    }
}
//学生删课--------------------待定
void delete()
{
    int i,tip,sum=0;
    timetable *head,*top,*p1,*p2;
    int DID;//要删除号的ID
    printf("原课表是：\n");
    top=head =S_new_list();
    output(head);
    head = top;
    while (head!=NULL)
    {
        sum = sum + head->score;
        head = head->next;
    }
    head = top;
    for (i = 0;;i++)
    {
        head = top;
        printf("\n");
        printf("\n");
        printf("你要删除那个号：");
        scanf("%d", &DID);
        if(DID==0)
        {
            break;
        }        
        p1 = lookfor(head, DID);
        sum = sum - p1->score;
        head = top;
        if(sum<15)
        {
            printf("您的学分不足60分，删除失败！！！\n");
            break;
        }
        p2 = dele(head, DID);
        S_save(p2);
        head = top;
    }
    output(p2);
    printf("您的数据已修改完成！\n");
    printf("\n");
    printf("0:返回上一界面\n");
    printf("1:退出程序\n");
    printf("\n");
    printf("请选择操作：");
    scanf("%d", &tip);
    switch (tip)
    {
    case 0:
        system("cls");
        S_choose_ui(); //返回上一界面
        break;
    case 1:
        exit(0);
        break;

    default:
        printf("请选择正确的指令\n");
        int i;
        for (i = 0; i <= 500000000; i++)
        {
        }
        system("cls"); //刷新屏幕
        begin_ui();
        break;
    }
}
//学生加课--------------待定
void add()
{
    int tip;
    timetable *p1, *p2, *p3;
    p1 = new_list();//从课表文件中得到一个链表
    printf("课表是：\n");
    output(p1);//打印课表到屏幕
    printf("\n\n");
    printf("您已经选择的课程有：\n");
    p2=S_new_list();//从学生
    output(p2);
    printf("\n\n");
    FILE *add = fopen("student_class.txt", "w+");    
    int AID,i,t=0;
    while (p2!=NULL)
    {
        fprintf(add,"|%d |%s  |%s  |%d  |%d  |%d  |%d  |%f  |\n", p2->ID, p2->name, p2->type, p2->A_time, p2->T_time, p2->D_time, p2->score, p2->year);
        p2 = p2->next;
    }   
    for (i = 0;; i++)
    {
        printf("请输入你要添加的课程的编号：");
        scanf("%d", &AID);
        if (AID == 0)
        {
            break;
        }
        while (p2!=NULL)
        {
            if(p2->ID==AID)
            {
                printf("你已经选择过了.\n");
                t = 1;
                break;
            }
            p2 = p2->next;
        }
        if(t==1)
        {
            continue;
        }
        p3 = lookfor(p1, AID);

        fprintf(add, "|%d |%s  |%s  |%d  |%d  |%d  |%d  |%f  |\n", p3->ID, p3->name, p3->type, p3->A_time, p3->T_time, p3->D_time, p3->score, p3->year);
    }
    fprintf(add, "|%d |%d  |%d  |%d  |%d  |%d  |%d  |%d  |\n", 0, 0, 0, 0, 0, 0, 0, 0);
    fclose(add);
    printf("您的数据已修改完成！\n");
    printf("\n");
    printf("0:返回上一界面\n");
    printf("1:退出程序\n");
    printf("\n");
    printf("请选择操作：");
    scanf("%d", &tip);
    switch (tip)
    {
    case 0:
        system("cls");
        S_choose_ui();
        break;
    case 1:
        exit(0);
        break;
    default:
        printf("请选择正确的指令\n");
        int i;
        for (i = 0; i <= 500000000; i++) {}
        system("cls");//刷新屏幕
        begin_ui();
        break;
    }
}
//学生查看选课结果的界面UI------------待定
void S_see()
{
    int tip;
    printf("您选择的课程是：\n");
    timetable *p;
    p = S_new_list();
    output(p);
    printf("=======================\n");
    printf("\n");
    printf("0:返回上一界面\n");
    printf("1:退出程序\n");
    printf("\n");
    printf("请选择操作：");
    scanf("%d", &tip);
    switch (tip)
    {
    case 0:
        system("cls");
        S_choose_ui();
        break;
    case 1:
        exit(0);
        break;
    default:
        printf("请选择正确的指令\n");
        int i;
        for (i = 0; i <= 500000000; i++) {}
        system("cls");//刷新屏幕
        begin_ui();
        break;
    }
}
//===============================管理员操作================================
//管理员登录以后的界面UI
void T_choose_ui()
{
    all_ui();
    int tip;
    MoveCursor(21, 10);
    printf("西安石油大学学生选课管理界面\n");
    MoveCursor(21, 12);
    printf("1:课程信息输入\n");
    MoveCursor(21, 13);
    printf("2:修改课程信息\n");
    MoveCursor(21, 14);
    printf("3:查看学生选课结果\n");
    MoveCursor(21, 15);
    printf("0:退出\n");
    MoveCursor(21, 17);
    printf("请选择您的操作： ");
    scanf("%d", &tip);
    switch (tip)
    {
    case 1:
        system("cls");
        T_input();
        break;
    case 2:
        system("cls");
        T_change();
        break;
    case 3:
        system("cls");
        T_see();
        break;
    case 0:
        system("cls");
        begin_ui();
        break;
    default:
        break;
    }
}
//管理员输入数据的页面UI-------------一半
void T_input()
{
    int tip;
    timetable* head,*p1;
    head = input();
    printf("您输入最终的结果是：\n");
    output(head);
    printf("\n");
    p1 = new_list();
    if(p1!=NULL)
    {
        printf("数据成功存入course_information.dat中\n");
    }
    printf("\n");    
    printf("您的数据已输入完成！\n");
    printf("\n");
    printf("0:返回上一界面\n");
    printf("1:退出程序\n");
    printf("\n");
    printf("请选择操作：");
    scanf("%d", &tip);
    switch (tip)
    {
    case 0:
        system("cls");
        T_choose_ui();
        break;
    case 1:
        exit(0);
        break;
    default:
        printf("请选择正确的指令\n");
        int i;
        for (i = 0; i <= 500000000; i++) {}
        system("cls");//刷新屏幕
        begin_ui();
        break;
    }
}
//管理员修改选课数据的界面UI
void T_change()
{
    all_ui();
    int tip;
    MoveCursor(20, 10);
    printf("您已进入选课数据修改页面(管理员界面)\n");
    MoveCursor(20, 12);
    printf("1:增加未有课程\n");
    MoveCursor(20, 13);
    printf("2:删除已有课程\n");
    MoveCursor(20, 14);
    printf("0:退出\n");
    MoveCursor(20, 16);
    printf("请选择您的操作： ");
    scanf("%d", &tip);
    switch (tip)
    {
    case 1:
        system("cls");        
        T_increase();//增加课程界面
        break;
    case 2:
        system("cls");
        T_dele();//删除课程界面
        break;
    case 0:
        system("cls");
        T_choose_ui();//删除课程界面
        break;
    default:
        break;
    }
}
//管理员删课界面-----------一半
void T_dele()
{
    int tip;
    timetable *head, *p;
    int DID;//要删除号的ID
    printf("原课表是：\n");
    head =new_list();
    output(head);
    printf("\n");
    printf("\n");
    printf("你要删除那个号：");
    scanf("%d", &DID);
    p = dele(head, DID);
    output(p);
    save(p);
    printf("您的数据已修改完成！\n");
    printf("\n");
    printf("0:返回上一界面\n");
    printf("1:退出程序\n");
    printf("\n");
    printf("请选择操作：");
    scanf("%d", &tip);
    switch (tip)
    {
    case 0:
        system("cls");
        T_choose_ui();//返回上一界面
        break;
    case 1:
        exit(0);
        break;
    default:
        printf("请选择正确的指令\n");
        int i;
        for (i = 0; i <= 500000000; i++) {}
        system("cls");//刷新屏幕
        begin_ui();
        break;
    }
}
//管理员加课界面---------------待定
void T_increase()
{
    int tip,AID;
    timetable *head,*p;
    head = new_list();
    output(head);
    printf("你要哪个位置增加课程：");
    scanf("%d", &AID);
    p = increase(head, AID);
    output(p);
    save(p);
    printf("您的数据已修改完成！\n");
    printf("\n");
    printf("0:返回上一界面\n");
    printf("1:退出程序\n");
    printf("\n");
    printf("请选择操作：");
    scanf("%d", &tip);
    switch (tip)
    {
    case 0:
        system("cls");
        T_choose_ui();
        break;
    case 1:
        exit(0);
        break;
    default:
        printf("请选择正确的指令\n");
        int i;
        for (i = 0; i <= 500000000; i++) {}
        system("cls");//刷新屏幕
        begin_ui();
        break;
    }
}
//管理员查看学生选课结果的界面UI-------------待定
void T_see()
{
    printf("学生的选课结果如下：\n");
    timetable *head;
    head = S_new_list();
    output(head);
    printf("\n\n");
    int tip;
    printf("============================\n");
    printf("\n");
    printf("0:返回上一界面\n");
    printf("1:退出程序\n");
    printf("\n");
    printf("请选择操作：");
    scanf("%d", &tip);
    switch (tip)
    {
    case 0:
        system("cls");
        T_choose_ui();
        break;
    case 1:
        exit(0);
        break;
    default:
        printf("请选择正确的指令\n");
        int i;
        for (i = 0; i <= 500000000; i++) {}
        system("cls");//刷新屏幕
        begin_ui();
        break;
    }
}
//=================================动态链表的使用===============================
//课程数据的输入操作
timetable* input()
{
    FILE *T_write=fopen("course_information.txt","w+");
    printf("|编号|名称|性质|总学时|授课学时|实验或上机学时|学分|开设学期|\n");
    timetable* head = NULL, * p1, * p2;
    p1 = p2 = (timetable*)malloc(LEN);
    scanf("%d%s%s%d%d%d%d%f", &p1->ID, p1->name, p1->type, &p1->A_time, &p1->T_time, &p1->D_time, &p1->score, &p1->year);
    // fwrite(p1,LEN,1,T_write);
    fprintf(T_write,"|%d |%s  |%s  |%d  |%d  |%d  |%d  |%f  |\n", p1->ID, p1->name, p1->type, p1->A_time, p1->T_time, p1->D_time, p1->score, p1->year);
    if (p1->ID == 0)
    {
        return head;
    }
    else
    {
        head = p1;
    }
    while (p1->ID != 0)
    {
        p2->next = p1;
        p2 = p1;
        p1 = (timetable*)malloc(LEN);
        scanf("%d%s%s%d%d%d%d%f", &p1->ID, p1->name, p1->type, &p1->A_time, &p1->T_time, &p1->D_time, &p1->score, &p1->year);
        fprintf(T_write,"|%d |%s  |%s  |%d  |%d  |%d  |%d  |%f  |\n", p1->ID, p1->name, p1->type, p1->A_time, p1->T_time, p1->D_time, p1->score, p1->year);
    }
    // p1 = (timetable *)malloc(LEN);
    fprintf(T_write,"|%d |%d  |%d  |%d  |%d  |%d  |%d  |%d  |\n",0,0,0,0,0,0,0,0);
    p2->next = NULL;
    fclose(T_write);
    return head;
}//信息输入界面,以0结束
//对链表内容的输出操作
void output(timetable* head)
{
    timetable* p;
    p = head;
    while (p != NULL)
    {
        printf("|%d |%s  |%s  |%d  |%d  |%d  |%d  |%f  |\n", p->ID, p->name, p->type, p->A_time, p->T_time, p->D_time, p->score, p->year);
        p = p->next;
    }
}
//专门打印选修课的课表的输出
void output_2(timetable* head)
{
    timetable* p;
    p = head;
    while (p != NULL)
    {
        if(strcmp("ele",p->type)==0)
        {
            printf("|%d |%s  |%s  |%d  |%d  |%d  |%d  |%f  |\n", p->ID, p->name, p->type, p->A_time, p->T_time, p->D_time, p->score, p->year);
        }
        p = p->next;
    }
}
//数据增加操作
timetable* increase(timetable* head, int AID)
{
    timetable* p, * p1;
    p = (timetable*)malloc(LEN);
    printf("请输入你要插入的数据：\n");
    scanf("%d%s%s%d%d%d%d%f", &p->ID, p->name, p->type, &p->A_time, &p->T_time, &p->D_time, &p->score, &p->year);
    for (p1 = head; p1 != NULL; p1 = p1->next)
    {
        if (p1->ID == AID)
        {
            p->next = p1->next;
            p1->next = p;
            return head;
        }
    }
    printf("SORRY,没有找到该位置\n");
    return head;
}
//数据删除操作
timetable* dele(timetable* head, int DID)
{
    printf("删除以后的是\n");
    timetable* p1, * p2;
    if (head->ID == DID)
    {
        p1 = head->next;
        free(head);
        return p1;
    }
    else
    {
        for (p1 = head, p2 = p1; p1 != NULL; p2 = p1, p1 = p1->next)
        {
            if (p1->ID == DID)
            {
                p2->next = p1->next;
                free(p1);
                return head;
            }
        }
    }
    printf("SORRY,没有这个课\n原数据如下：\n");
    return head;//争议地区  head or NULL?
}
//数据查找操作
timetable* lookfor(timetable* head, int LID)
{
    timetable* p1;
    for (p1 = head; p1 != NULL; p1 = p1->next)
    {
        if (p1->ID == LID)
        {
            return p1;
        }
    }
    return NULL;
}
//从文件course_information.txt读取数据并得到一个链表的操作
timetable *new_list()
{
    FILE *read=fopen("course_information.txt","r+");
    timetable * p1, * p2, *head = NULL;
    p1 = p2 = (timetable*)malloc(LEN);
    // fread(p1,sizeof(struct timetable),1,read);
    fscanf(read,"|%d |%s  |%s  |%d  |%d  |%d  |%d  |%f  |\n", &p1->ID, p1->name, p1->type, &p1->A_time, &p1->T_time, &p1->D_time, &p1->score, &p1->year);
    if (p1->ID == 0)
    {
        return head;
    }
    else
    {
        head = p1;
    }  
    while (p1->ID != 0)
    {
        p2->next = p1;
        p2 = p1;
        p1 = (timetable*)malloc(LEN);
        // fread(p1,sizeof(struct timetable),1,read);
        fscanf(read,"|%d |%s  |%s  |%d  |%d  |%d  |%d  |%f  |\n", &p1->ID, p1->name, p1->type, &p1->A_time, &p1->T_time, &p1->D_time, &p1->score, &p1->year);
    }
    p2->next = NULL;  
    rewind(read);
    fclose(read);
    return head;
}
//将新的动态链表存入文件course_information.txt中
void save(timetable*head)
{
    FILE *saved = fopen("course_information.txt", "w+");
    timetable *p;
    p = head;
    while(p!=NULL)
    {
        // fwrite(p, LEN, 1, saved);
        fprintf(saved,"|%d |%s  |%s  |%d  |%d  |%d  |%d  |%f  |\n", p->ID, p->name, p->type, p->A_time, p->T_time, p->D_time, p->score, p->year);
        p = p->next;
    }
    fprintf(saved,"|%d |%d  |%d  |%d  |%d  |%d  |%d  |%d  |\n",0,0,0,0,0,0,0,0);
    printf("课程数据成功保存进入文件course_information.txt\n");
    rewind(saved);
    fclose(saved);
}
//从文件student_class.txt读取数据并得到一个链表的操作
timetable *S_new_list()
{
    FILE *read=fopen("student_class.txt","r+");
    timetable * p1, * p2, *head = NULL;
    p1 = p2 = (timetable*)malloc(LEN);
    // fread(p1,sizeof(struct timetable),1,read);
    fscanf(read,"|%d |%s  |%s  |%d  |%d  |%d  |%d  |%f  |\n", &p1->ID, p1->name, p1->type, &p1->A_time, &p1->T_time, &p1->D_time, &p1->score, &p1->year);
    if (p1->ID == 0)
    {
        return head;
    }
    else
    {
        head = p1;
    }  
    while (p1->ID != 0)
    {
        p2->next = p1;
        p2 = p1;
        p1 = (timetable*)malloc(LEN);
        fscanf(read,"|%d |%s  |%s  |%d  |%d  |%d  |%d  |%f  |\n", &p1->ID, p1->name, p1->type, &p1->A_time, &p1->T_time, &p1->D_time, &p1->score, &p1->year);
    }
    p2->next = NULL;  
    rewind(read);
    fclose(read);
    return head;
}
//将新的动态链表存入文件student_class.txt中
void S_save(timetable*head)
{
    FILE *saved = fopen("student_class.txt", "w+");
    timetable *p;
    p = head;
    while(p!=NULL)
    {
        fprintf(saved,"|%d |%s  |%s  |%d  |%d  |%d  |%d  |%f  |\n", p->ID, p->name, p->type, p->A_time, p->T_time, p->D_time, p->score, p->year);
        p = p->next;
    }
    fprintf(saved,"|%d |%d  |%d  |%d  |%d  |%d  |%d  |%d  |\n",0,0,0,0,0,0,0,0);
    printf("选课数据成功保存进入文件student_class.txt\n");
    rewind(saved);
    fclose(saved);
}
//=======================================程序结束================================================
/*
密码：
    学生： 1 1
    管理员：2 2
*/
