#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include<math.h>
int Cx=3,Cy=3,Y=0,X=0,cunmoves[7][7]={0};
char cunboard[7][7]={0},cunuserq=0,cuncomq=0;
void display(char board[7][7])//打印棋盘
{
    int hang=0;
    int lie=0;
    char liema='a';
    printf("\n ");
    for(lie=0;lie<7;lie++)
        printf("   %c",liema+lie);
    printf("\n");
    for(hang=0;hang<7;hang++)
    {
        printf("  +");
        for(lie=0;lie<7;lie++)
        {
            if(lie==Cx&&(hang==Cy+1||hang==Cy))
                printf("-+-+");
            else
            printf("---+");
        }
        if(hang==Cy&&Cx==0)
            printf("\n%2d+",hang+1);
        else
            printf("\n%2d|",hang+1);
        for(lie=0;lie<7;lie++)
        {
            if(hang==Cy&&(lie==Cx||lie==Cx-1))
                printf(" %c +",board[hang][lie]);
            else
                printf(" %c |",board[hang][lie]);
        }
        printf("\n");
    }
    printf("  +");
    for(lie=0;lie<7;lie++)
    {
            if(lie==Cx&&(hang==Cy+1||hang==Cy))
                printf("-+-+");
            else
            printf("---+");
    }
    printf("\n");
}
int validmoves(char board[7][7],int moves[7][7],char player)//判断可下的位置
{
    int hang=0;
    int lie=0;
    int hangdelta=0;
    int liedelta=0;
    int keyi=0;
    for(hang=0;hang<7;hang++){
        for(lie=0;lie<7;lie++){
            moves[hang][lie]=0;}}
    for(hang=0;hang<7;hang++){
        for(lie=0;lie<7;lie++)
        {
            if(board[hang][lie]==player)
            {
                for(hangdelta=-2;hangdelta<=2;hangdelta++){
                    for(liedelta=-2;liedelta<=2;liedelta++)
                    {
                        if(hang+hangdelta<0||hang+hangdelta>=7||lie+liedelta<0||lie+liedelta>=7||(hangdelta==0&&liedelta==0))
                            continue;
                        if(board[hang+hangdelta][lie+liedelta]==' '){
                            moves[hang+hangdelta][lie+liedelta]=1;
                            keyi++;}
                    }}
            }
        }}
    return keyi;
}
void makemove(char board[7][7],int x0,int y0,int x,int y,char player)//进行下棋的步骤
{
    int i=0;
    int hangdelta=0;
    int liedelta=0;
    int hang=0;
    int lie=0;
    char oppsite=(player=='0')?'@':'0';
    board[x][y]=player;
    if(x-x0==-2||x-x0==2||y-y0==-2||y-y0==2)
        board[x0][y0]=' ';
    for(hangdelta=-1;hangdelta<=1;hangdelta++){
        for(liedelta=-1;liedelta<=1;liedelta++)
        {
            if(x+hangdelta<0||x+hangdelta>=7||y+liedelta<0||y+liedelta>=7||(hangdelta==0&&liedelta==0))
                continue;
            if(board[x+hangdelta][y+liedelta]==oppsite)
                board[x+hangdelta][y+liedelta]=player;
        }}
}
int getscore(char board[7][7],char player)//计算电脑下一步棋的期望
{
    int score=0;
    int hang=0,lie=0;
    char oppsite=(player=='@')?'0':'@';
    for(hang=0;hang<7;hang++){
        for(lie=0;lie<7;lie++){
            if(board[hang][lie]==player)
                score+=1;
            else if(board[hang][lie]==oppsite)
                score-=1;
        }}
    return score;
}
int bestmove(char board[7][7],int moves[][7],char player)//模拟决定最大期望的一步
{
    int hang=0,lie=0;
    int i=0,j=0;
    char newboard[7][7]={0};
    int score=0;
    int newscore=0;
    char oppsite=(player=='@')?'0':'@';
    for(hang=0;hang<7;hang++){
        for(lie=0;lie<7;lie++){
            if(moves[hang][lie]==0)
                continue;
            int hangdelta=0,liedelta=0;
            for(hangdelta=-2;hangdelta<=2;hangdelta++){
                for(liedelta=-2;liedelta<=2;liedelta++){
                    if(hang+hangdelta<0||hang+hangdelta>=7||lie+liedelta<0||lie+liedelta>=7||(hangdelta==0&&liedelta==0))
                        continue;
                    if(board[hang+hangdelta][lie+liedelta]==player)
                    {
                        for(i=0;i<7;i++){
                            for(j=0;j<7;j++){
                                newboard[i][j]=board[i][j];}}
                        makemove(newboard,hang+hangdelta,lie+liedelta,hang,lie,player);
                        newscore=getscore(newboard,player);
                    }
                    if(score<newscore)
                        score=newscore;
                }}}}
    return score;
}
void computermove(char board[7][7],int moves[7][7],char player)//对电脑的下棋决策
{
    int hang=0,lie=0,flag,t0=49,t;
    int besthang=0,bestlie=0,besthang0=0,bestlie0=0;
    int i=0,j=0;
    int newscore=0,score=100;
    char tempboard[7][7]={0};
    int tempmoves[7][7]={0};
    char oppsite=(player=='@')?'0':'@';
    for(hang=0;hang<7;hang++){
        for(lie=0;lie<7;lie++){
            if(moves[hang][lie]==0)
                continue;
            int hangdelta=0,liedelta=0;
            for(hangdelta=-2;hangdelta<=2;hangdelta++){
                for(liedelta=-2;liedelta<=2;liedelta++){
                    if(hang+hangdelta<0||hang+hangdelta>=7||lie+liedelta<0||lie+liedelta>=7||(hangdelta==0&&liedelta==0))
                        continue;
                    if(board[hang+hangdelta][lie+liedelta]==player)
                    {
                        for(i=0;i<7;i++){
                            for(j=0;j<7;j++){
                                tempboard[i][j]=board[i][j];}}
                        makemove(tempboard,hang+hangdelta,lie+liedelta,hang,lie,player);
                        validmoves(tempboard,tempmoves,oppsite);
                        flag=0;
                        t=0;
                        for(i=0;i<7;i++){
                            for(j=0;j<7;j++){
                                if(tempmoves[i][j]==1){
                                    t=t+1;
                                    flag=1;}}}
                        if(flag==0)
                        {
                            besthang0=hang+hangdelta;
                            bestlie0=lie+liedelta;
                            besthang=hang;
                            bestlie=lie;
                            break;
                        }
                        newscore=bestmove(tempboard,tempmoves,oppsite);
                        if(newscore<=score)
                        {
                            if(newscore<score){
                                score=newscore;
                                besthang0=hang+hangdelta;
                                bestlie0=lie+liedelta;
                                besthang=hang;
                                bestlie=lie;
                                t0=t;}
                            else if(newscore==score&&abs(hangdelta)<=1&&abs(liedelta)<=1){
                                if(abs(besthang0-besthang)<=1&&abs(bestlie0-bestlie)<=1){
                                    if(t<t0){
                                        score=newscore;
                                        besthang0=hang+hangdelta;
                                        bestlie0=lie+liedelta;
                                        besthang=hang;
                                        bestlie=lie;
                                        t0=t;}}
                                else{
                                    score=newscore;
                                    besthang0=hang+hangdelta;
                                    bestlie0=lie+liedelta;
                                    besthang=hang;
                                    bestlie=lie;
                                    t0=t;}}
                            else if(newscore==score&&t<t0){
                                score=newscore;
                                besthang0=hang+hangdelta;
                                bestlie0=lie+liedelta;
                                besthang=hang;
                                bestlie=lie;
                                t0=t;}
                        }}}
                        if(flag==0)
                            break;}
                        if(flag==0)
                            break;}
                        if(flag==0)
                            break;}
    makemove(board,besthang0,bestlie0,besthang,bestlie,player);
}
void zimenu()
{
    printf("   @为黑棋，0为白棋，黑棋为先手\n");
    printf("\n\n\n\n\n");
    printf("         请选择您是否先手\n\n\n\n\n");
    if(X==0)
    {
        printf("               ┏ ┓\n");
        printf("                是\n");
        printf("               ┗ ┛\n\n");
        printf("                否\n\n");
    }
    else if(X==1)
    {
        printf("\n");
        printf("                是\n\n");
        printf("               ┏ ┓\n");
        printf("                否\n");
        printf("               ┗ ┛\n");
    }
}
void againorno(char board[7][7],int userscore,int comscore,int H)
{
    system("cls");
    display(board);
    printf("最终成绩是：\n");
    printf("你：%d     电脑：%d\n",userscore,comscore);
    if(userscore<comscore)
    printf("很遗憾，你输了！\n");
    else
        printf("恭喜你，你赢了！\n");
    printf("你想再玩一次吗:\n");
    if(H==0)
    {
        printf("           ┏ ┓\n");
        printf("            是      否\n");
        printf("           ┗ ┛\n");
    }
    else if(H==1)
    {
        printf("                   ┏ ┓\n");
        printf("            是      否\n");
        printf("                   ┗ ┛\n");
    }
}
void continueorno(int M)
{
    printf("\n\n\n\n\n");
    printf("        是否继续上次游戏？\n\n\n\n\n");
    if(M==0)
    {
        printf("               ┏ ┓\n");
        printf("                是\n");
        printf("               ┗ ┛\n\n");
        printf("                否\n\n");
    }
    else if(M==1)
    {
        printf("\n");
        printf("                是\n\n");
        printf("               ┏ ┓\n");
        printf("                否\n");
        printf("               ┗ ┛\n");
    }
}
void rungame()
{
    char again=0;
    int input,H=0;
    do
    {
        int f=0;
        char board[7][7]={0};
        int moves[7][7]={0};
        int hang=0;
        int lie=0;
        char xianshou=0;//决定谁先手
        int bushu=0;//记录总步数
        int invalidmoves=0;//记录无棋可下的步数
        int comscore=0;
        int userscore=0;
        int x=0,y=0,x0=0,y0=0;
        int player=0;
        char userq=0,comq=0;
        if(Y==0&&cunuserq==0&&cuncomq==0)
        {
            system("cls");
            while(1)
            {
            system("cls");
            zimenu();
            input=_getch();
            if(input==27)
            {
                break;
            }
            else if(input==0x20)
            {
                if(X==0)
                {
                    player=1;
                    userq='@';
                    comq='0';
                    break;
                }
                else if(X==1)
                {
                    player=0;
                    userq='0';
                    comq='@';
                    break;
                }
            }
            else if(input==0xE0)
            {
                input = _getch();//获得第二次输入信息
                switch (input)//判断方向键方向并移动光标位置
                {
                    case 0x48:
                        X--;
                        break;
                    case 0x50:
                        X++;
                        break;
                }
                if (X<0)X=1;//如果光标位置越界则移动到对侧
                if (X>1)X=0;
            }
            system("cls");
            zimenu();
            }
            bushu=4;
            for(hang=0;hang<7;hang++){
                for(lie=0;lie<7;lie++){
                    board[hang][lie]=' ';}}
            board[0][0]=board[6][6]='@';
            board[0][6]=board[6][0]='0';
        }
        else if(Y==0)
        {
            int M=0;
            system("cls");
            while(1)
            {
                system("cls");
                continueorno(M);
                input=_getch();
                if(input==27)
                {
                    break;
                }
                else if(input==0x20)
                {
                    if(M==0)
                    {
                        player=1;
                        bushu=4;
                        userq=cunuserq;
                        comq=cuncomq;
                        cunuserq=0;
                        cuncomq=0;
                        for(hang=0;hang<7;hang++){
                            for(lie=0;lie<7;lie++){
                                board[hang][lie]=cunboard[hang][lie];}}
                        break;
                    }
                    else if(M==1)
                    {
                        cunuserq=0;
                        cuncomq=0;
                        system("cls");
                        while(1)
                        {
                            system("cls");
                            zimenu();
                            input=_getch();
                            if(input==27)
                            {
                                break;
                            }
                            else if(input==0x20)
                            {
                                if(X==0)
                                {
                                    player=1;
                                    userq='@';
                                    comq='0';
                                    break;
                                }
                                else if(X==1)
                                {
                                    player=0;
                                    userq='0';
                                    comq='@';
                                    break;
                                }
                            }
                            else if(input==0xE0)
                            {
                                input = _getch();//获得第二次输入信息
                                switch (input)//判断方向键方向并移动光标位置
                                {
                                    case 0x48:
                                        X--;
                                        break;
                                    case 0x50:
                                        X++;
                                        break;
                                }
                                if (X<0)X=1;//如果光标位置越界则移动到对侧
                                if (X>1)X=0;
                            }
                            system("cls");
                            zimenu();
                        }
                        bushu=4;
                        for(hang=0;hang<7;hang++){
                            for(lie=0;lie<7;lie++){
                                board[hang][lie]=' ';}}
                        board[0][0]=board[6][6]='@';
                        board[0][6]=board[6][0]='0';
                        break;
                    }
                }
                else if(input==0xE0)
                {
                    input = _getch();//获得第二次输入信息
                    switch (input)//判断方向键方向并移动光标位置
                    {
                        case 0x48:
                            M--;
                            break;
                        case 0x50:
                            M++;
                            break;
                    }
                    if (M<0)M=1;//如果光标位置越界则移动到对侧
                    if (M>1)M=0;
                }
                system("cls");
                continueorno(M);
            }
        }
        else if(Y==2)
        {
            Y=0;
            player=1;
            bushu=4;
            userq=cunuserq;
            comq=cuncomq;
            cunuserq=0;
            cuncomq=0;
            for(hang=0;hang<7;hang++){
                for(lie=0;lie<7;lie++){
                    board[hang][lie]=cunboard[hang][lie];}}
        }
        do
        {
            if(input==27)
                break;
            system("cls");
            display(board);
            userscore=0;
            comscore=0;
            for(hang=0;hang<7;hang++){//算分
                for(lie=0;lie<7;lie++){
                    if(board[hang][lie]==comq)
                        comscore+=1;
                    else if(board[hang][lie]==userq)
                        userscore+=1;}}
            printf("你%c：%d         电脑%c：%d\n",userq,userscore,comq,comscore);
            if(player++%2)
            {
                if(validmoves(board,moves,userq))
                {
                    for(;;)
                    {
                        input=_getch();
                        if(input==27)
                        {
                            int i,j;
                            for(i=0;i<7;i++){
                                for(j=0;j<7;j++){
                                    cunboard[i][j]=board[i][j];}}
                            cunuserq=userq;
                            cuncomq=comq;
                            break;
                        }
                        else if(input==8&&bushu>5)
                        {
                            int i,j;
                            for(i=0;i<7;i++){
                                for(j=0;j<7;j++){
                                    board[i][j]=cunboard[i][j];
                                    moves[i][j]=cunmoves[i][j];}}
                        }
                        else if(input == 0x20&&f==0)
                        {
                            x0=Cy;
                            y0=Cx;
                            f=1;
                        }
                        else if(input==0x20&&f==1)
                        {
                            x=Cy;
                            y=Cx;
                            f=0;
                            if(x>=0&&y>=0&&x<7&&y<7&&moves[x][y]&&x-x0<=2&&x-x0>=-2&&y-y0<=2&&y-y0>=-2&&board[x0][y0]==userq)
                            {
                                int i,j;
                                for(i=0;i<7;i++){
                                    for(j=0;j<7;j++){
                                        cunboard[i][j]=board[i][j];
                                        cunmoves[i][j]=moves[i][j];}}
                                makemove(board,x0,y0,x,y,userq);
                                bushu++;
                                break;
                            }
                            else
                            {
                                printf("此步违规，再试一次,按回车继续\n");
                                getchar();
                            }
                        }
                        else if(input==0xE0)
                        {
                            input = _getch();//获得第二次输入信息
                            switch (input)//判断方向键方向并移动光标位置
                            {
                            case 0x4B://
                                Cx--;
                                break;
                            case 0x48:
                                Cy--;
                                break;
                            case 0x4D:
                                Cx++;
                                break;
                            case 0x50:
                                Cy++;
                                break;
                            }
                            if (Cx<0)Cx =6;//如果光标位置越界则移动到对侧
                            if (Cy<0)Cy = 6;
                            if (Cx>6)Cx = 0;
                            if (Cy>6)Cy = 0;
                        }
                        system("cls");
                        display(board);
                        userscore=0;
                        comscore=0;
                        for(hang=0;hang<7;hang++){//算分
                            for(lie=0;lie<7;lie++){
                                if(board[hang][lie]==comq)
                                    comscore+=1;
                                else if(board[hang][lie]==userq)
                                    userscore+=1;}}
                        printf("你%c：%d         电脑%c：%d\n",userq,userscore,comq,comscore);
                    }
                    if(input==27)
                        break;
                }
                else
                {
                    if(++invalidmoves==2||userscore==0||comscore==0)
                        break;
                }
            }
            else
            {
                if(validmoves(board,moves,comq))
                {
                    invalidmoves=0;
                    computermove(board,moves,comq);
                    bushu++;
                }
                else
                {
                    if(++invalidmoves==2||userscore==0||comscore==0)
                        break;
                }
            }
        }while(invalidmoves<2);
        if(input==27)
            break;
        system("cls");
        display(board);
        comscore=0;
        userscore=0;
        for(hang=0;hang<7;hang++){//算分
            for(lie=0;lie<7;lie++){
                if(board[hang][lie]==comq)
                    comscore+=1;
                else if(board[hang][lie]==userq)
                    userscore+=1;}}
        while(1)
        {
            system("cls");
            againorno(board,userscore,comscore,H);
            input=_getch();
            if(input==27)
            {
                break;
            }
            else if(input==0x20)
            {
                if(H==0)
                {
                    break;
                }
                else if(H==1)
                {
                    break;
                }
            }
            else if(input==0xE0)
            {
                input = _getch();//获得第二次输入信息
                switch (input)//判断方向键方向并移动光标位置
                {
                    case 0x4B:
                        H--;
                        break;
                    case 0x4D:
                        H++;
                        break;
                }
                if (H<0)H=1;//如果光标位置越界则移动到对侧
                if (H>1)H=0;
            }
            system("cls");
            againorno(board,userscore,comscore,H);
        }
    if(input==27)
        break;
    }while(H==0);
}
void cunchu()
{
    FILE*fp;
    int i,j,input,t=0;
    char fname[50]={0},buf;
    system("cls");
    printf("请输入存储文档名：");
    while((input=_getch())!=13)
    {
        if(input==27)
            return 0;
        else if(input==8)
        {
            fname[t-1]=0;
            t=t-1;
            system("cls");
            printf("请输入存储文档名：");
            printf("%s",fname);
        }
        else
        {
            fname[t]=input;
            printf("%c",fname[t]);
            t=t+1;
        }
    }
    fp=fopen(fname,"w");
    for(i=0;i<7;i++){
        for(j=0;j<7;j++){
            buf=cunboard[i][j];
            fwrite(&buf,1,1,fp);}}
    fwrite(&cunuserq,1,1,fp);
    fwrite(&cuncomq,1,1,fp);
    fclose(fp);
    if(fname[0]!=0)
    {
        printf("\n存储完成,按回车回主界面\n");
        getchar();
    }
    else
    {
        printf("\n无效文件名，存储失败\n");
        printf("按回车回主界面\n");
        getchar();
    }
}
void duqv()
{
    FILE*fp;
    int i,j,input,t=0;
    char fname[50]={0},buf;
    system("cls");
    printf("请输入读取文档名：");
    while((input=_getch())!=13)
    {
        if(input==27)
            return 0;
        else if(input==8)
        {
            fname[t-1]=0;
            t=t-1;
            system("cls");
            printf("请输入读取文档名：");
            printf("%s",fname);
        }
        else
        {
            fname[t]=input;
            printf("%c",fname[t]);
            t=t+1;
        }
    }
    if((fp=fopen(fname,"r"))==NULL)
    {
        printf("\n无此文档，按回车退回主菜单");
        getchar();
    }
    else
    {
        for(i=0;i<7;i++){
            for(j=0;j<7;j++){
                fscanf(fp,"%c",&buf);
                cunboard[i][j]=buf;}}
        fscanf(fp,"%c",&cunuserq);
        fscanf(fp,"%c",&cuncomq);
        fclose(fp);
        printf("\n读取完成，按回车开始游戏");
        getchar();
        rungame();
        fp=fopen(fname,"w");
        for(i=0;i<7;i++){
            for(j=0;j<7;j++){
                buf=cunboard[i][j];
                fwrite(&buf,1,1,fp);}}
        fwrite(&cunuserq,1,1,fp);
        fwrite(&cuncomq,1,1,fp);
        fclose(fp);
    }
}
void displaymenu()
{
    system("cls");
    printf("\n\n         欢迎来玩同化棋！\n\n\n\n");
    if(Y==0)
    {
        printf("           ┏       ┓\n");
        printf("            开始游戏\n");
        printf("           ┗       ┛\n\n");
        printf("            存储游戏\n\n\n");
        printf("            读取游戏\n\n\n");
        printf("            游戏说明\n\n\n");
        printf("            退出游戏\n\n");
    }
    else if(Y==1)
    {
        printf("\n");
        printf("            开始游戏\n\n");
        printf("           ┏       ┓\n");
        printf("            存储游戏\n");
        printf("           ┗       ┛\n\n");
        printf("            读取游戏\n\n\n");
        printf("            游戏说明\n\n\n");
        printf("            退出游戏\n\n");
    }
    else if(Y==2)
    {
        printf("\n");
        printf("            开始游戏\n\n\n");
        printf("            存储游戏\n\n");
        printf("           ┏       ┓\n");
        printf("            读取游戏\n");
        printf("           ┗       ┛\n\n");
        printf("            游戏说明\n\n\n");
        printf("            退出游戏\n\n");
    }
    else if(Y==3)
    {
        printf("\n");
        printf("            开始游戏\n\n\n");
        printf("            存储游戏\n\n\n");
        printf("            读取游戏\n\n");
        printf("           ┏       ┓\n");
        printf("            游戏说明\n");
        printf("           ┗       ┛\n\n");
        printf("            退出游戏\n\n");
    }
    else if(Y==4)
    {
        printf("\n");
        printf("            开始游戏\n\n\n");
        printf("            存储游戏\n\n\n");
        printf("            读取游戏\n\n\n");
        printf("            游戏说明\n\n");
        printf("           ┏       ┓\n");
        printf("            退出游戏\n");
        printf("           ┗       ┛\n");
    }
}
void youxishuoming()
{
    int input=0;
    system("cls");
    printf("游戏规则：\n");
    printf("    初始布置为双方各将两枚棋子放在最外的对角格。\n");
    printf("    玩家必须轮流移动一枚己子到一个空棋位，该棋位可以是邻近八格（包括对角相邻的格）之一，或相隔一格的次邻十二格之一。移动的新棋位，会使邻近的所有敌棋如黑白棋一样变成己方。如果棋子移到的是邻接八格，会有一颗新己棋出现在原先棋位。\n");
    printf("    无法行棋需弃权。当两方都无法行棋时，游戏结束。以最多子者胜。\n\n");
    printf("操作方法：\n");
    printf("    通过空格键在主菜单确定，在游戏中选子落子，通过方位键移动光标,通过Esc键返回主菜单,按Backspace悔棋\n\n");
    printf("存盘复盘方法：\n");
    printf("    存储时输入文档名进行存盘，再次游戏时通过读取游戏输入文档名进行复盘。\n");
    while(input=_getch())
    {
        if(input==27)
            break;
    }
}
int main()
{
    system("title 同化棋");//标题
    system("mode con cols=34 lines=25");
    system("color F0");
    while(1)
    {
        system("cls");
        displaymenu();
        int input;
        input=_getch();
        if(input==0x20)
        {
            if(Y==0)
                rungame();
            else if(Y==1)
                cunchu();
            else if(Y==2)
                duqv();
            else if(Y==3)
                youxishuoming();
            else if(Y==4)
                break;
        }
        else if(input==0xE0)
        {
            input = _getch();//获得第二次输入信息
            switch (input)//判断方向键方向并移动光标位置
            {
                case 0x48:
                    Y--;
                    break;
                case 0x50:
                    Y++;
                    break;
            }
            if (Y<0)Y =4;//如果光标位置越界则移动到对侧
            if (Y>4)Y =0;
        }
        system("cls");
        displaymenu();
    }
}
