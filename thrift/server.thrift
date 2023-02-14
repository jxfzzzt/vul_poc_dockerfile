namespace cpp container_service

struct Req {
    1: i64 uid,
    2: string cveName,
}

service Container {
    i32 open_container(1: Req req, 2: string info),

    i32 close_container(1: Req req, 2: string info),
}