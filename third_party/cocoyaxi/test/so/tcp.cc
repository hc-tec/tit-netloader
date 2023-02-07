#include "co/all.h"

DEF_string(ip, "127.0.0.1", "ip");
DEF_int32(port, 9988, "port");
DEF_int32(client_num, 1, "client num");
DEF_string(key, "", "private key file");
DEF_string(ca, "", "certificate file");

void on_connection(tcp::Connection conn) {
    char buf[8] = { 0 };

    while (true) {
        int r = conn.recv(buf, 8);
        if (r == 0) {         /* client close the connection */
            conn.close();
            break;
        } else if (r < 0) { /* error */
            conn.reset(3000);
            break;
        } else {
            LOG << "server recv " << fastring(buf, r);
            LOG << "server send pong";
            r = conn.send("pong", 4);
            if (r <= 0) {
                LOG << "server send error: " << conn.strerror();
                conn.reset(3000);
                break;
            }
        }
    }
}

void client_fun() {
    bool use_ssl = !FLG_key.empty() && !FLG_ca.empty();
    tcp::Client c(FLG_ip.c_str(), FLG_port, use_ssl);
    if (!c.connect(3000)) return;

    char buf[8] = { 0 };

    for (int i = 0; i < 3; ++i) {
        LOG << "client send ping";
        int r = c.send("ping", 4);
        if (r <= 0) {
            LOG << "client send error: " << c.strerror();
            break;
        }

        r = c.recv(buf, 8);
        if (r < 0) {
            LOG << "client recv error: " << c.strerror();
            break;
        } else if (r == 0) {
            LOG << "server close the connection";
            break;
        } else {
            LOG << "client recv " << fastring(buf, r) << '\n';
            co::sleep(500);
        }
    }

    c.disconnect();
}


co::Pool* gPool = NULL;

// we don't need to close the connection manually with co::Pool.
void client_with_pool() {
    co::PoolGuard<tcp::Client> c(*gPool);
    if (!c->connect(3000)) return;

    char buf[8] = { 0 };

    for (int i = 0; i < 3; ++i) {
        LOG << "client send ping";
        int r = c->send("ping", 4);
        if (r <= 0) {
            LOG << "client send error: " << c->strerror();
            break;
        }

        r = c->recv(buf, 8);
        if (r < 0) {
            LOG << "client recv error: " << c->strerror();
            break;
        } else if (r == 0) {
            LOG << "server close the connection";
            break;
        } else {
            LOG << "client recv " << fastring(buf, r) << '\n';
            co::sleep(500);
        }
    }
}

int main(int argc, char** argv) {
    flag::init(argc, argv);
    FLG_cout = true;
    gPool = new co::Pool(
        []() {
            bool use_ssl = !FLG_key.empty() && !FLG_ca.empty();
            return (void*) new tcp::Client(FLG_ip.c_str(), FLG_port, use_ssl);
        },
        [](void* p) { delete (tcp::Client*) p; }
    );

    tcp::Server s;
    s.on_connection(on_connection);
    s.start(FLG_ip.c_str(), FLG_port, FLG_key.c_str(), FLG_ca.c_str());

    sleep::ms(32);

    if (FLG_client_num > 1) {
        for (int i = 0; i < FLG_client_num; ++i) {
            go(client_with_pool);
        }
    } else {
        go(client_fun);
    }

    sleep::sec(2);
    s.exit();
    delete gPool;
    return 0;
}
