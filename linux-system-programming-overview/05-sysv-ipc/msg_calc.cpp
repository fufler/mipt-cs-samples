#include <iostream>
#include <cassert>
#include <cstring>
#include <limits>

#include <sys/ipc.h>
#include <sys/msg.h>
#include <fcntl.h>

using namespace std;

typedef double data_type;

typedef struct
{
    long mtype;
    struct
    {
        char op;
        data_type x, y;
    } payload;
} request;

typedef struct
{
    long mtype;
    data_type ans;
} response;

constexpr long REQ_MTYPE = 1;
constexpr long RESP_MTYPE = 2;

constexpr data_type ERR = numeric_limits<data_type>::max();

void client(int msgid)
{
    request req;
    response resp;

    req.mtype = REQ_MTYPE;

    while (true)
    {
        cout << ">>> ";
        cin >> req.payload.op >> req.payload.x >> req.payload.y;
        msgsnd(msgid, &req, sizeof(req.payload), 0);

        if (req.payload.op == 'x')
            break;

        msgrcv(msgid, &resp, sizeof(resp.ans), RESP_MTYPE, 0);
        cout << resp.ans << endl;
    }
}

void server(int msgid)
{
    request req;
    response resp;

    resp.mtype = RESP_MTYPE;

    while (true)
    {
        msgrcv(msgid, &req, sizeof(req.payload), REQ_MTYPE, 0);

        cout << "Got request: " << req.payload.x << " " << req.payload.op << " " << req.payload.y << endl;

        if (req.payload.op == 'x')
            break;

        switch (req.payload.op)
        {
            case '+': resp.ans = req.payload.x + req.payload.y; break;
            case '-': resp.ans = req.payload.x - req.payload.y; break;
            case '*': resp.ans = req.payload.x * req.payload.y; break;
            case '/': resp.ans = req.payload.y == 0.0 ? ERR : req.payload.x / req.payload.y; break;
            default: resp.ans = ERR;
        }

        cout << "Sending response: " << resp.ans << endl;

        msgsnd(msgid, &resp, sizeof(resp.ans), 0);
    }
}

int main(int argc, char** argv)
{
    assert(argc == 2);

    bool client_mode = !strcmp(argv[1], "client");
    bool server_mode = !strcmp(argv[1], "server");

    assert(client_mode || server_mode);

    key_t key = ftok(argv[0], 1);
    assert(key != -1);

    int msgid = msgget(key, IPC_CREAT | S_IRUSR | S_IWUSR);
    assert(msgid >= 0);

    if (client_mode)
        client(msgid);
    else
        server(msgid);

    msgctl(msgid, IPC_RMID, nullptr);
    
    return 0;
}
