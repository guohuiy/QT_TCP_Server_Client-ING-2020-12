#ifndef MSGINFO_H
#define MSGINFO_H
/*服务器端使用的端口*/
const int SERVER_PORT_NO=8889;
const int SERVER_IP_NO=11111;

/*客户端与服务器端使用的消息类型定义*/
const int INITIAL_VALUE=65535;

/*客户端使用的消息代码含义*/
const int DISCONNECT=0;
const int BUY_TICKET=1;
const int INQUIRE_ONE=2;
const int INQUIRE_ALL=3;

/*服务器端使用的消息代码含义*/
const int BUY_SUCCEED=255;
const int BUY_FAILED=256;
const int INQUIRE_SUCCEED=257;
const int INQUIRE_FAILED=258;
const int UNKNOWN_CODE=259;
const int INQUIRE_ALL_SUCCEED=260;
const int INQUIRE_ALL_FAILED=261;

#endif // MSGINFO_H
