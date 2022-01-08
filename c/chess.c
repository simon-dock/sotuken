 #include <stdio.h>

 int bx,by; 
 int cask1=0,cask2=0,casrl1=0,casrr1=0,casrl2=0,casrr2=0,crl1=0,crr1=0,crl2=0,crr2=0;//キャスリング関係
 int flag1,flag2,FSflag=1,cmflag;//勝ち判定、先手後手,移動可能

 void display(int board[8][8][2],int cmove[8][8],char piece[7]);
 void range(int slp,int board[8][8][2],int cmove[8][8],int enP[8][8]);
 
 int main(void){

     int i,j,k,ax,ay,pm,slp;
     int InBoardflag,canflag;//盤面内、移動可能

    /*盤面の管理配列　第１引数＝行　第２引数＝列　第３引数＝｛０＝駒の種類、１＝陣営判定｝
    0=NULL 1=Pwan 2=kNight 3=Bishop 4=Rook 5=Queen 6=King
    0=NULL 1=White(First) -1=Black(Second)*/
     int board[8][8][2]={{{4,-1},{2,-1},{3,-1},{5,-1},{6,-1},{3,-1},{2,-1},{4,-1}},
                        {{1,-1},{1,-1},{1,-1},{1,-1},{1,-1},{1,-1},{1,-1},{1,-1}},
                        {{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0}},
                        {{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0}},
                        {{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0}},
                        {{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0}},
                        {{1,1},{1,1},{1,1},{1,1},{1,1},{1,1},{1,1},{1,1}},
                        {{4,1},{2,1},{3,1},{5,1},{6,1},{3,1},{2,1},{4,1}}};
    /*移動可能な座標配列　第１引数＝行　第２引数＝列　値0=移動不可　1=移動可*/
     int cmove[8][8]={{0,0,0,0,0,0,0,0},
                      {0,0,0,0,0,0,0,0},
                      {0,0,0,0,0,0,0,0},
                      {0,0,0,0,0,0,0,0},
                      {0,0,0,0,0,0,0,0},
                      {0,0,0,0,0,0,0,0},
                      {0,0,0,0,0,0,0,0},
                      {0,0,0,0,0,0,0,0}};
    /*アンパッサン(en passant)の残像を管理する配列 
    第１引数＝行　第２引数＝列　値0=なし　1=残像あり*/
     int enP[8][8]={{0,0,0,0,0,0,0,0},
                    {0,0,0,0,0,0,0,0},
                    {0,0,0,0,0,0,0,0},
                    {0,0,0,0,0,0,0,0},
                    {0,0,0,0,0,0,0,0},
                    {0,0,0,0,0,0,0,0},
                    {0,0,0,0,0,0,0,0},
                    {0,0,0,0,0,0,0,0}};
     char piece[7]={' ','P','N','B','R','Q','K'};//' 'は半角スペース一つ

     printf("Game Start\n");
     printf("\n");


    while(1){

        /*盤面表示*/
        
        display(board,cmove,piece);

        if(flag1==0){
            printf("後手プレイヤーの勝ち\n");
            return 0;
        }
        if(flag2==0){
            printf("先手プレイヤーの勝ち\n");
            return 0;
        }


        /*駒の移動を入力*/
        
        if(FSflag==1){
                printf("先手番です（白）\n");
            }else{
                printf("後手番です（緑）\n");
            }
        InBoardflag=0;
        canflag=0;
        do{    
            do{
                do{
                    if(0<InBoardflag)printf("正しい値を入力してください\n");
                    if(0<canflag)printf("移動可能なマスがありません\n");
                    InBoardflag=0;
                    canflag=0;
                    printf("動かす駒の座標を入力してください(x,y)\n");
                    scanf("%d",&bx);
                    scanf("%d",&by);
                    InBoardflag++;
                    }while(by<1||8<by||bx<1||8<bx);//盤内か判定
                    }while(board[by-1][bx-1][0]==0||board[by-1][bx-1][1]!=FSflag);//そのマスに先手後手に対応する駒があるか判定
                    bx=bx-1;
                    by=by-1;
                    slp=board[by][bx][0];
                    range(slp,board,cmove,enP);
                    display(board,cmove,piece);
                    canflag++;
        }while(cmflag==0);//移動可能なマスがあるか判定

        printf("動かす駒 %c(%d,%d)\n",piece[slp],bx+1,by+1);

        /*移動する座標の入力*/
        InBoardflag=0;
        do{
            do{
                if(0<InBoardflag)printf("正しい値を入力してください\n");
                printf("動かしたい座標を入力してください(x,y)\n");
                scanf("%d",&ax);
                scanf("%d",&ay);
                InBoardflag++;
                }while(ay<1||8<ay||ax<1||8<ax);
                }while(cmove[ay-1][ax-1]==0);

        ax=ax-1;
        ay=ay-1;

        /*キャスリング（入城）*/
        if(crl1==1){
            if(ay==7&&ax==2){
                board[7][3][0]=board[7][0][0];
                board[7][3][1]=board[7][0][1];
                board[7][0][0]=0;
                board[7][0][1]=0;
                printf("キャスリングしました\n");
            }
        }
        if(crr1==1){
            if(ay==7&&ax==6){
                board[7][5][0]=board[7][7][0];
                board[7][5][1]=board[7][7][1];
                board[7][7][0]=0;
                board[7][7][1]=0;
                printf("キャスリングしました\n");
            }
        }
        if(crl2==1){
            if(ay==0&&ax==2){
                board[0][3][0]=board[0][0][0];
                board[0][3][1]=board[0][0][1];
                board[0][0][0]=0;
                board[0][0][1]=0;
                printf("キャスリングしました\n");
            }
        }
        if(crr2==1){
            if(ay==0&&ax==6){
                board[0][5][0]=board[0][7][0];
                board[0][5][1]=board[0][7][1];
                board[0][7][0]=0;
                board[0][7][1]=0;
                printf("キャスリングしました\n");
            }
        }

        /*キングとルークが動いていないか管理するフラグ*/
        if(by==0&&bx==0)casrl2=1;
        if(by==0&&bx==7)casrr2=1;
        if(by==0&&bx==4)cask2=1;
        if(by==7&&bx==0)casrl1=1;
        if(by==7&&bx==7)casrr1=1;
        if(by==7&&bx==4)cask1=1;

        /*移動の処理*/
        board[ay][ax][0]=board[by][bx][0];
        board[ay][ax][1]=board[by][bx][1];

        board[by][bx][0]=0;
        board[by][bx][1]=0;

        /*プロモーション（昇格）*/
        for(i=0;i<8;i++){
            if(board[0][i][0]==1){
                printf("何に昇格しますか？数字を入力してください\n");
                printf("2=ナイト,3=ビショップ,4=ルーク,5=クイーン\n");
                scanf("%d",&pm);
                board[0][i][0]=pm;
            }
            if(board[7][i][0]==1){
                printf("何に昇格しますか？数字を入力してください\n");
                printf("2=ナイト,3=ビショップ,4=ルーク,5=クイーン\n");
                scanf("%d",&pm);
                board[7][i][0]=pm;
            }
        }

        /*アンパッサン*/

        //配列の初期化
        for(i=0;i<8;i++){
            for(j=0;j<8;j++){
                if(enP[i][j]==1){
                    
                }
            }
        }
        for(i=0;i<8;i++){
            for(j=0;j<8;j++){
                enP[i][j]=0;
            }
        }

        //ポーンを動かした判定
        if(slp==1){
            if(FSflag==1){//先手の場合
                if(by==6&&ay==4){//２マス移動したか判定
                    enP[ay+1][ax]=1;
                }
            }
            if(FSflag==-1){
                if(by==1&&ay==3){
                    enP[ay-1][ax]=1;
                }
            }
        }

        /*cmflagの初期化*/
        cmflag=0;

        /*cmoveの再初期化*/
        for(i=0;i<8;i++){
            for(j=0;j<8;j++){
                cmove[i][j]=0;
            }
        }
        /*crl,crrの初期化*/
        crl1=0;
        crr1=0;
        crl2=0;
        crr2=0;

        /*先手後手入れ替え*/
        FSflag=FSflag*-1;

    }

    return 0;
 }


 void display(int board[8][8][2],int cmove[8][8],char piece[7]){

     int i,j;

     printf("\x1b[46m\x1b[1m");
     flag1=0;
     flag2=0;
     for(i=0;i<8;i++){
         printf("%4d",i+1);
     }
     printf("  \x1b[49m\n");//半角スペース２つ

     for(i=0;i<8;i++){
         printf("\x1b[46m ");//半角スペース１つ
         for(j=0;j<32;j++){
             printf("—");
         }
         printf(" \x1b[49m\n");//半角スペース１つ
         
         printf("\x1b[46m");
         printf("%d",i+1);
         for(j=0;j<8;j++){
             printf("|");
             if(board[i][j][1]==-1){
                 printf("\x1b[32m");
             }
             if(cmove[i][j]==1){//移動可能マスの表示
                 cmflag=1;
                 printf("\x1b[106m");
             }
             if(board[i][j][0]==6){//キングがあるか判定
                 if(board[i][j][1]==1){
                     flag1=1;
                 }else{
                     flag2=1;
                 }
             }
             printf("%2c ",piece[board[i][j][0]]);//%2cの後半角スペース一つ
             printf("\x1b[46m");
             printf("\x1b[39m");
         }
         printf("|\x1b[49m\n");
     }
     return ;
 }

 void range(int slp,int board[8][8][2],int cmove[8][8],int enP[8][8]){

    int i,j,k,py,px;

    if(slp==1){
         if(FSflag==1){//先手番の判定
             if(by==6){//初期位置の判定
                 if(board[5][bx][1]==0){
                     if(board[4][bx][1]==0){//駒がない場合２マス進める
                         cmove[4][bx]=1;
                     }
                 }
             }
             py=by-1;
             px=bx-1;
             if(0<=py&&py<8&&0<=px&&px<8){//左上に敵の駒or敵の残像があれば移動可能
                 if(board[py][px][1]==FSflag*-1||enP[py][px]==1){
                     cmove[py][px]=1;
                 }
             }
             py=by-1;
             px=bx+1;
             if(0<=py&&py<8&&0<=px&&px<8){//右上に敵の駒or敵の残像があれば移動可能
                 if(board[py][px][1]==FSflag*-1||enP[py][px]==1){                         
                     cmove[py][px]=1;
                 }
             }
             py=by-1;
             if(0<=py&&py<8&&0<=bx&&bx<8){//真上に駒がなければ進める
                 if(board[py][bx][1]==0){                         
                     cmove[py][bx]=1;
                 }
             }
         }
         if(FSflag==-1){//以下後手番バージョン
             if(by==1){
                 if(board[2][bx][1]==0){
                     if(board[3][bx][1]==0){
                         cmove[3][bx]=1;
                     }
                }
             }
             py=by+1;
             px=bx+1;
             if(0<=py&&py<8&&0<=px&&px<8){
                 if(board[py][px][1]==FSflag*-1||enP[py][px]==1){
                     cmove[py][px]=1;
                 }
             }
             py=by+1;
             px=bx-1;
             if(0<=py&&py<8&&0<=px&&px<8){
                 if(board[py][px][1]==FSflag*-1||enP[py][px]==1){                         
                     cmove[py][px]=1;
                 }
             }
             py=by+1;
             if(0<=py&&py<8&&0<=bx&&bx<8){
                 if(board[py][bx][1]==0){                         
                     cmove[py][bx]=1;
                 }
             }
         }
     }
     if(slp==2){
         for(i=-1;i<2;i++){
             for(j=-1;j<2;j++){
                 if(i==0||j==0){//斜め移動のx,yのどちらかを２倍してやるとナイトを表現できる
                 }else{
                     for(k=0;k<2;k++){
                         if(k==0){
                             py=by+i*2;
                             px=bx+j;
                         }
                         if(k==1){
                             py=by+i;
                             px=bx+j*2;
                         }
                         if(0<=py&&py<8&&0<=px&&px<8){
                             if(board[py][px][1]!=FSflag){
                                 cmove[py][px]=1;
                             }
                         }
                     }
                 }
             }
         }
     }
     if(slp==3){
         for(i=-1;i<2;i++){
             for(j=-1;j<2;j++){
                 if(i==0||j==0){//x,yのいずれかに0が含まれる、つまり縦横の動きであり、それを排除することでビショップを表現
                 }else{
                    py=by+i;
                    px=bx+j;
                    if(0<=py&&py<8&&0<=px&&px<8){
                        if(board[py][px][1]==FSflag){
                        }else if(board[py][px][1]==FSflag*-1){
                            cmove[py][px]=1;
                        }else{
                            cmove[py][px]=1;
                            for(k=0;k<8;k++){
                                py=py+i;
                                px=px+j;
                                if(0<=py&&py<8&&0<=px&&px<8){
                                    if(board[py][px][1]==FSflag){
                                        break;
                                    }else if(board[py][px][1]==FSflag*-1){
                                        cmove[py][px]=1;
                                        break;
                                    }else{
                                        cmove[py][px]=1;
                                    }
                                }
                            }
                        }
                    }
                 }
             }
         }
     }
     if(slp==4){
         for(i=-1;i<2;i++){
             for(j=-1;j<2;j++){
                 if(i!=0&&j!=0){//x,yに0が含まれない、つまり斜め移動の時は何もしないことでルークを表現
                 }else{
                    py=by+i;
                    px=bx+j;
                    if(0<=py&&py<8&&0<=px&&px<8){
                        if(board[py][px][1]==FSflag){
                        }else if(board[py][px][1]==FSflag*-1){
                            cmove[py][px]=1;
                        }else{
                            cmove[py][px]=1;
                            for(k=0;k<8;k++){
                                py=py+i;
                                px=px+j;
                                if(0<=py&&py<8&&0<=px&&px<8){
                                    if(board[py][px][1]==FSflag){
                                        break;
                                    }else if(board[py][px][1]==FSflag*-1){
                                        cmove[py][px]=1;
                                        break;
                                    }else{
                                        cmove[py][px]=1;
                                    }
                                }
                            }
                        }
                    }
                 }
             }
         }
     }
     if(slp==5){
         for(i=-1;i<2;i++){
             for(j=-1;j<2;j++){
                 py=by+i;
                 px=bx+j;
                 if(0<=py&&py<8&&0<=px&&px<8){
                     if(board[py][px][1]==FSflag){//移動先が自分と同じ陣営の駒の場合、何もせずループを継続
                     }else if(board[py][px][1]==FSflag*-1){
                         cmove[py][px]=1;//違う陣営の場合cmoveに書き込み３×３のループを継続
                     }else{
                         cmove[py][px]=1;//駒がない場合cmoveに書き込んだあと、その直線上のマスも調べるループに入る
                         for(k=0;k<8;k++){
                             py=py+i;//３×３のループで進んだ方向と同じ方向に進める
                             px=px+j;
                             if(0<=py&&py<8&&0<=px&&px<8){
                                 if(board[py][px][1]==FSflag){//同じ陣営の駒がある場合、そこには自分の駒は置けないためループを抜ける
                                     break;
                                 }else if(board[py][px][1]==FSflag*-1){//違う陣営の駒がある場合、そのマスまでいけるがその先にはいけないため記録したあとループを抜ける
                                     cmove[py][px]=1;
                                     break;
                                 }else{
                                     cmove[py][px]=1;//駒がない場合、記録した後、直線上を探すループを継続
                                 }
                             }
                         }
                     }
                 }
             }
         }
     }
     if(slp==6){
         for(i=-1;i<2;i++){
             for(j=-1;j<2;j++){//周辺の３×３の範囲を回す
                 py=by+i;//移動先をpx,pyに保管
                 px=bx+j;
                 if(0<=py&&py<8&&0<=px&&px<8){//盤面のサイズからはみ出ないようにする判定
                     if(board[py][px][1]!=FSflag){//移動先の駒が現在の手番の人の駒と同じか判定
                         cmove[py][px]=1;
                     }
                 }
             }
         }
         if(FSflag==1){
             if(cask1==0&&casrl1==0){
                 if(board[7][1][0]==0&&board[7][2][0]==0&&board[7][3][0]==0){
                     cmove[7][2]=1;
                     crl1=1;
                 }
             }
             if(cask1==0&&casrr1==0){
                 if(board[7][5][0]==0&&board[7][6][0]==0){
                     cmove[7][6]=1;
                     crr1=1;
                 }
             }
         }
         if(FSflag==-1){
             if(cask2==0&&casrl2==0){
                 if(board[0][1][0]==0&&board[0][2][0]==0&&board[0][3][0]==0){
                     cmove[0][2]=1;
                     crl2=1;
                 }
             }
             if(cask2==0&&casrr2==0){
                 if(board[0][5][0]==0&&board[0][6][0]==0){
                     cmove[0][6]=1;
                     crr2=1;
                 }
             }
         }
     }
     return ;
}