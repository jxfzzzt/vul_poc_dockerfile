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
    stack<int> stk;

    ContainerHandler() {
        // Your initialization goes here
        for(int i = 20000; i <= 65535 ; i ++ ) {
            stk.push(i);
        }
    }

    int32_t open_container(const Req &req, const std::string &info) {
        string cveName = req.cveName;
        int64_t uid = req.uid;

        // transfer cveName to docker image name
        string dockerName = cveName;
        for(int i = 0 ; i < dockerName.size() ; i ++ ) {
            if(dockerName[i] >= 'A' && dockerName[i] <= 'Z') {
                dockerName[i] = tolower(dockerName[i]);
            }
        }
        // 对s
        dockerName += "-poc";
        string dockerRunCmd = "docker run -p 20000:22 -itd --name CVE-2022-3224-POC cve-2022-3224-poc";
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

