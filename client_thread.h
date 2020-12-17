//
// Created by Genki Sasaki on 2020/12/17.
//

#ifndef UDP_FOR_MAC_CLIENT_THREAD_H
#define UDP_FOR_MAC_CLIENT_THREAD_H

bool end_flag = false;  // スレッドの終了を監視するフラグ


/* クライアント（受信）のスレッド */
void *client_thread(void *p) {
    printf("start@thread\n");

    /* 変数の宣言 */
    int *port = (int *)p;   // ポート番号はmain関数からコピー
    int size = 1024;        // 文字のサイズ
    char buf[size];         // 受信するためのバッファ
    char str[size];         // 受信データの格納

    /* ソケットの作成と設定 */
    int sock;
    struct sockaddr_in addr{};
    int retn_byte;

    sock = socket(AF_INET, SOCK_DGRAM, 0);

    addr.sin_family = AF_INET;
    addr.sin_port = htons(*port);
    addr.sin_addr.s_addr = INADDR_ANY;

    bind(sock, (struct sockaddr *)&addr, sizeof(addr));

    /* ノンブロッキングモードに設定 */
    int mode = 1;   // if mode = 0 blocking
    ioctl(sock, FIONBIO, &mode);

    /* 受信開始 */
    while(1) {
        if (end_flag) break;    // 終了のフラグが立ったら抜ける

        retn_byte = recv(sock, buf, size, 0);   //受信
        if(retn_byte > 0) {
            strcpy(str, buf);
            printf("recv: %s@thread\n\r", str);
        }

    }
    printf("end@thread\n\r", str);
    return 0;
}

#endif //UDP_FOR_MAC_CLIENT_THREAD_H
