#include "container_server/Container.h"
#include <thrift/protocol/TBinaryProtocol.h>
#include <thrift/server/TSimpleServer.h>
#include <thrift/transport/TServerSocket.h>
#include <thrift/transport/TBufferTransports.h>
#include <cstdlib>
#include <iostream>

using namespace ::apache::thrift;
using namespace ::apache::thrift::protocol;
using namespace ::apache::thrift::transport;
using namespace ::apache::thrift::server;

using boost::shared_ptr;

using namespace ::container_service;

class ContainerHandler : virtual public ContainerIf {
public:
    ContainerHandler() {
        // Your initialization goes here
    }

    int32_t open_container(const Req &req, const std::string &info) {
        // Your implementation goes here
        system("");
        printf("open_container\n");
    }

    int32_t close_container(const Req &req, const std::string &info) {
        // Your implementation goes here
        printf("close_container\n");
    }

};

int main(int argc, char **argv) {
    // port
    int port = 9090;
    shared_ptr <ContainerHandler> handler(new ContainerHandler());
    shared_ptr <TProcessor> processor(new ContainerProcessor(handler));
    shared_ptr <TServerTransport> serverTransport(new TServerSocket(port));
    shared_ptr <TTransportFactory> transportFactory(new TBufferedTransportFactory());
    shared_ptr <TProtocolFactory> protocolFactory(new TBinaryProtocolFactory());

    std::cout << "Run Container Server start at 9090 port" << std::endl;

    // start server
    TSimpleServer server(processor, serverTransport, transportFactory, protocolFactory);
    server.serve();
    return 0;
}

