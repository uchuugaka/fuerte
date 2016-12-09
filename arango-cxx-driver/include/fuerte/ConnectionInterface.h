////////////////////////////////////////////////////////////////////////////////
/// DISCLAIMER
///
/// Copyright 2016 ArangoDB GmbH, Cologne, Germany
///
/// Licensed under the Apache License, Version 2.0 (the "License");
/// you may not use this file except in compliance with the License.
/// You may obtain a copy of the License at
///
///     http://www.apache.org/licenses/LICENSE-2.0
///
/// Unless required by applicable law or agreed to in writing, software
/// distributed under the License is distributed on an "AS IS" BASIS,
/// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
/// See the License for the specific language governing permissions and
/// limitations under the License.
///
/// Copyright holder is ArangoDB GmbH, Cologne, Germany
///
/// @author Frank Celler
/// @author Jan Uhde
/// @author John Bufton
////////////////////////////////////////////////////////////////////////////////

#ifndef ARANGO_CXX_DRIVER_CONNECTION_INTERFACE_H
#define ARANGO_CXX_DRIVER_CONNECTION_INTERFACE_H 1

#include <fuerte/Request.h>
#include <fuerte/Response.h>

namespace arangodb {
namespace fuerte {
inline namespace v1 {
class ConnectionInterface {
 public:
  ConnectionInterface() = default;
  virtual ~ConnectionInterface() = default;

 public:
  virtual void start() = 0;

  virtual void sendRequest(std::unique_ptr<Request>, OnSuccessCallback,
                           OnErrorCallback) = 0;
};
}
}
}

#endif
