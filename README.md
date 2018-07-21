# Fuerte

Fuerte is a c++ library that allows you to communicate with a ArangoDB database
over the http and velocystream (optionally ssl encrypted) protocols.

## design

Fuerte is a communication library only. You will get what the other side is
sending you. No conversion is done! When receiving a message fuerte provides
content type and payload. In case the payload is velocypack you can access the
slices with slices() when using the c++ driver. The node driver will always
provide the payload as it is. 

Fuerte itself is designed to be thread-safe, connections can handle multiple
producer threads concurrently sending requests. Of course it depends on the underlying
protocol implementation how "concurrent" requests really are. The velocystream 
protocol allows for full duplex communication, the HTTP only for half duplex
communication.

## Build requirements

The following development packages need to be installed

- C++ 11 compiler
- VelocyPack
- cmake 3.4
- Boost Libraries 1.67

VelocyPack source can be obtained from GitHub using the following git command into your chosen directory 
git clone https://github.com/arangodb/velocypack
Boost can be installed via the package manager of your choice

```bash
mkdir build; cd build
cmake .. \
      -DCMAKE_BUILD_TYPE=Debug \
      -DFUERTE_TESTS=On \
      -DFUERTE_EXAMPLES=ON \
      -DVELOCYPACK_SOURCE_DIR=../../velocypack
make -j4
```

To add for example the address sanitzer for _clang_ you can add `LDFLAGS="-fsanitize=address" CXXFLAGS="-fsanitize=address"`
in front of the _cmake_ command.

## Usage example

```c++
#include <fuerte/fuerte.h>
#include <velocystream/Slice.h>

int main(){
    using namespace arangodb::fuerte;
    EventLoopService eventLoopService;
    auto conn = ConnectionBuilder().host("vst://localhost:8529")
                                   .user("hund")
                                   .password("arfarf")
                                   .connect(eventLoopService);
    auto request = fu::createRequest(fu::RestVerb::Get, "/_api/version");
    auto result = _connection->sendRequest(std::move(request));
    auto slice = result->slices().front();
    std::cout << slice.get("version").copyString();
    std::cout << slice.get("server").copyString();
}
```

## nodejs: a low-level node.js driver

Install node and npm and execute

```
> cd cmake-node-driver
> npm install
```

## Project status

Basic functionality of the c++ and node driver are implemented:

Things that are missing:

- agenda - the task is to get the nosql-tests working - what do those tests require?
- tests - without tests we never know the exact status (below is a list of missing featues)
- hanging with 100k requests (needs to be found)
- http/vst: content type handling needs testing
- http: only first slice is added as payload
- vst: no compression
- node: no good node integration (libuv)
- node: no real asynchronous work because of the above
- node: not building on different systems (locating of headers)

## License

Fuerte is published under the Apache 2 License. Please see
the files [LICENSE](LICENSE) and
[LICENSES-OTHER-COMPONENTS.md](LICENSES-OTHER-COMPONENTS.md)
for details.
