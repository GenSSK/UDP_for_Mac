#include <iostream>
#include <stdio.h>
#include <fcntl.h>
#include <termios.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/ioctl.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include "client_thread.h"

int main() {
    printf("start\n");

    /* 変数の宣言 */
    int port = 23231;               //ポート番号:任意の番号
    const int size = 1024;          // 文字の大きさ
    char buf[size] = { '\0' };      // 入力された文字
    char str[size] = { '\0' };      // 送信する文字
    char address[] = "127.0.0.1";   // 送信するアドレス

    /* ソケットの作成と設定 */
    int sock;
    struct sockaddr_in addr{};
    int send_byte;

    sock = socket(AF_INET, SOCK_DGRAM, 0);

    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    addr.sin_addr.s_addr = inet_addr(address);


    /*　スレッド処理　*/
    pthread_t pthread;
    pthread_create(&pthread, NULL, client_thread, (void*)&port);

    while(1){

        scanf("%s", &buf);  // キーボードの文字入力

        strcpy(str, buf);   //bufの中身をstrにコピー
        send_byte = sendto(sock, str, size, 0, (struct sockaddr *)&addr, sizeof(addr)); //送信
        if(send_byte){
            printf("send: %s\n", str);
        }

        if (strcmp(str, "end") == 0) break; //endが入力されたら終了

        sleep(1);   // 一秒待つ
    }

    end_flag = true;    // スレッドを終了するフラグを立てる

    close(sock);
    pthread_join(pthread, NULL);    // スレッドが終わるまで待つ

    printf("end\n");
    return 0;
}